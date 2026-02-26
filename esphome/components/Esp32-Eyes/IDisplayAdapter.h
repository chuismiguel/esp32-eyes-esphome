/***************************************************
Display Adapter Interface for ESP32 Eyes
Allows use with different display backends (U8g2, ESPHOME Display, etc.)
***************************************************/

#ifndef _IDISPLAYADAPTER_h
#define _IDISPLAYADAPTER_h

#include <Arduino.h>

/**
 * Abstract interface for display operations
 * Implementations should translate calls to their respective display libraries
 */
class IDisplayAdapter {
public:
    virtual ~IDisplayAdapter() {}
    
    // Basic drawing operations
    virtual void drawHLine(int16_t x, int16_t y, int16_t length) = 0;
    virtual void drawBox(int16_t x, int16_t y, int16_t width, int16_t height) = 0;
    virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) = 0;
    
    // Color operations
    virtual void setDrawColor(uint16_t color) = 0;
    virtual uint16_t getDrawColor() = 0;
    
    // Display refresh
    virtual void sendBuffer() = 0;
    
    // Utility
    virtual uint16_t getWidth() = 0;
    virtual uint16_t getHeight() = 0;
    virtual void clearDisplay() = 0;
};

#endif
