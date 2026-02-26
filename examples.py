#!/usr/bin/env python3
"""
ESP32 Eyes ESPHOME Library - Example Configurations

This file contains example YAML configurations for using the ESP32 Eyes
library with ESPHOME Display components.
"""

# Example 1: Basic Display with I2C OLED
basic_config = """
esphome:
  name: esp32-eyes-display

esp32:
  board: esp32dev

# I2C setup for OLED display
i2c:
  sda: GPIO21
  scl: GPIO22
  frequency: 400kHz

# Display component
display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: esp32_display

# ESP32 Eyes component
esp32_eyes:
  id: eyes
  display_id: esp32_display
  screen_width: 128
  screen_height: 64
  eye_size: 20
  eye_distance: 4
  
  # Update frequency (ms)
  update_interval: 50
  
  # Behavior settings
  random_behavior: true
  random_blink: true
  random_look: true
  
  # Timing intervals
  blink_interval: 3000
  look_interval: 2000
  behavior_interval: 5000
  
  # Emotion weights
  emotions:
    - name: normal
      weight: 1.0
    - name: happy
      weight: 0.8
    - name: sad
      weight: 0.3
    - name: angry
      weight: 0.2
    - name: surprised
      weight: 0.5
"""

# Example 2: Advanced configuration with Home Assistant integration
home_assistant_config = """
esphome:
  name: esp32-eyes-ha

esp32:
  board: esp32dev

# Home Assistant API
api:
  encryption:
    key: !secret api_encryption_key

ota:
  password: !secret ota_password

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  
  # Enable fallback hotspot
  ap:
    ssid: "ESP32-Eyes Fallback"
    password: !secret ap_password

captive_portal:

logger:

# I2C setup
i2c:
  sda: GPIO21
  scl: GPIO22
  frequency: 400kHz

# Display component
display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: esp32_display

# ESP32 Eyes with sensible defaults
esp32_eyes:
  id: eyes
  display_id: esp32_display
  
  # Face dimensions
  screen_width: 128
  screen_height: 64
  eye_size: 22
  eye_distance: 6
  
  # Rendering performance
  update_interval: 50  # ~20 FPS
  
  # Behavior toggles that can be controlled via Home Assistant
  random_behavior: true
  random_blink: true
  random_look: true
  
  # Comfortable interaction timings
  blink_interval: 3000   # Blink every 3 seconds
  look_interval: 2500    # Look around every 2.5 seconds
  behavior_interval: 4000  # Change emotion every 4 seconds
  
  # Define emotional range
  emotions:
    - name: normal
      weight: 1.5
    - name: happy
      weight: 1.2
    - name: sad
      weight: 0.6
    - name: angry
      weight: 0.4
    - name: surprised
      weight: 0.8
    - name: fearful
      weight: 0.3
    - name: content
      weight: 1.0
"""

# Example 3: High-frequency rendering for more fluid animation
high_performance_config = """
esphome:
  name: esp32-eyes-performance

esp32:
  board: esp32dev

# Increase CPU frequency for smoother rendering
esp32:
  cpu_freq: 240MHz

i2c:
  sda: GPIO21
  scl: GPIO22
  frequency: 1MHz  # Higher I2C frequency for better display updates

display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: esp32_display

esp32_eyes:
  id: eyes
  display_id: esp32_display
  
  screen_width: 128
  screen_height: 64
  eye_size: 24
  eye_distance: 3
  
  # Higher update frequency for smoother animation
  update_interval: 33  # ~30 FPS
  
  # More frequent behavior updates for liveliness
  random_behavior: true
  random_blink: true
  random_look: true
  
  blink_interval: 2000   # More frequent blinking
  look_interval: 1500    # More frequent looking around
  behavior_interval: 3000  # Faster emotion changes
  
  emotions:
    - name: normal
      weight: 1.0
    - name: happy
      weight: 1.0
    - name: content
      weight: 0.8
    - name: focused
      weight: 0.6
"""

# Example 4: Low-power configuration
low_power_config = """
esphome:
  name: esp32-eyes-lowpower

esp32:
  board: esp32dev
  # Lower CPU frequency to save power
  cpu_freq: 80MHz

i2c:
  sda: GPIO21
  scl: GPIO22
  frequency: 100kHz

display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: esp32_display
    # Reduce display update frequency
    update_interval: 500ms

esp32_eyes:
  id: eyes
  display_id: esp32_display
  
  screen_width: 128
  screen_height: 64
  eye_size: 18
  eye_distance: 4
  
  # Lower update frequency
  update_interval: 100  # ~10 FPS
  
  random_behavior: true
  random_blink: true
  random_look: false  # Disable random looking to save power
  
  # Less frequent updates
  blink_interval: 4000
  look_interval: 0  # Disabled
  behavior_interval: 8000
  
  emotions:
    - name: normal
      weight: 1.0
    - name: content
      weight: 0.8
    - name: relaxed
      weight: 0.6
"""

if __name__ == "__main__":
    print("ESP32 Eyes ESPHOME Library - Example Configurations")
    print("=" * 60)
    print("\n1. BASIC CONFIGURATION")
    print("-" * 60)
    print(basic_config)
    print("\n2. HOME ASSISTANT INTEGRATION")
    print("-" * 60)
    print(home_assistant_config)
    print("\n3. HIGH-PERFORMANCE CONFIGURATION")
    print("-" * 60)
    print(high_performance_config)
    print("\n4. LOW-POWER CONFIGURATION")
    print("-" * 60)
    print(low_power_config)
