/***************************************************
Modified Common.h for ESPHOME Display Support
This header provides a unified interface for drawing operations
***************************************************/

#ifndef COMMON_ESP32_EYES_h
#define COMMON_ESP32_EYES_h

#include <Arduino.h>

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


#endif
