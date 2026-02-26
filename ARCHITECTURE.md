# ESP32 Eyes ESPHOME Library - Architecture Overview

## System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                     ESPHOME Framework                           │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │           User Application / Home Assistant               │  │
│  └────────────────────────┬────────────────────────────────┘  │
│                           │                                    │
│  ┌────────────────────────▼────────────────────────────────┐  │
│  │         Esp32EyesComponent (C++/Component)              │  │
│  │  - Setup & Loop management                              │  │
│  │  - Configuration handling                               │  │
│  │  - Update timing                                        │  │
│  └────────────┬────────────────────────────┬──────────────┘  │
│               │                            │                  │
│  ┌────────────▼──────────────┐  ┌─────────▼─────────────┐   │
│  │  Face (Core Rendering)    │  │ EsphomeDisplayAdapter │   │
│  │  - Eye positions          │  │ - Converts calls to   │   │
│  │  - Emotion management     │  │   ESPHOME Display API │   │
│  │  - Blink/Look control     │  └─────────┬─────────────┘   │
│  │  - Expression transitions │            │                 │
│  └────────────┬──────────────┘  ┌─────────▼──────────────┐  │
│               │                 │                        │  │
│  ┌────────────▼──────────────┐  │  IDisplayAdapter      │  │
│  │ Eye + EyeDrawer           │  │  (Abstract Interface) │  │
│  │ - Shape calculation       │  │                       │  │
│  │ - Curve rendering         │  └─────────┬──────────────┘  │
│  │ - Slope/radius handling   │            │                 │
│  └────────────┬──────────────┘            │                 │
│               │                ┌──────────┴──────────────┐  │
│               │                ▼                         ▼  │
│               │         ┌──────────────┐        ┌────────────┐ │
│               └────────▶│ ESPHOME DMA  │        │ U8g2 Lib   │ │
│                         │ Display Buf  │        │ (Optional) │ │
│                         └──────────────┘        └────────────┘ │
│                               │                               │
└───────────────────────────────┼───────────────────────────────┘
                                │
                    ┌───────────▼──────────┐
                    │   Display Hardware   │
                    │  (SSD1306, ST7789, │
                    │   ILI9341, etc)     │
                    └──────────────────────┘
```

## Component Layer Stack

### 1. **ESPHOME Integration Layer** (Top)
- **Esp32EyesComponent**: Main component class
- **Python Integration** (`__init__.py`): YAML configuration parsing
- **Lifecycle Management**: Setup, loop, teardown

### 2. **Display Abstraction Layer** (Middle)
- **IDisplayAdapter**: Abstract interface for drawing
- **EsphomeDisplayAdapter**: ESPHOME Display implementation
- **U8g2DisplayAdapter**: U8g2 library support (optional)

### 3. **Rendering Engine** (Core)
- **Face**: Orchestrates left/right eyes, emotions, behaviors
- **Eye**: Individual eye state and configuration
- **EyeDrawer**: Low-level drawing primitives
- **Expression/Behavior/Blink**: Logic layers

### 4. **Hardware Drivers** (Bottom)
- ESPHOME Display component (I2C, SPI, etc.)
- Original display library (if using U8g2)

## Data Flow

### Initialization Sequence

```
1. ESPHome Boot
   │
2. i2c Component Init
   │
3. display.ssd1306_i2c Init
   │
4. Esp32EyesComponent::setup()
   ├─ Create EsphomeDisplayAdapter
   ├─ Create Face(width, height)
   └─ Register g_displayAdapter globally
   │
5. Loop starts
```

### Frame Rendering Sequence

```
┌─────────────────────────────────────────┐
│  Esp32EyesComponent::loop()             │
│  Every update_interval (default 50ms)   │
└──────────────┬──────────────────────────┘
               │
               ▼
   ┌─────────────────────────┐
   │ face->Update()          │
   │ - Update timers         │
   │ - Check for blink       │
   │ - Evaluate emotions     │
   │ - Smooth transitions    │
   └──────────┬──────────────┘
              │
              ▼
   ┌─────────────────────────┐
   │ adapter->clearDisplay() │
   │ - Clear buffer          │
   └──────────┬──────────────┘
              │
              ▼
   ┌─────────────────────────┐
   │ face->Draw()            │
   │ ├─ leftEye.Draw()       │
   │ │  └─ EyeDrawer calls   │
   │ │     adapter methods   │
   │ └─ rightEye.Draw()      │
   └──────────┬──────────────┘
              │
              ▼
   ┌─────────────────────────┐
   │ display->update()       │
   │ - Transmit buffer to HW │
   └─────────────────────────┘
```

### Drawing Call Chain Example

```cpp
// In Eye::Draw()
EyeDrawer::Draw(centerX, centerY, config);

// Inside EyeDrawer::Draw() - calls adapter
adapter->drawBox(x, y, width, height);
adapter->drawTriangle(x0, y0, x1, y1, x2, y2);
adapter->drawHLine(x, y, length);

// In EsphomeDisplayAdapter::drawBox()
display->filled_rectangle(x, y, x_end, y_end, color);

