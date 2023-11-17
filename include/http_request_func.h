#ifndef _HTTP_REQUEST_FUNC_
#define _HTTP_REQUEST_FUNC_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "project_config.h"
#include "weather_status.h"

extern uint16_t calculateWeatherId(const String& str);
extern uint16_t calculateWeatherId(const char* str);

void YandexHttpRequest(void);
void CbrHttpRequest(void);
float getCurrency(const String& xml, const String& currency_name);

#endif /* _HTTP_REQUEST_FUNC_ */