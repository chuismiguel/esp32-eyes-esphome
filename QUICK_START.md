# ESP32 Eyes ESPHOME Quick Start

## 5-Minute Setup

### 1. Copy Component to ESPHOME

Ensure the `Esp32-Eyes` directory is in your ESPHOME components folder:
```
esphome/components/Esp32-Eyes/
```

### 2. Add to Your YAML

```yaml
i2c:
  sda: GPIO21
  scl: GPIO22

display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: my_display

esp32_eyes:
  display_id: my_display
```

### 3. Compile & Flash

```bash
esphome run my_device.yaml
```

That's it! You should see animated eyes on your display.

## Common Customizations

### Change Eye Size
```yaml
esp32_eyes:
  display_id: my_display
  eye_size: 18  # Smaller eyes
```

### Slower/Faster Animation
```yaml
esp32_eyes:
  display_id: my_display
  update_interval: 100  # Slower (10 FPS)
  # or
  update_interval: 33   # Faster (30 FPS)
```

### Disable Random Behavior
```yaml
esp32_eyes:
  display_id: my_display
  random_behavior: false
  random_blink: false
  random_look: false
```

### Add Emotions
```yaml
esp32_eyes:
  display_id: my_display
  emotions:
    - name: normal
      weight: 1.0
    - name: happy
      weight: 1.0
    - name: sad
      weight: 0.5
```

## Supported Displays

Any display supported by ESPHOME (SSD1306, ILI9341, ST7789, etc.) can be used with this component:

```yaml
# OLED I2C
display:
  - platform: ssd1306_i2c
    id: my_display

# OLED SPI  
display:
  - platform: ssd1306_spi
    id: my_display

# LCD SPI
display:
  - platform: ili9341
    id: my_display

# Use any of these with esp32_eyes component
esp32_eyes:
  display_id: my_display
```

## GPIO Wiring

### I2C OLED (SSD1306)
- VCC → 3.3V
- GND → GND
- SDA → GPIO21 (configurable)
- SCL → GPIO22 (configurable)

### SPI Display
Refer to ESPHOME display documentation for your specific display.

## Next Steps

- See [ESPHOME_INTEGRATION_GUIDE.md](ESPHOME_INTEGRATION_GUIDE.md) for full documentation
- Check `examples.py` for more configuration examples
- See [Original README.md](esphome/components/Esp32-Eyes/README.md) for Esp32-Eyes library details
