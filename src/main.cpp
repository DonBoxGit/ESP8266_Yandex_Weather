/*
  The weather and currency informer.
           ver. 1.0.0
                by Yakubovskiy R. N.
*/
#include "main.h"

IRAM_ATTR void isr() {
  encoder.tickISR();
}

void setup() {
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(ENC_CLK_PIN), isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_DT_PIN), isr, CHANGE);
  encoder.setEncISR(true);
  encoder.setEncType(EB_STEP2);
  
  /* init ST7735S chip, black tab */
  tft_display.initR (INITR_BLACKTAB);
  tft_display.fillScreen(ST77XX_BLACK);
  tft_display.setRotation(3);
  tft_display.println ("ST7735 SPI tft initialized");
  //tft.cp437(true);

  WiFi.begin(SSID, PASS);
  tft_display.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    tft_display.print(".");
    delay(500);
  }
  tft_display.print("\nWiFi IP: ");
  tft_display.println(WiFi.localIP());

  YandexHttpRequest();
  CbrHttpRequest();
  tft_display.setTextSize(1);
  tft_display.fillScreen(ST77XX_BLACK);
}

enum class ScreenName {
  kWeather = 0,
  kCurrency,
  kCalendar,
  kMaxElement
};

void loop() {
  encoder.tick();

  /* HTTP GET request to Yandex */
  if (httpRequestPeriod.ready()) {
    YandexHttpRequest();
  }

  /* Get value currencys from CBR */
  if (cbrRequestPeriod.ready()) {
    CbrHttpRequest();
  }

  static int8_t enc_count = 0;
  if (encoder.left()) {
    if (++enc_count > static_cast<int8_t>(ScreenName::kMaxElement) - 1)
      enc_count = 0;
    if (enc_count == static_cast<int8_t>(ScreenName::kWeather))
      refreshWeatherScreen();
    if (enc_count == static_cast<int8_t>(ScreenName::kCurrency)) {
      refresh_currency_rate = true;
      refreshClock();
    }
    if (enc_count == static_cast<int8_t>(ScreenName::kCalendar))
      refresh_calendar = true;
    tft_display.fillScreen(0x0000);
  }

  if (encoder.right()) {
    if (--enc_count < 0)
      enc_count = static_cast<int8_t>(ScreenName::kMaxElement) - 1;
    if (enc_count == static_cast<int8_t>(ScreenName::kWeather))
      refreshWeatherScreen();
    if (enc_count == static_cast<int8_t>(ScreenName::kCurrency)) {
      refresh_currency_rate = true;
      refreshClock();
    }
    if (enc_count == static_cast<int8_t>(ScreenName::kCalendar))
      refresh_calendar = true;
    tft_display.fillScreen(0x0000);
  }
  
  switch (enc_count) {
    /*---------------| The Yandex weather screen |---------------- */
    case static_cast<int8_t>(ScreenName::kWeather):
      /* Draw the weather picture */
      drawWeatherIcon(weather_id);
      
      /* Display temperature */
      displayTemperature(weather_temperature);

      /* Display curent time with blink dots */
      displayTime(time_info);

      /* Display day of month and day of week */
      drawDateCard(time_info);
      break;

    /*-------------| The CBRs currency rate screen |---------------*/
    case static_cast<int8_t>(ScreenName::kCurrency):
      drawCurrencyRates(time_info, usd_currency, eur_currency);
      displayTime(time_info);
      break;
    
    /*-------------------| The calendar screen |-------------------*/
    case static_cast<int8_t>(ScreenName::kCalendar):
      drawCalendar(time_info);
      break;

    default:
      break;
  }
}