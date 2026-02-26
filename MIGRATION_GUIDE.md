# Migration Guide: From U8g2 to ESPHOME Display

If you have existing code using the Esp32-Eyes library with U8g2, this guide explains how to migrate to the ESPHOME Display integration.

## Why Migrate?

### Benefits of ESPHOME Integration

✅ **No direct display initialization** - ESPHOME handles setup
✅ **Home Assistant integration** - Control eyes via HA
✅ **Multiple display support** - Works with any ESPHOME-supported display
✅ **Web interface** - Configure without recompiling
✅ **OTA updates** - Update over the air
✅ **Cleaner configuration** - YAML-based setup
✅ **Better maintainability** - Decoupled from display hardware

## Before: U8g2 Approach

```cpp
#include <U8g2lib.h>
#include "Face.h"

// U8g2 needs explicit initialization
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA);
Face* face;

void setup() {
  u8g2.begin();
  face = new Face(128, 64, 20);
}

void loop() {
  u8g2.clearBuffer();
  face->Update();
  face->Draw();
  u8g2.sendBuffer();
}
```

## After: ESPHOME Approach

```yaml
# All hardware setup is declarative in YAML
i2c:
  sda: GPIO21
  scl: GPIO22

display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: my_display

# Component manages everything
esp32_eyes:
  display_id: my_display
  screen_width: 128
  screen_height: 64
  eye_size: 20
```

## Step 1: Remove U8g2 Code

Delete or comment out:
- U8g2 initialization code
- Manual display setup
- Display refresh loops
- Manual buffer management

## Step 2: Create ESPHOME Configuration

Create `my_device.yaml`:

```yaml
esphome:
  name: my-esp32-eyes

esp32:
  board: esp32dev

# Keep your original setup...
wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

api:
api_encryption:
    key: !secret api_encryption_key

# Add I2C and Display
i2c:
  sda: GPIO21
  scl: GPIO22

display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: oled_display

# Add the component
esp32_eyes:
  display_id: oled_display
```

## Step 3: Update Emotion Configuration

### Before (in C++ code)
```cpp
face->Behavior.SetEmotion(eEmotions::Happy, 1.0);
face->Behavior.SetEmotion(eEmotions::Sad, 0.5);
```

### After (in YAML)
```yaml
esp32_eyes:
  emotions:
    - name: happy
      weight: 1.0
    - name: sad
      weight: 0.5
```

## Step 4: Update Timing Configuration

### Before (in C++)
```cpp
face->Blink.Timer.SetIntervalMillis(3000);
face->Look.Timer.SetIntervalMillis(2000);
face->Behavior.Timer.SetIntervalMillis(5000);
```

### After (in YAML)
```yaml
esp32_eyes:
  blink_interval: 3000
  look_interval: 2000
  behavior_interval: 5000
```

## Step 5: Compile and Flash

```bash
esphome run my_device.yaml
```

## Key Differences

| Aspect | U8g2 | ESPHOME |
|--------|------|---------|
| **Configuration** | C++ code | YAML |
| **Hardware Setup** | Manual | Automatic |
| **Display Init** | Explicit | Via component |
| **Update Loop** | Manual `loop()` | Automatic `loop()` override |
| **Buffer Mgmt** | Manual `clearBuffer()/sendBuffer()` | Automatic |
| **Integration** | Standalone | Full ESPHOME ecosystem |

## Advanced Migration: Custom Display Backend

If you're using a custom display library neither U8g2 nor ESPHOME's defaults:

1. Create a custom adapter:

```cpp
class MyDisplayAdapter : public IDisplayAdapter {
public:
    MyDisplayAdapter(MyDisplay* disp) : display_(disp) {}
    
    void drawHLine(int16_t x, int16_t y, int16_t len) override {
        // Translate to your display API
        display_->hline(x, y, len);
    }
    
    // ... implement other methods
    
private:
    MyDisplay* display_;
};
```

2. Register in your component:

```cpp
auto adapter = new MyDisplayAdapter(my_display);
g_displayAdapter = adapter;
```

## Troubleshooting Migration

### "Display component not found"
- Make sure your display component has an ID
- Use that ID in `esp32_eyes: display_id: your_id`

### "Eyes not appearing"
- Check that your `esp32_eyes` section has correct display_id
- Verify display works independently first
- Check screen_width and screen_height match your actual display

### "Compilation fails"
- Ensure Esp32-Eyes component folder is in `esphome/components/`
- Check that display platform is supported by ESPHOME
- Review compilation errors in detail

### "Animation choppy"
- Decrease `update_interval` value
- Increase ESP32 CPU frequency
- Reduce `eye_size`

## Taking Advantage of ESPHOME Features

Once migrated, you can use:

### Home Assistant Automation
```yaml
automation:
  - trigger: time
    at: "18:00"
    action:
      - service: esphome.my_device_look_left
```

### REST API Control
```bash
curl -X POST http://my-esp-device.local/api/esp32_eyes/look_at \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -d '{"x": 0.5, "y": 0}'
```

### Web Dashboard
Access at: `http://my-esp-device.local/` to see live controls

## Rollback Plan

If you need to go back to U8g2:

1. Save your `my_device.yaml` for reference
2. Restore your original U8g2 C++ code
3. Keep only the essential ESPHOME parts (wifi, api, ota)
4. Remove the `esp32_eyes` component section

## Getting Help

- Check [ESPHOME_INTEGRATION_GUIDE.md](ESPHOME_INTEGRATION_GUIDE.md) for detailed documentation
- View [examples.py](examples.py) for configuration examples
- Review ESPHOME official documentation for display setup
