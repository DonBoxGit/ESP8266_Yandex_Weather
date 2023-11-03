#ifndef _MAIN_H_
#define _MAIN_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <EncButton.h>

//#include <time.h>
//#include "FontsRus/TimesNRCyr6.h"
#include "weather_icon_elements.h"
#include "weather_status.h"
#include "timer_blink.h"
#include "drawer_functions.h"

EncButton encoder(ENC_SLK_PIN, ENC_DT_PIN, ENC_SW_PIN);
//Button encButton(D0, INPUT_PULLUP, LOW);

Blink blinkDots(CLOCK_DOTS_BLINK_PERIOD_MS);
Timer httpRequestPeriod(WEATHER_REQUEST_PERIOD_MS);
Timer cbrRequestPeriod(60000);
static void YandexHttpRequest(void);
static void CbrHttpRequest(void);
Adafruit_ST7735 tft_display = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);
StaticJsonDocument<1000> jsonDocument;
struct tm* time_info;
static uint16_t weather_id;
static int8_t weather_temperature;

static float usd_currency;
static float eur_currency;
/*------------------------| Get currency value |-----------------------------*/
#define CHARACTERS_NAMBER 7
float getCurrency(const String& xml, const String& currency_name) {
    String sub_string = "<Value>";
    int currency_position = xml.indexOf(currency_name);
    int value_position = xml.indexOf(sub_string, currency_position)
        + sub_string.length();
    String buff = "";
    for (int i = value_position; i < value_position + CHARACTERS_NAMBER; i++) {
        if (xml[i] == ',') {
            buff += '.';
            continue;
        }
        buff += xml[i];
    }
    float curency = buff.toFloat();
    return curency;
}

#endif /* _MAIN_H_ */