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
  tft_display.fillScreen (ST77XX_BLACK);
  tft_display.setRotation(3);
  tft_display.println ("ST7735 SPI tft initialized");
  //tft.cp437(true);

  WiFi.begin(ssid, pass);
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
    if (enc_count == static_cast<int8_t>(ScreenName::kCurrency))
      refresh_currency_rate = true;
    tft_display.fillScreen(0x0000);
  }
  if (encoder.right()) {
    if (--enc_count < 0)
      enc_count = static_cast<int8_t>(ScreenName::kMaxElement) - 1;
    if (enc_count == static_cast<int8_t>(ScreenName::kWeather))
      refreshWeatherScreen();
    if (enc_count == static_cast<int8_t>(ScreenName::kCurrency))
      refresh_currency_rate = true;
    tft_display.fillScreen(0x0000);
  }
  
  switch (enc_count) {
    case static_cast<int8_t>(ScreenName::kWeather):
      /* Draw the weather picture */
      drawWeatherIcon(weather_id);
      
      /* Display temperature */
      displayTemperature(weather_temperature);

      /* Display curent time with blink dots */
      displayTime(time_info);
      drawBlinkDots();

      /* Display day of month and day of week */
      drawDateCard(time_info);
      break;
    
    case static_cast<int8_t>(ScreenName::kCurrency):
      drawCurrencyRates(time_info, usd_currency, eur_currency);
      break;
    
    case static_cast<int8_t>(ScreenName::kCalendar):
      tft_display.setFont();
      tft_display.setCursor(7, 55);
      tft_display.print("This will be a calendar");
      break;

    default:
      break;
  }
}

static void CbrHttpRequest() {
  WiFiClientSecure wifiClientSecure;
  HTTPClient httpClient;
  httpClient.useHTTP10(true);
  wifiClientSecure.setInsecure();
  /* Get with UTF-8 code format transformation:
   https://www.cbr-xml-daily.ru/daily_utf8.xml */
  httpClient.begin(wifiClientSecure, "https://www.cbr-xml-daily.ru/daily_utf8.xml");
  Serial.println("Try to get request...");
  
  int httpCode = httpClient.GET();
  Serial.printf("Http code: %d\n", httpCode);
  String payload = httpClient.getString().substring(2702, 2997);
  httpClient.end();
  usd_currency = getCurrency(payload, "USD");
  eur_currency = getCurrency(payload, "EUR");
}

static void YandexHttpRequest() {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      String serverPath = YANDEX_WEATHER_JSON + region_id;

      WiFiClient wifiClient;
      HTTPClient httpClient;
      httpClient.begin(wifiClient, serverPath);
      int httpCode = httpClient.GET();

      if (httpCode > 0) {
        String response = httpClient.getString();
        //Deserialize the JSON document
        DeserializationError error = deserializeJson(jsonDocument, response);

        /* Checking the success of parsing */
        if (error) {
          String errorStr = error.c_str();
          Serial.println(errorStr);
        } else {
        /* Get Unix time as microseconds */
        time_t unixTime = (jsonDocument["time"]);

        JsonObject clocks = jsonDocument["clocks"][region_id];
        JsonObject clocks_weather = clocks["weather"];

        /* Get UTC offset as microseconds */
        unsigned long utc_off_set = clocks["offset"];

        /* Get weather icon name */
        String weather_icon = clocks_weather["icon"];
        Serial.print("Weather icon: ");
        Serial.println(weather_icon);
        weather_id = calculateWeatherId(weather_icon);

        /* Get temperature */
        weather_temperature = clocks_weather["temp"];
       
        /* Calculate local time from Unix time */
        unixTime = (unixTime + utc_off_set) / 1000;
        time_info = localtime(&unixTime);
        }
        Serial.printf("Current time - %d:%d\n", time_info->tm_hour, time_info->tm_min);
      } else {
        Serial.println("http.GET() == 0");
      }

      httpClient.end(); // Закрываем соединение
    } else {
      Serial.println("WiFi отключен");
    }
}