// ESPHOME Display handles:
// - Color conversion
// - Coordinate validation
// - Buffer management
// - Hardware transmission
```

## Key Design Decisions

### 1. Adapter Pattern
**Why**: Decouples rendering logic from display backend
**Benefit**: Same code works with U8g2, ESPHOME Display, or custom implementations

### 2. Global Display Adapter
```cpp
extern IDisplayAdapter* g_displayAdapter;
```
**Why**: Original library uses static U8g2 instance; global adapter maintains compatibility
**Trade-off**: Not ideal for multiple displays, but solves backward compatibility

### 3. Component-Based Architecture
**Why**: Integrates cleanly with ESPHOME's component system
**Benefit**: Automatic lifecycle management, configuration parsing, Home Assistant integration

### 4. Lazy Updates
**Why**: Only redraws when `update_interval` elapsed
**Benefit**: Better performance, reduces flicker, battery-friendly

## Configuration Flow

### YAML Configuration
```yaml
esp32_eyes:
  display_id: my_display
  eye_size: 20
  emotions:
    - name: happy
      weight: 1.0
```

### Python Processing (__init__.py)
```
YAML → Python Config → CodeGen → C++ Code
```

### C++ Component Initialization
```
CONFIG dict → set_eye_size(20) → face_->EyeSize = 20
           → set_emotion(HAPPY, 1.0) → behavior_.SetEmotion(HAPPY, 1.0)
```

## Memory Layout

### Per-Component Memory
```
Esp32EyesComponent:     ~50 bytes
Face:                   ~200 bytes
Left Eye + Right Eye:   ~400 bytes
Adapters:               ~100 bytes
─────────────────────────────────
Total (rough):          ~750 bytes

Plus ESPHOME overhead:  ~1500 bytes
───────────────────────────────
Estimated total:        ~2.3 KB
```

### Display Buffer
Depends on display type:
- SSD1306 (128x64, 1 bits/pixel): 1024 bytes
- ILI9341 (240x320, RGB565): 153,600 bytes
- ST7789 (240x240, RGB565): 115,200 bytes

## Performance Characteristics

### Execution Time
```
Face::Update()          ~2-5 ms
Face::Draw()            ~5-15 ms (depends on eye_size)
Display transmission    ~20-50 ms (I2C) to ~1 ms (SPI)
───────────────────────
Total per frame:        ~30-70 ms

At 50ms update interval: ~14-20 FPS achievable on I2C
At 33ms update interval: ~15-20 FPS achievable on SPI
```

### CPU Load
- Idle: < 1% (only when update timeout reached)
- Active: 5-15% (during frame drawing)
- Full (30 FPS): 20-30% CPU usage

## Extending the Library

### Adding a New Display Backend

1. **Create Adapter Class**
   ```cpp
   class MyDisplayAdapter : public IDisplayAdapter {
   public:
       // Implement all virtual methods
   };
   ```

2. **Register in Component**
   ```cpp
   auto adapter = new MyDisplayAdapter(...);
   g_displayAdapter = adapter;
   ```

### Adding New Emotions

1. **Add to enum** in `FaceEmotions.hpp`
2. **Add preset** in `EyePresets.h`
3. **Add to Python** emotion mapping in `__init__.py`

### Custom Eye Shapes

Edit `EyePresets.h`:
```cpp
const EyeConfig CustomShape = {
    .Width = 32,
    .Height = 16,
    .Slope_Top = 0.1f,
    .Slope_Bottom = 0.0f,
    .Radius_Top = 8,
    .Radius_Bottom = 4,
    // ...
};
```

## Thread Safety

**Current Design**: Single-threaded
- All operations in ESPHOME main loop
- No concurrent access to Face or display

**If Adding Threads**:
- Protect Face state with mutex
- Don't access display adapter from other threads
- ESPHOME's loop() is not reentrant

## Known Limitations

1. **Single Display**: System designed for one display
2. **Static Adapter**: Global `g_displayAdapter` limits use cases
3. **Rendering Speed**: Complex eyes on slow I2C can be choppy
4. **Memory**: Eye configuration stored per eye (could be optimized)
5. **Color**: Binary only (suitable for 1-bit displays like OLED)

## Future Improvements

- [ ] Multi-display support
- [ ] Color emotion rendering (for RGB displays)  
- [ ] Custom animation scripts
- [ ] Blinking coordination with audio
- [ ] Gaze tracking from Home Assistant data
- [ ] Eye dilation/pupil size control
- [ ] Tear effects for emotional expressions
- [ ] Performance profiling API

## File Organization

```
Esp32-Eyes/
├── Core Rendering (Original Library)
│   ├── Face.h/cpp
│   ├── Eye.h/cpp
│   ├── EyeDrawer.h
│   ├── EyeConfig.h
│   ├── EyePresets.h
│   ├── FaceExpression.h/cpp
│   ├── FaceBehavior.h/cpp
│   ├── BlinkAssistant.h/cpp
│   ├── LookAssistant.h/cpp
│   └── ... other core files
│
├── Display Adapters (New)
│   ├── IDisplayAdapter.h
│   ├── EsphomeDisplayAdapter.h/cpp
│   └── U8g2DisplayAdapter.h
│
├── ESPHOME Integration (New)
│   ├── Esp32EyesComponent.h/cpp
│   ├── __init__.py
│   └── Common_esp32eyes.h
│
└── Documentation
    ├── README.md (original)
    ├── ESPHOME_INTEGRATION_GUIDE.md
    ├── QUICK_START.md
    ├── MIGRATION_GUIDE.md
    ├── SETUP_CHECKLIST.md
    └── ARCHITECTURE.md (this file)
```

## Related ESPHOME Components

- **display**: Base display component
- **i2c**: I2C communication (for OLED displays)
- **api**: Home Assistant integration
- **wifi**: Network connectivity
- **ota**: Over-the-air updates

## References

- ESPHOME: https://esphome.io/
- ESP32 Hardware: https://www.espressif.com/en/products/socs/esp32/
- U8g2 Library: https://github.com/olikraus/u8g2
- Original Esp32-Eyes: https://github.com/playfultechnology/esp32-eyes
