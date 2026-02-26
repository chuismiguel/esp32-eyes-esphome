# ESP32 Eyes ESPHOME Integration Guide

## Overview

This guide explains how to use the ESP32 Eyes library with ESPHOME's Display component, enabling you to create expressive animated eyes on any display supported by ESPHOME.

## What This Library Provides

The ESP32 Eyes ESPHOME integration bridges the powerful, expressive eye animation library with ESPHOME's flexible display ecosystem. Key features include:

- **Dynamic eye rendering** - Eyes drawn programmatically (not bitmap-based) with customizable shapes
- **18 different emotions** - Happy, sad, angry, surprised, loving, and more
- **Smooth animations** - Automatic blinking, looking around, smooth transitions
- **Smart behavior system** - Weighted emotion selection for natural expression
- **Full ESPHOME integration** - Configure via YAML, control via Home Assistant, API

## Architecture

### Component Structure

```
ESP32 Eyes ESPHOME Library
├── Display Adapter Layer
│   ├── IDisplayAdapter (interface)
│   ├── EsphomeDisplayAdapter (ESPHOME implementation)
│   └── U8g2DisplayAdapter (U8g2 implementation)
├── Core Rendering (ESP32-Eyes)
│   ├── Face (manages left/right eyes)
│   ├── Eye (individual eye rendering)
│   ├── EyeDrawer (drawing algorithms)
│   └── FaceExpression (emotion management)
└── ESPHOME Integration
    ├── Esp32EyesComponent (main component)
    └── __init__.py (ESPHOME configuration)
```

### Design Pattern: Display Adapter

The library uses an **Adapter Pattern** to abstract away display-specific code:

```
ESP32-Eyes (drawing logic)
         ↓
IDisplayAdapter (interface)
         ↓
EsphomeDisplayAdapter → ESPHOME Display API
```

This allows the same eye rendering code to work with different display backends.

## Installation

### Step 1: Add to Your ESPHOME Config

Place the `Esp32-Eyes` folder in your ESPHOME configuration's `components` directory:

```
esphome/
├── config/
│   └── my_device.yaml
└── components/
    └── Esp32-Eyes/
        ├── __init__.py
        ├── *.h/*.cpp (component files)
        └── ... (other library files)
```

### Step 2: Basic Configuration

Add to your ESPHOME YAML:

```yaml
display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: oled_display

esp32_eyes:
  display_id: oled_display
  screen_width: 128
  screen_height: 64
  eye_size: 20
```

### Step 3: Compile and Flash

```bash
esphome run my_device.yaml
```

## Configuration Options

### Display Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `display_id` | ID | **required** | Reference to the display component |
| `screen_width` | int | 128 | Display width in pixels |
| `screen_height` | int | 64 | Display height in pixels |
| `eye_size` | int | 20 | Diameter of each eye in pixels |
| `eye_distance` | int | 4 | Gap between the two eyes |

### Performance Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `update_interval` | int | 50 | Redraw interval in milliseconds (50ms ≈ 20 FPS) |

### Behavior Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `random_behavior` | bool | true | Randomly change emotions |
| `random_blink` | bool | true | Automatically blink eyes |
| `random_look` | bool | true | Randomly look around screen |

### Animation Intervals

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `blink_interval` | int | 3000 | Milliseconds between blinks |
| `look_interval` | int | 2000 | Milliseconds between look changes |
| `behavior_interval` | int | 5000 | Milliseconds between emotion changes |

### Emotions Configuration

Define which emotions are active and their relative weights:

```yaml
esp32_eyes:
  emotions:
    - name: normal
      weight: 1.0
    - name: happy
      weight: 0.8
    - name: sad
      weight: 0.3
```

**Available Emotions:**
- normal (neutral)
- happy
- sad
- angry
- surprised
- fearful
- disgusted
- glee
- content
- relaxed
- focused
- confused
- frustrated
- determined
- concerned
- expectant
- joyful
- loving

Weight higher values for emotions you want to appear more frequently. Emotions are randomly selected based on their relative weights.

## Complete Example

```yaml
esphome:
  name: living-room-eyes

esp32:
  board: esp32dev

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

api:
  encryption:
    key: !secret api_encryption_key

ota:
  password: !secret ota_password

logger:

i2c:
  sda: GPIO21
  scl: GPIO22
  frequency: 400kHz

display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: oled_display

esp32_eyes:
  display_id: oled_display
  screen_width: 128
  screen_height: 64
  eye_size: 22
  eye_distance: 5
  
  # Update at 20 FPS
  update_interval: 50
  
  # Enable all automatic behaviors
  random_behavior: true
  random_blink: true
  random_look: true
  
  # Natural timing
  blink_interval: 3000
  look_interval: 2500
  behavior_interval: 5000
  
  # Emotional range
  emotions:
    - name: normal
      weight: 1.5
    - name: happy
      weight: 1.2
    - name: content
      weight: 1.0
    - name: loving
      weight: 0.8
    - name: surprised
      weight: 0.6
    - name: sad
      weight: 0.4
```

## Performance Tuning

### For Smooth Animation (30+ FPS)

