/***************************************************
ESPHOME Display Adapter Implementation
***************************************************/

#ifndef _ESPHOME_DISPLAY_ADAPTER_h
#define _ESPHOME_DISPLAY_ADAPTER_h

#include "IDisplayAdapter.h"

#ifdef USE_ESPHOME_DISPLAY

namespace esphome {
namespace display {
class Display;
}
}

/**
 * Adapter for ESPHOME Display component
 * Translates ESP32-Eyes drawing calls to ESPHOME Display API
 */
class EsphomeDisplayAdapter : public IDisplayAdapter {
private:
    esphome::display::Display* display;
    uint16_t currentColor = 1;
    
public:
    EsphomeDisplayAdapter(esphome::display::Display* disp) : display(disp) {}
    
    void drawHLine(int16_t x, int16_t y, int16_t length) override;
    
    void drawBox(int16_t x, int16_t y, int16_t width, int16_t height) override;
    
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) override;
    
    void setDrawColor(uint16_t color) override {
        currentColor = color;
    }
    
    uint16_t getDrawColor() override {
        return currentColor;
    }
    
    void sendBuffer() override {
        // ESPHOME Display handles buffer management
    }
    
    uint16_t getWidth() override;
    
    uint16_t getHeight() override;
    
    void clearDisplay() override;
};

#endif

#endif
