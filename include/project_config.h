#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_

static const char* ssid = "Mars-23";      // SSID name of WiFi 
static const char* pass = "1978231978";   // Pass of WiFi router
static String region_id = "11036";        // ID region by Yandex
#define YANDEX_WEATHER_JSON  "https://yandex.com/time/sync.json?geo="

#define CBR_REQUEST_PERIOD_MS        1000 * 60 * 60
#define WEATHER_REQUEST_PERIOD_MS    1000 * 60 * 2
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