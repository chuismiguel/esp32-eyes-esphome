/***************************************************
U8g2 Display Adapter Implementation
***************************************************/

#ifndef _U8G2DISPLAYADAPTER_h
#define _U8G2DISPLAYADAPTER_h

#include "IDisplayAdapter.h"

#ifdef USE_U8G2_DISPLAY
#include <U8g2lib.h>

/**
 * Adapter for U8g2 display library
 * Provides backward compatibility with existing code
 */
class U8g2DisplayAdapter : public IDisplayAdapter {
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display;
    uint16_t currentColor = 1;
    
public:
    U8g2DisplayAdapter(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* disp) : display(disp) {}
    
    void drawHLine(int16_t x, int16_t y, int16_t length) override {
        display->drawHLine(x, y, length);
    }
    
    void drawBox(int16_t x, int16_t y, int16_t width, int16_t height) override {
        display->drawBox(x, y, width, height);
    }
    
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) override {
        display->drawTriangle(x0, y0, x1, y1, x2, y2);
    }
    
    void setDrawColor(uint16_t color) override {
        currentColor = color;
        display->setDrawColor(color);
    }
    
    uint16_t getDrawColor() override {
        return currentColor;
    }
    
    void sendBuffer() override {
        // U8g2 with F_HW_I2C mode handles this automatically
    }
    
    uint16_t getWidth() override {
        return display->getWidth();
    }
    
    uint16_t getHeight() override {
        return display->getHeight();
    }
    
    void clearDisplay() override {
        display->clearBuffer();
        display->sendBuffer();
    }
};

#endif

#endif