```yaml
esp32:
  cpu_freq: 240MHz  # Max CPU frequency

i2c:
  frequency: 1MHz  # Fast I2C

esp32_eyes:
  update_interval: 33  # ~30 FPS
  eye_size: 24
```

### For Low Power (5-10 FPS)

```yaml
esp32:
  cpu_freq: 80MHz  # Low CPU frequency

i2c:
  frequency: 100kHz  # Slow I2C

esp32_eyes:
  update_interval: 100  # ~10 FPS
  eye_size: 18
  random_look: false  # Disable to save power
```

### Memory Considerations

- **Face object**: ~2-3 KB
- **Display adapter**: ~1 KB
- **Per-frame display buffer**: Depends on display type

The component is designed to work on standard ESP32s with 320KB+ of stack memory.

## Controlling Eyes via Home Assistant

Once integrated with Home Assistant via ESPHOME, you can control the eyes through the API.

### Example: Service Call

```yaml
service: esphome.esp32_eyes_look_at
data:
  device_id: esp32_eyes_display
  x: 0.5      # -1.0 (left) to 1.0 (right)
  y: 0.0      # -1.0 (top) to 1.0 (bottom)
```

### Available Service Commands

- **Look direction**: `look_at(x, y)`, `look_left()`, `look_right()`, `look_top()`, `look_bottom()`, `look_front()`
- **Blink**: `do_blink()`
- **Emotion control**: `set_emotion(emotion_id, weight)`
- **Behavior toggles**: `set_random_behavior()`, `set_random_blink()`, `set_random_look()`

## Development Notes

### Display Adapter Pattern

The library uses an adapter pattern to support multiple display backends:

```cpp
// IDisplayAdapter - The interface
class IDisplayAdapter {
public:
    virtual void drawHLine(...) = 0;
    virtual void drawBox(...) = 0;
    virtual void drawTriangle(...) = 0;
    // ... more methods
};

// EsphomeDisplayAdapter - Implementation for ESPHOME
class EsphomeDisplayAdapter : public IDisplayAdapter {
    // Translates calls to ESPHOME Display API
};
```

### Adding a New Display Backend

To support a new display library:

1. Create a new adapter class inheriting from `IDisplayAdapter`
2. Implement all pure virtual methods
3. Translate calls to your display's API
4. Compile with `-DUSE_YOUR_DISPLAY_ADAPTER`

### Modifying Eye Shape

Edit `EyePresets.h` to customize the eye shapes for each emotion:

```cpp
const EyeConfig Happy = {
    .Width = 32,
    .Height = 16,
    .Slope_Top = 0.2f,
    .Slope_Bottom = 0.2f,
    .Radius_Top = 8,
    .Radius_Bottom = 8,
    // ... other parameters
};
```

### Performance Profiling

Monitor these metrics:

- **Frame time**: Should be < `update_interval`
- **Memory usage**: `free_heap` in logs
- **Display refresh rate**: Compare expected FPS with observed smoothness

## Troubleshooting

### Eyes Not Appearing

1. **Check display is working** - Verify the display component is configured and working
2. **Check display ID** - Ensure `display_id` matches your display component's ID
3. **Check screen dimensions** - Make sure `screen_width` and `screen_height` match your display
4. **Check logs** - ESPHome logs show setup status

### Jerky Animation

1. **Increase update_interval** - Lower values = higher FPS (try values between 30-50ms)
2. **Reduce eye_size** - Larger eyes take longer to draw
3. **Disable random_look** - Reduces computation load
4. **Increase CPU frequency** - Set `esp32: cpu_freq: 240MHz`

### Display Flickering

1. **Use double buffering** - Most ESPHOME displays support this automatically
2. **Reduce update frequency** - Try `update_interval: 100`
3. **Check I2C frequency** - Default 400kHz usually works; try lower if unstable

### Memory Issues

1. **Simplify emotions** - Remove unused emotions from configuration
2. **Reduce eye_size** - Smaller eyes require less computation
3. **Monitor free heap** - Check logs for heap space

## Files Included

| File | Purpose |
|------|---------|
| `IDisplayAdapter.h` | Abstract display interface |
| `EsphomeDisplayAdapter.h/cpp` | ESPHOME Display implementation |
| `U8g2DisplayAdapter.h` | U8g2 library support |
| `Esp32EyesComponent.h/cpp` | Main ESPHOME component |
| `__init__.py` | ESPHOME integration |
| All original Esp32-Eyes files | Core rendering logic |

## References

- [Original Esp32-Eyes Library](https://github.com/playfultechnology/esp32-eyes)
- [ESPHOME DisplayComponent Documentation](https://esphome.io/components/display/index.html)
- [ESPHOME Component Development](https://esphome.io/components/index.html)

## License

This integration maintains the same license as the original ESP32-Eyes library (AGPL-3.0).

## Support

For issues or questions:

1. Check the [ESPHOME Component Development Guide](https://esphome.io/components/)
2. Review the example configurations in `examples.py`
3. Check the logs for compilation/runtime errors
4. Verify hardware connections (I2C, display wiring)
