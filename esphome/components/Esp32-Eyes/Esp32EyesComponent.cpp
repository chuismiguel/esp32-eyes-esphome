/***************************************************
ESP32 Eyes ESPHOME Component - Implementation
***************************************************/

#ifdef USE_ESPHOME_DISPLAY

#include "Esp32EyesComponent.h"
#include "esphome/core/log.h"

namespace esphome {
namespace esp32_eyes {

static const char *const TAG = "esp32_eyes";

// Global display adapter instance
IDisplayAdapter* g_displayAdapter = nullptr;

Esp32EyesComponent::Esp32EyesComponent(display::Display* display)
    : display_(display),
      display_adapter_(nullptr),
      face_(nullptr),
      screen_width_(128),
      screen_height_(64),
      eye_size_(20),
      update_interval_(50),  // 20 FPS default
      last_update_(0) {}

void Esp32EyesComponent::setup() {
    ESP_LOGI(TAG, "Setting up ESP32 Eyes component...");
    
    if (!display_) {
        ESP_LOGE(TAG, "Display is not configured!");
        return;
    }
    
    // Get actual display dimensions
    screen_width_ = display_->get_width();
    screen_height_ = display_->get_height();
    
    ESP_LOGI(TAG, "Display dimensions: %dx%d", screen_width_, screen_height_);
    
    // Create display adapter
    display_adapter_ = new EsphomeDisplayAdapter(display_);
    g_displayAdapter = display_adapter_;
    
    // Create Face object
    face_ = new Face(screen_width_, screen_height_, eye_size_);
    
    // Set default emotions with weights
    // You can configure these in the YAML
    face_->Behavior.SetEmotion(eEmotions::Normal, 1.0f);
    face_->Behavior.SetEmotion(eEmotions::Happy, 0.5f);
    face_->Behavior.SetEmotion(eEmotions::Sad, 0.3f);
    
    // Configure timers
    face_->Blink.Timer.SetIntervalMillis(3000);  // Blink every 3 seconds
    face_->Look.Timer.SetIntervalMillis(2000);   // Look around every 2 seconds
    face_->Behavior.Timer.SetIntervalMillis(5000);  // Change emotion every 5 seconds
    
    ESP_LOGI(TAG, "ESP32 Eyes component setup complete");
}

void Esp32EyesComponent::loop() {
    if (!face_ || !display_) {
        return;
    }
    
    uint32_t now = millis();
    
    // Update face at configured interval
    if (now - last_update_ >= update_interval_) {
        last_update_ = now;
        
        // Update face state
        face_->Update();
        
        // Clear and redraw display
        if (display_adapter_) {
            display_adapter_->clearDisplay();
        }
        
        // Draw the face
        face_->Draw();
        
        // Send buffer to display
        if (display_adapter_) {
            display_adapter_->sendBuffer();
        }
        display_->update();
    }
}

void Esp32EyesComponent::dump_config() {
    ESP_LOGCONFIG(TAG, "ESP32 Eyes Component:");
    ESP_LOGCONFIG(TAG, "  Display: %s", display_->get_name().c_str());
    ESP_LOGCONFIG(TAG, "  Screen Size: %dx%d", screen_width_, screen_height_);
    ESP_LOGCONFIG(TAG, "  Eye Size: %d", eye_size_);
    ESP_LOGCONFIG(TAG, "  Update Interval: %d ms", update_interval_);
}

float Esp32EyesComponent::get_setup_priority() const {
    // Should setup after display component
    return setup_priority::PROCESSOR;
}

}  // namespace esp32_eyes
}  // namespace esphome

#endif  // USE_ESPHOME_DISPLAY
