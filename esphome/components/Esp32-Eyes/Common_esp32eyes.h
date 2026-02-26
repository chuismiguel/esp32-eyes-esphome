/***************************************************
Modified Common.h for ESPHOME Display Support
This header provides a unified interface for drawing operations
***************************************************/

#ifndef COMMON_ESP32_EYES_h
#define COMMON_ESP32_EYES_h

#include <Arduino.h>

#ifdef USE_ESPHOME_DISPLAY
    #include "IDisplayAdapter.h"
    extern IDisplayAdapter* g_displayAdapter;
    
    // Macro-based interface for compatibility with existing code
    #define DRAW_HLINE(x, y, len) (g_displayAdapter ? g_displayAdapter->drawHLine(x, y, len) : (void)0)
    #define DRAW_BOX(x, y, w, h) (g_displayAdapter ? g_displayAdapter->drawBox(x, y, w, h) : (void)0)
    #define DRAW_TRIANGLE(x0, y0, x1, y1, x2, y2) (g_displayAdapter ? g_displayAdapter->drawTriangle(x0, y0, x1, y1, x2, y2) : (void)0)
    #define SET_DRAW_COLOR(c) (g_displayAdapter ? g_displayAdapter->setDrawColor(c) : (void)0)
    #define GET_DISPLAY_WIDTH() (g_displayAdapter ? g_displayAdapter->getWidth() : 128)
    #define GET_DISPLAY_HEIGHT() (g_displayAdapter ? g_displayAdapter->getHeight() : 64)
    #define CLEAR_DISPLAY() (g_displayAdapter ? g_displayAdapter->clearDisplay() : (void)0)

#else
    // Original U8g2 support
    #include <U8g2lib.h>
    extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    
    // Compatibility macros
    #define DRAW_HLINE(x, y, len) u8g2.drawHLine(x, y, len)
    #define DRAW_BOX(x, y, w, h) u8g2.drawBox(x, y, w, h)
    #define DRAW_TRIANGLE(x0, y0, x1, y1, x2, y2) u8g2.drawTriangle(x0, y0, x1, y1, x2, y2)
    #define SET_DRAW_COLOR(c) u8g2.setDrawColor(c)
    #define GET_DISPLAY_WIDTH() u8g2.getWidth()
    #define GET_DISPLAY_HEIGHT() u8g2.getHeight()
    #define CLEAR_DISPLAY() { u8g2.clearBuffer(); u8g2.sendBuffer(); }

#endif

#endif
