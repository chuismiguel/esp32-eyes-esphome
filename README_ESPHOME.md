# ESP32 Eyes ESPHOME Integration

Professional animated eyes for your ESPHOME display!

> Transform any ESPHOME-compatible display into expressive, animated eyes with 18 different emotions, smooth animations, and full Home Assistant integration.

## 🎯 What This Is

A complete ESPHOME library that brings the powerful [ESP32-Eyes](https://github.com/playfultechnology/esp32-eyes) animation engine to ESPHOME's display ecosystem.

**Key Features:**
- 🎭 18 different emotions with smooth transitions
- 👁️ Programmatic eye rendering (not bitmaps)
- 👀 Automatic/manual blinking and looking around
- 🎨 Works with any ESPHOME-supported display
- 🏠 Full Home Assistant integration
- ⚙️ YAML-based configuration (no code required)
- 🚀 OTA updates and web interface

## ⚡ 30-Second Quick Start

### 1. Copy the Component
```bash
cp -r Esp32-Eyes/ esphome/components/
```

### 2. Add to Your YAML
```yaml
display:
  - platform: ssd1306_i2c
    id: oled

esp32_eyes:
  display_id: oled
```

### 3. Compile & Flash
```bash
esphome run my_device.yaml
```

**Done!** Animated eyes appear on your display. ✨

## 📚 Documentation

Start with the right guide for your needs:

| Goal | Document | Time |
|------|----------|------|
| **Get started now** | [QUICK_START.md](QUICK_START.md) | 5 min |
| **Complete reference** | [ESPHOME_INTEGRATION_GUIDE.md](ESPHOME_INTEGRATION_GUIDE.md) | 20 min |
| **Migrating from U8g2** | [MIGRATION_GUIDE.md](MIGRATION_GUIDE.md) | 10 min |
| **Setup verification** | [SETUP_CHECKLIST.md](SETUP_CHECKLIST.md) | 10 min |
| **Architecture details** | [ARCHITECTURE.md](ARCHITECTURE.md) | 15 min |
| **Configuration examples** | [examples.py](examples.py) | 5 min |
| **Full overview** | [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) | 10 min |

## 🔧 Full Configuration Example

```yaml
esphome:
  name: my-esp32-eyes

esp32:
  board: esp32dev

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

api:
api_encryption:
    key: !secret api_encryption_key

ota:
  password: !secret ota_password

logger:

# Hardware setup
i2c:
  sda: GPIO21
  scl: GPIO22

# Display
display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: oled_display

# Animated eyes!
esp32_eyes:
  display_id: oled_display
  screen_width: 128
  screen_height: 64
  eye_size: 22
  
  # Performance
  update_interval: 50  # ~20 FPS
  
  # Behavior
  random_behavior: true
  random_blink: true
  random_look: true
  
  # Timing
  blink_interval: 3000      # Every 3 seconds
  look_interval: 2500       # Every 2.5 seconds
  behavior_interval: 5000   # Every 5 seconds
  
  # Emotions
  emotions:
    - name: normal
      weight: 1.5
    - name: happy
      weight: 1.2
    - name: sad
      weight: 0.5
    - name: surprised
      weight: 0.8
```

## 🖧 Supported Displays

Any display supported by ESPHOME:
- ✅ **OLED I2C** - SSD1306, SH1106, etc.
- ✅ **OLED SPI** - SSD1306 SPI variants
- ✅ **LCD TFT** - ILI9341, ST7789, ST7735, etc.
- ✅ **E-Ink** - Where supported by ESPHOME

## 🎭 Available Emotions

The library includes 18 presets:
normal • happy • sad • angry • surprised • fearful • disgusted • glee • content • relaxed • focused • confused • frustrated • determined • concerned • expectant • joyful • loving

## 🏠 Home Assistant Integration

Once connected, control eyes from Home Assistant:

```yaml
# Service calls
service: esphome.my_device_look_left
service: esphome.my_device_do_blink
service: esphome.my_device_set_emotion
```

## 🔨 Architecture Highlights

The library uses a **Display Adapter Pattern** for flexibility:

```
ESP32-Eyes Library
       ↓
IDisplayAdapter (Abstract Interface)
       ↓
EsphomeDisplayAdapter → ESPHOME Display API
   OR
U8g2DisplayAdapter → U8g2 Library
```

This allows the same rendering logic to work with different display backends.

## 📁 What's Included

```
esp32-eyes-esphome/
├── Documentation/
│   ├── QUICK_START.md                 ← Start here
│   ├── ESPHOME_INTEGRATION_GUIDE.md    ← Full reference
│   ├── MIGRATION_GUIDE.md              ← From U8g2
│   ├── ARCHITECTURE.md                 ← Technical details
│   └── ... (more docs)
│
├── esphome/components/Esp32-Eyes/
│   ├── Core Rendering (Original Library)
│   │   ├── Face.h/cpp
│   │   ├── Eye.h/cpp
│   │   ├── EyeDrawer.h
│   │   └── ... (animation classes)
│   │
│   ├── New Display Abstraction
│   │   ├── IDisplayAdapter.h
│   │   ├── EsphomeDisplayAdapter.h/cpp
│   │   └── U8g2DisplayAdapter.h
│   │
│   └── ESPHOME Integration
│       ├── Esp32EyesComponent.h/cpp
│       └── __init__.py
│
└── examples.py                         ← Configuration examples
```

## ⚙️ Configuration Options

### Display Settings
| Option | Default | Description |
|--------|---------|-------------|
| `display_id` | **required** | Reference to display component |
| `screen_width` | 128 | Display width in pixels |
| `screen_height` | 64 | Display height in pixels |
| `eye_size` | 20 | Eye diameter in pixels |
| `eye_distance` | 4 | Gap between eyes |

### Performance
| Option | Default | Description |
|--------|---------|-------------|
| `update_interval` | 50 | Redraw interval (ms) |

### Behavior
| Option | Default | Description |
|--------|---------|-------------|
| `random_behavior` | true | Random emotion changes |
| `random_blink` | true | Auto blink |
| `random_look` | true | Random looking around |

### Timing
| Option | Default | Description |
|--------|---------|-------------|
| `blink_interval` | 3000 | Blink period (ms) |
| `look_interval` | 2000 | Look change period (ms) |
| `behavior_interval` | 5000 | Emotion change period (ms) |

## 📊 Performance

- **Memory**: ~2.3 KB component overhead
- **CPU**: 5-15% during animation
- **Frame Time**: 30-70ms with I2C display
- **Update Rate**: 10-30 FPS (configurable)

## 🚀 Getting Started

1. **Read**: [QUICK_START.md](QUICK_START.md) (5 minutes)
2. **Setup**: Copy component to `esphome/components/`
3. **Configure**: Add `esp32_eyes` section to YAML
4. **Build**: `esphome run my_device.yaml`
5. **Enjoy**: Watch your eyes animate!

## 🆘 Troubleshooting

**Eyes not appearing?**
- Check `display_id` matches your display component
- Verify `screen_width` and `screen_height`
- Review logs for errors

**Animation choppy?**
- Decrease `update_interval` (try 30-50)
- Increase `eye_size` (starts at 20)
- Enable higher CPU frequency

**Memory issues?**
- Reduce emotion count
- Decrease `eye_size`
- Lower update frequency

See [SETUP_CHECKLIST.md](SETUP_CHECKLIST.md) for complete troubleshooting.

## 💡 Examples

### Expressive Face
```yaml
esp32_eyes:
  display_id: oled
  emotions:
    - name: happy
      weight: 2.0
    - name: loving
      weight: 1.5
    - name: content
      weight: 1.0
```

### Calm Display
```yaml
esp32_eyes:
  display_id: oled
  random_look: false
  blink_interval: 5000
  emotions:
    - name: relaxed
      weight: 1.0
    - name: content
      weight: 1.0
```

### High Performance
```yaml
esp32:
  cpu_freq: 240MHz

esp32_eyes:
  display_id: oled
  update_interval: 33     # 30 FPS
  eye_size: 24
```

See [examples.py](examples.py) for more configurations.

## 📖 Original Library

This integration builds on the excellent [esp32-eyes](https://github.com/playfultechnology/esp32-eyes) library by Alastair Aitchison and Luis Llamas, adding ESPHOME integration while preserving all original functionality.

## 📄 License

Maintains the same license as ESP32-Eyes (AGPL-3.0).

## 🤝 Contributing

Found an issue? Have a suggestion? The library is well-documented and extensible:

- **Bug Reports**: Include logs and configuration
- **Feature Requests**: Check if it's supported in ESPHOME
- **Custom Adapters**: Implement `IDisplayAdapter`

## 📞 Support

1. **Quick answers**: Check [QUICK_START.md](QUICK_START.md)
2. **Complete guide**: See [ESPHOME_INTEGRATION_GUIDE.md](ESPHOME_INTEGRATION_GUIDE.md)
3. **Troubleshooting**: Review [SETUP_CHECKLIST.md](SETUP_CHECKLIST.md)
4. **Architecture**: Understand [ARCHITECTURE.md](ARCHITECTURE.md)

## 🎯 Next Steps

- [ ] Copy `Esp32-Eyes/` to `esphome/components/`
- [ ] Add `esp32_eyes` to your YAML
- [ ] Build and flash: `esphome run my_device.yaml`
- [ ] Watch your eyes animate! 👀

---

**Ready to get started?** → [QUICK_START.md](QUICK_START.md)

**Want more details?** → [ESPHOME_INTEGRATION_GUIDE.md](ESPHOME_INTEGRATION_GUIDE.md)

**Need help?** → [SETUP_CHECKLIST.md](SETUP_CHECKLIST.md)
