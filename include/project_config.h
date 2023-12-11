#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_

#define SSID_ROUTER "Mars-23"            // SSID name of WiFi router
#define PASS_ROUTER "1978231978"         // Password of WiFi router
#define YANDEX_WEATHER_JSON_PATH  "https://yandex.com/time/sync.json?geo="
#define REGION_ID   "11036"              // ID region by Yandex

constexpr uint32_t CBR_REQUEST_PERIOD_MS = 1000 * 60 * 60;
constexpr uint32_t WEATHER_REQUEST_PERIOD_MS = 1000 * 60 * 3;
#define CLOCK_DOTS_BLINK_PERIOD_MS   500

/*-----------------------| Encoder pins configuration |----------------------*/
#define ENC_CLK_PIN  D1
#define ENC_DT_PIN   D2
#define ENC_SW_PIN   D0

/*----------------------| ST7735 display configuration |---------------------*/
#define TFT_WIDTH    128
#define TFT_HEIGHT   160
#define TFT_CS_PIN   D8
#define TFT_DC_PIN   D3
#define TFT_RST_PIN  D4
//#define TFT_RST_PIN -1 // If display RESET pin is connected to NodeMCU RST or 3.3V

#endif /* _PROJECT_CONFIG_H_ */