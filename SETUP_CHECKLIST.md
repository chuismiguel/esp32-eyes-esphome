# Integration Checklist for ESP32 Eyes ESPHOME Library

Use this checklist to ensure your ESPHOME ESP32 Eyes integration is set up correctly.

## Setup Verification

- [ ] Component folder located at `esphome/components/Esp32-Eyes/`
- [ ] All header files (`.h`) present
- [ ] All implementation files (`.cpp`) present
- [ ] `__init__.py` is populated (not empty)
- [ ] Original library files intact (Face.h, Eye.h, etc.)

## Configuration Checklist

- [ ] I2C configured (SDA/SCL pins)
- [ ] Display component configured with ID
- [ ] `esp32_eyes` section added with `display_id`
- [ ] `screen_width` and `screen_height` match your display
- [ ] `eye_size` is reasonable (16-24 for 128x64 displays)
- [ ] Blink/look/behavior intervals are set

## Compilation Checklist

- [ ] Project compiles without errors
- [ ] Warnings reviewed (if any)
- [ ] Correct board selected (esp32dev, esp32-s3, etc.)
- [ ] All dependencies resolved
- [ ] Binary size is acceptable

## Hardware Verification

### Display Wiring
- [ ] Display detected (check logs: "Initializing SSD1306...")
- [ ] Display shows on web interface
- [ ] No I2C communication errors in logs

### GPIO Pins
- [ ] SDA pin correct (GPIO21 default, or your chosen)
- [ ] SCL pin correct (GPIO22 default, or your chosen)
- [ ] Pins not used for other peripherals
- [ ] Pull-up resistors present (usually on display module)

## First Run Checklist

- [ ] Device powers on without crashes
- [ ] Logs show: "Setting up ESP32 Eyes component..."
- [ ] Display shows animated eyes
- [ ] Eyes respond to configuration (blink, look around)
- [ ] Web interface accessible
- [ ] API accessible (if configured)

## Network Configuration

- [ ] WiFi connects successfully
- [ ] IP address assigned
- [ ] Device appears in Home Assistant (if HA is setup)
- [ ] API encryption key configured (if needed)
- [ ] OTA password configured (if needed)

## Performance Verification

- [ ] Animation is smooth (not jerky)
- [ ] Display updates regularly
- [ ] No memory leaks indicated in logs
- [ ] Device doesn't reset unexpectedly
- [ ] Loop time is acceptable

## Debugging Tips

If something doesn't work, check:

### Eyes Not Appearing
```
Check logs for:
✓ "Display dimensions: NxM"
✓ "ESP32 Eyes component setup complete"
✓ "Setting up ESP32 Eyes component..."
```

### Animation Choppy
```
Adjust:
✓ update_interval (try 33-100 ms)
✓ CPU frequency in esp32: config
✓ eye_size (smaller = faster)
```

### I2C Errors
```
Verify:
✓ SDA/SCL pins correct
✓ Display address correct (usually 0x3C or 0x3D)
✓ Pull-up resistors present
✓ I2C frequency reasonable (100-400kHz)
```

### Compilation Errors
```
Check:
✓ Component folder structure
✓ All .cpp files present
✓ No typos in platform name
✓ Arduino.h included in files
```

## Configuration Validation

Valid emotion names:
- [ ] All emotion names match the supported list
- [ ] Weights are positive numbers
- [ ] At least one emotion configured

GPIO pins (common options):
- [ ] GPIO21/22 for I2C (default)
- [ ] No conflicts with other components
- [ ] Valid for your board type

Display dimensions:
- [ ] Correct for your display model
- [ ] eye_size not larger than screen_height/2
- [ ] screen_width >= 64, screen_height >= 32

## Final Verification

Run these checks:

1. **Web Interface Test**: Open `http://your-device.local/`
   - [ ] Page loads
   - [ ] Shows device info
   - [ ] No error messages

2. **API Test** (if configured): 
   ```bash
   curl http://your-device.local/api/info
   ```
   - [ ] Returns JSON response
   - [ ] Device listed correctly

3. **Home Assistant Integration** (if enabled):
   - [ ] Device appears in HA
   - [ ] Can control entities
   - [ ] Responds to commands

4. **Stress Test**:
   - [ ] Leave running for 1 hour
   - [ ] Check for memory leaks
   - [ ] Monitor free heap
   - [ ] No unexpected resets

## Troubleshooting Reference

| Issue | Check | Solution |
|-------|-------|----------|
| Display dark/no change | Display ID correct? | Verify `display_id` reference |
| Eyes very small | eye_size too small? | Increase to 20-24 |
| Animation jerky | update_interval too low? | Increase to 50-100ms |
| Memory errors | Too many emotions? | Reduce emotion count |
| I2C errors | Right pins? | Check GPIO assignments |
| Won't compile | Missing files? | Verify Esp32-Eyes folder complete |

## Support Resources

- Main Documentation: [ESPHOME_INTEGRATION_GUIDE.md](ESPHOME_INTEGRATION_GUIDE.md)
- Quick Start: [QUICK_START.md](QUICK_START.md)
- Examples: [examples.py](examples.py)
- Migration Help: [MIGRATION_GUIDE.md](MIGRATION_GUIDE.md)
- ESPHOME Docs: https://esphome.io/
- Original Library: https://github.com/playfultechnology/esp32-eyes

## Notes for Your Setup

Write anything specific to your setup:

```
Board: ___________________
Display Type: ___________________
Display Resolution: ___________________
I2C Address: ___________________
SDA Pin: ___________________
SCL Pin: ___________________
Target FPS: ___________________
```
