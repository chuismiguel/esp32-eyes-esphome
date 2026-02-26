/***************************************************
ESPHOME Display Adapter Implementation
***************************************************/

#ifdef USE_ESPHOME_DISPLAY

#include "EsphomeDisplayAdapter.h"
#include "esphome/components/display/display.h"

void EsphomeDisplayAdapter::drawHLine(int16_t x, int16_t y, int16_t length) {
    if (display && length > 0) {
        uint16_t xEnd = x + length - 1;
        // Use ESPHOME's line drawing with same start and end y coordinate
        display->line(x, y, xEnd, y, esphome::Color(currentColor, currentColor, currentColor));
    }
}

void EsphomeDisplayAdapter::drawBox(int16_t x, int16_t y, int16_t width, int16_t height) {
    if (display && width > 0 && height > 0) {
        // Draw filled rectangle using ESPHOME API
        uint16_t xEnd = x + width - 1;
        uint16_t yEnd = y + height - 1;
        display->filled_rectangle(x, y, xEnd, yEnd, 
                                 esphome::Color(currentColor, currentColor, currentColor));
    }
}

void EsphomeDisplayAdapter::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                                        int16_t x2, int16_t y2) {
    if (display) {
        // ESPHOME's triangle drawing
        display->filled_polygon({
            esphome::display::Point(x0, y0),
            esphome::display::Point(x1, y1),
            esphome::display::Point(x2, y2)
        }, esphome::Color(currentColor, currentColor, currentColor));
    }
}

uint16_t EsphomeDisplayAdapter::getWidth() {
    return display ? display->get_width() : 128;
}

uint16_t EsphomeDisplayAdapter::getHeight() {
    return display ? display->get_height() : 64;
}

void EsphomeDisplayAdapter::clearDisplay() {
    if (display) {
        display->fill(esphome::Color::BLACK);
    }
}

#endif
