#ifndef _FIGMA_DRAW_
#define _FIGMA_DRAW_

#include <stdint-gcc.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "rgb_converter.h"
#include "project_config.h"

extern Adafruit_ST7735 tft_display;

namespace figma {
  /*!
    @brief    Draw a circle with fill like in Figma
    @param    x   Left-top x coordinate
    @param    y   Left-top y coordinate
    @param    d   Diameter in pixels
    @param    rgb888 24-bit 8-8-8 Color to fill with
  */
  void fillCircle(uint16_t x, uint16_t y, uint16_t d, uint32_t rgb888) {
    uint16_t r = d / 2;
    tft_display.fillCircle((x + r), (y + r), r, rgb888_to_rgb565(rgb888));
  }

  void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t rgb888) {
    tft_display.fillRect(x, y, w, h, rgb888_to_rgb565(rgb888));
  }

  void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                    uint16_t x2, uint16_t y2, uint32_t rgb888) {
    tft_display.fillTriangle(x0, y0, x1, y1, x2, y2, rgb888_to_rgb565(rgb888));
  }

  void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                uint32_t rgb888) {
    tft_display.drawLine(x0, y0, x1, y1, rgb888_to_rgb565(rgb888));
  }

} /* namespace figma */

#endif /* _FIGMA_DRAW_ */