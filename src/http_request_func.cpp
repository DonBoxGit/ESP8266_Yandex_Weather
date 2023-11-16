#include "http_request_func.h"

StaticJsonDocument<1000> jsonDocument;
String region_id = REGION_ID;
struct tm* time_info;
uint16_t weather_id;
int8_t weather_temperature;
float usd_currency;
float eur_currency;

void CbrHttpRequest() {
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
  String payload = httpClient.getString().substring(2690, 2997);
  httpClient.end();
  eur_currency = getCurrency(payload, "EUR");
  usd_currency = getCurrency(payload, "USD");
  Serial.print(payload);
}

void YandexHttpRequest() {
    /* Check WiFi connection status */
    if (WiFi.status() == WL_CONNECTED) {
      String serverPath = YANDEX_WEATHER_JSON_PATH + region_id;

      WiFiClient wifiClient;
      HTTPClient httpClient;
      httpClient.begin(wifiClient, serverPath);
      int httpCode = httpClient.GET();

      if (httpCode > 0) {
        String response = httpClient.getString();
        /* Deserialize the JSON document */
        DeserializationError error = deserializeJson(jsonDocument, response);

        /* Checking the success of parsing */
        if (error) {
          String errorStr = error.c_str();
          Serial.println("Something goin wrong");
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
      /* Closing the http connection */
      httpClient.end();
    } else {
      Serial.println("WiFi отключен");
    }
}

/*------------------------| Get currency value |-----------------------------*/
#define CHARACTERS_QUANTITY 7
float getCurrency(const String& xml, const String& currency_name) {
    String sub_string = "<Value>";
    int currency_position = xml.indexOf(currency_name);
    int value_position = xml.indexOf(sub_string, currency_position)
        + sub_string.length();
    String buff = "";
    for (int i = value_position; i < value_position + CHARACTERS_QUANTITY; i++) {
        if (xml[i] == ',') {
            buff += '.';
            continue;
        }
        buff += xml[i];
    }
    float curency = buff.toFloat();
    return curency;
}

uint16_t calculateWeatherId(const char* str) {
	uint16_t id = 0;
	for (uint8_t i = 0; (str + i) !=0; i++) { // str[i] - exception?
		id += str[i];
	}
	return id;
}

uint16_t calculateWeatherId(const String& str) {
  uint16_t id = 0;
  for (uint8_t i = 0; i < str.length(); i++)
    id += str[i];
  return id;
}
