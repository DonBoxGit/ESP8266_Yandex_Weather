#ifndef _RGB_CONVERTOR_
#define _RGB_CONVERTOR_

#include <stdint.h>
#include <cmath>

/* The conversion function from RGB24-bit to RGB16-bit. */
uint16_t rgb888_to_rgb565(uint32_t rgb24) {
  /* Splitting a 24-bit value to 3 8-bit ones. */
  uint8_t red8 = (rgb24 >> 16);
  uint8_t green8 = (rgb24 >> 8);
  uint8_t blue8 = rgb24;

  /* Converting 8-bit value to 5 and 6 bit respectively. */
  uint8_t red5 = round(red8 * 31 / 255);
  uint8_t green6 = round(green8 * 63 / 255);
  uint8_t blue5 = round(blue8 * 31 / 255);

  /* Gluing 565 bits to 16-bit and returning. */
  return ((red5 << 11) | (green6 << 5) | blue5);
}

#endif /* _RBG_CONVERTOR_ */