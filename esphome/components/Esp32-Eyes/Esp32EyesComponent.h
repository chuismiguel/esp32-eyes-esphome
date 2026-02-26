/***************************************************
ESP32 Eyes ESPHOME Component
Main component class that integrates Face rendering with ESPHOME Display
***************************************************/

#ifdef USE_ESPHOME_DISPLAY

#ifndef _ESP32_EYES_ESPHOME_COMPONENT_h
#define _ESP32_EYES_ESPHOME_COMPONENT_h

#include "esphome/core/component.h"
#include "esphome/components/display/display.h"
#include "Face.h"
#include "EsphomeDisplayAdapter.h"

namespace esphome {
namespace esp32_eyes {

class Esp32EyesComponent : public Component {
public:
    Esp32EyesComponent(display::Display* display);
    
    // Component lifecycle
    void setup() override;
    void loop() override;
    void dump_config() override;
    
    // Face control methods
    Face* get_face() { return face_; }
    
    // Configuration setters
    void set_screen_width(uint16_t width) { screen_width_ = width; }
    void set_screen_height(uint16_t height) { screen_height_ = height; }
    void set_eye_size(uint16_t size) { eye_size_ = size; }
    void set_eye_distance(uint16_t distance) { 
        if (face_) face_->EyeInterDistance = distance;
    }
    
    // Emotion control
    void set_emotion(uint8_t emotion, float weight) {
        if (face_) face_->Behavior.SetEmotion((eEmotions)emotion, weight);
    }
    
    void set_random_behavior(bool enabled) {
        if (face_) face_->RandomBehavior = enabled;
    }
    
    void set_random_blink(bool enabled) {
        if (face_) face_->RandomBlink = enabled;
    }
    
    void set_random_look(bool enabled) {
        if (face_) face_->RandomLook = enabled;
    }
    
    // Look direction control
    void look_at(float x, float y) {
        if (face_) face_->Look.LookAt(x, y);
    }
    
    void look_left() {
        if (face_) face_->LookLeft();
    }
    
    void look_right() {
        if (face_) face_->LookRight();
    }
    
    void look_front() {
        if (face_) face_->LookFront();
    }
    
    void look_top() {
        if (face_) face_->LookTop();
    }
    
    void look_bottom() {
        if (face_) face_->LookBottom();
    }
    
    // Blink control
    void do_blink() {
        if (face_) face_->DoBlink();
    }
    
    void set_blink_interval(unsigned long millis) {
        if (face_) face_->Blink.Timer.SetIntervalMillis(millis);
    }
    
    // Look interval control
    void set_look_interval(unsigned long millis) {
        if (face_) face_->Look.Timer.SetIntervalMillis(millis);
    }
    
    // Behavior interval control
    void set_behavior_interval(unsigned long millis) {
        if (face_) face_->Behavior.Timer.SetIntervalMillis(millis);
    }
    
    // Display update frequency
    void set_update_interval(uint32_t interval) { update_interval_ = interval; }
    
    float get_setup_priority() const override;
    
protected:
    display::Display* display_;
    EsphomeDisplayAdapter* display_adapter_;
    Face* face_;
    
    uint16_t screen_width_;
    uint16_t screen_height_;
    uint16_t eye_size_;
    uint32_t update_interval_;
    uint32_t last_update_;
};

}  // namespace esp32_eyes
}  // namespace esphome

#endif  // _ESP32_EYES_ESPHOME_COMPONENT_h

#endif  // USE_ESPHOME_DISPLAY
