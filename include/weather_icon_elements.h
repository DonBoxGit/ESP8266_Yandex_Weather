#ifndef _WEATHER_ICON_ELEMENTS_
#define _WEATHER_ICON_ELEMENTS_

#include "figma_drawer.h"
#include "bitmaps/beams_of_light.inc"
#include "bitmaps/beams_of_big_light.inc"
#include "bitmaps/snowflake.inc"

/* Draw the snowflake */
void drawSnowflake(uint16_t x = 0, uint16_t y = 0) {
  tft_display.drawRGBBitmap(x, y, snowflake, 18, 19);
}

/* Draw the one drop */
void drawOneDrops(uint16_t x = 0, uint16_t y = 0) {
  figma::fillTriangle(41 + x, 85 + y, 52 + x, 75 + y, 53 + x, 89 + y, 0x005DFF);
  figma::fillCircle(41 + x, 81 + y, 13, 0x005DFF);
}

/* Draw the two drops */  
void drawTwoDrops(uint16 x = 0, uint16_t y = 0) {
  /* The first drop. */
  figma::fillTriangle(30 + x, 90 + y, 39 + x, 81 + y, 40 + x, 95 + y, 0x005DFF);
  figma::fillCircle(28 + x, 88 + y, 12, 0x005DFF);
  /* The second drop. */
  figma::fillTriangle(57 + x, 86 + y, 67 + x, 75 + y, 68 + x, 90 + y, 0x005DFF);
  figma::fillCircle(56 + x, 83 + y, 12, 0x005DFF);
}

/* Draw the three drops */
void drawThreeDrops(uint16_t x = 0, uint16_t y = 0) {
  /* The first drop. */
  figma::fillTriangle(16 + x, 86 + y, 26 + x, 75 + y, 27 + x, 91 + y, 0x005DFF);
  figma::fillCircle(15 + x, 82 + y, 13, 0x005DFF);
  /* the middle drop. */
  figma::fillTriangle(41 + x, 92 + y, 52 + x, 81 + y, 52 + x, 95 + y, 0x005DFF);
  figma::fillCircle(41 + x, 87 + y, 13, 0x005DFF);
  /* The third drop. */
  figma::fillTriangle(66 + x, 85 + y, 78 + x, 76 + y, 78 + x, 91 + y, 0x005DFF);
  figma::fillCircle(66 + x, 82 + y, 13, 0x005DFF);
}

/* Draw the cloud */
void drawCloud(uint16_t x = 0, uint16_t y = 0) {
  figma::fillCircle(9  + x, 48 + y, 20, 0x8AADFB);
  figma::fillCircle(20 + x, 38 + y, 24, 0x8AADFB);
  figma::fillCircle(34 + x, 23 + y, 41, 0x8AADFB);
  figma::fillCircle(66 + x, 41 + y, 27, 0x8AADFB);
  figma::fillRect(17 + x, 57 + y, 63, 12, 0x8AADFB);
}

/* Draw the cloud behind */
void drawCloudBehind(uint16_t x = 0, uint16_t y = 0) {
  figma::fillCircle(6  + x, 35 + y, 29, 0xDBEBF9);
  figma::fillCircle(21 + x, 17 + y, 43, 0xDBEBF9);
}

/* Draw the moon */
void drawMoon(uint16_t x = 0, uint16_t y = 0) {
  figma::fillCircle(7 + x, 3 + y, 41, 0xFFB200);
  figma::fillCircle(4 + x, 0 + y, 36, 0x000000);
}

/* Draw the Sun behind the cloud */
void drawSmallSun(uint16_t x, uint16_t y) {
  figma::fillCircle(19 + x, 16 + y, 35, 0xFF9C00);
  tft_display.drawRGBBitmap(3 + x, 38 + y, beam_1, 13, 6);
  tft_display.drawRGBBitmap(3 + x, 23 + y, beam_2, 13, 6);
  tft_display.drawRGBBitmap(12 + x, 8 + y, beam_3, 10, 11);
  tft_display.drawRGBBitmap(27 + x, 0 + y, beam_4, 5, 13);
  tft_display.drawRGBBitmap(41 + x, 1 + y, beam_5, 6, 12);
  tft_display.drawRGBBitmap(51 + x, 9 + y, beam_6, 11, 10);
}

