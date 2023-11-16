#ifndef _MAIN_H_
#define _MAIN_H_

#include <EncButton.h>

#include "weather_icon_elements.h"
#include "weather_status.h"
#include "timer_blink.h"
#include "drawer_functions.h"
#include "http_request_func.h"

enum class ScreenName {
  kWeather = 0,
  kCurrency,
  kCalendar,
  kMaxElement
};

const char* SSID = SSID_ROUTER;
const char* PASS = PASS_ROUTER;

/* Create an encoder object */
EncButton encoder(ENC_CLK_PIN, ENC_DT_PIN, ENC_SW_PIN);

/* Create a tft display object  */
Adafruit_ST7735 tft_display = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

extern uint16_t weather_id;
extern int8_t weather_temperature;
extern struct tm* time_info;
extern float usd_currency;
extern float eur_currency;

Blink blinkDots(CLOCK_DOTS_BLINK_PERIOD_MS);
Timer httpRequestPeriod(WEATHER_REQUEST_PERIOD_MS);
Timer cbrRequestPeriod(CBR_REQUEST_PERIOD_MS);

#endif /* _MAIN_H_ */