/* Draw big Moon at night */
void drawBigMoon(uint16_t x, uint16_t y) {
  figma::fillCircle(32 +x, 23 + y, 56, 0xFFB200);
  figma::fillCircle(27 + x, 21 + y, 51, 0x000000);
  /* Big star */
  figma::fillTriangle(7 + x, 35 + y, 17 + x, 35 + y, 15 + x, 41 + y, 0x9CB6F0);
  figma::fillTriangle(13 + x, 38 + y, 17 + x, 28 + y, 20 + x, 38 + y, 0x9CB6F0);
  figma::fillTriangle(17 + x, 41 + y, 15 + x, 36 + y, 26 + x, 35 + y, 0x9CB6F0);
  figma::fillTriangle(13 + x, 40 + y, 19 + x, 36 + y, 22 + x, 46 + y, 0x9CB6F0);
  figma::fillTriangle(10 + x, 47 + y, 13 + x, 36 + y, 19 + x, 40 + y, 0x9CB6F0);
  /* Small star-1 */
  figma::fillTriangle(22 + x, 83 + y, 25 + x, 77 + y, 27 + x, 83 + y, 0x9CB6F0);
  figma::fillTriangle(24 + x, 84 + y, 23 + x, 81 + y, 29 + x, 81 + y, 0x9CB6F0);
  figma::fillTriangle(25 + x, 81 + y, 28 + x, 86 + y, 24 + x, 84 + y, 0x9CB6F0);
  figma::fillTriangle(23 + x, 82 + y, 26 + x, 83 + y, 22 + x, 86 + y, 0x9CB6F0);
  figma::fillTriangle(21 + x, 81 + y, 25 + x, 81 + y, 25 + x, 84 + y, 0x9CB6F0);
  /* Small star-2 */
  x += 64, y -= 73;
  figma::fillTriangle(22 + x, 83 + y, 25 + x, 77 + y, 27 + x, 83 + y, 0x9CB6F0);
  figma::fillTriangle(24 + x, 84 + y, 23 + x, 81 + y, 29 + x, 81 + y, 0x9CB6F0);
  figma::fillTriangle(25 + x, 82 + y, 28 + x, 86 + y, 24 + x, 84 + y, 0x9CB6F0);
  figma::fillTriangle(23 + x, 82 + y, 26 + x, 83 + y, 22 + x, 86 + y, 0x9CB6F0);
  figma::fillTriangle(21 + x, 81 + y, 25 + x, 81 + y, 25 + x, 84 + y, 0x9CB6F0);
}

/* Draw big Sun */
void drawBigSun(uint16_t x, uint16_t y) {
  figma::fillCircle(27 + x, 27 + y, 46, 0xFF9C00);
  /* First half beams */
  tft_display.drawRGBBitmap(6 + x, 56 + y, b_beam_1, 17, 8);
  tft_display.drawRGBBitmap(6 + x, 37 + y, b_beam_2, 17, 7);
  tft_display.drawRGBBitmap(17 + x, 17 + y, b_beam_3, 14, 14);
  tft_display.drawRGBBitmap(37 + x, 6 + y, b_beam_4, 8, 17);
  tft_display.drawRGBBitmap(56 + x, 6 + y, b_beam_5, 8, 17);
  tft_display.drawRGBBitmap(69 + x, 17 + y, b_beam_6, 14, 14);
  /* Second half beams */
  tft_display.drawRGBBitmap(77 + x, 37 + y, b_beam_1, 17, 8);
  tft_display.drawRGBBitmap(77 + x, 56 + y, b_beam_2, 17, 7);
  tft_display.drawRGBBitmap(69 + x, 69 + y, b_beam_3, 14, 14);
  tft_display.drawRGBBitmap(56 + x, 77 + y, b_beam_4, 8, 17);
  tft_display.drawRGBBitmap(37 + x, 77 + y, b_beam_5, 8, 17);
  tft_display.drawRGBBitmap(16 + x, 70 + y, b_beam_6, 14, 14);
}

#endif /* _WEATHER_ICON_ELEMENTS_ */