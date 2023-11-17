#ifndef _PROJECT_DRAWER_FUNCTIONS_
#define _PROJECT_DRAWER_FUNCTIONS_

#include <time.h>

#include "Fonts/FreeSans24pt7b.h"
#include "Fonts/FreeSans18pt7b.h"
#include "Fonts/FreeSans9pt7b.h"
#include "Fonts/FreeSansBold9pt7b.h"
#include "../../include/FontsRus/FreeSans6.h"
#include "weather_icon_elements.h"
#include "weather_status.h"

extern Blink blinkDots;
bool refresh_hours = false;
bool refresh_minutes = false;
bool refresh_temperature = false;
bool refresh_weather_icon = false;
bool refresh_date_card = false;
bool refresh_currency_rate = false;
bool refresh_calendar = false;

void refreshClock(void) {
  refresh_hours = true;
  refresh_minutes = true;
}

void refreshWeatherScreen(void) {
  refreshClock();
  refresh_date_card = true;
  refresh_temperature = true;
  refresh_weather_icon =true;
}

void displayTemperature(int8_t temperature) {
  static int8_t old_weather_temperature = 0;

  tft_display.setFont(&FreeSans24pt7b);
  /* The checking if the temperature has changed */
  if (old_weather_temperature != temperature || refresh_temperature) {
    /* Draw or erase the minus sign */
    if (temperature < 0)
      tft_display.fillRoundRect(3, 26, 10, 4, 1, ST7735_WHITE);
    else
      tft_display.fillRoundRect(3, 26, 10, 4, 1, ST7735_BLACK);
    
    uint8_t x = 66, y = 10;
    if (abs(temperature) > 9) {
      /* Erase old value of one sign */
      if (old_weather_temperature < 10) {
        tft_display.fillCircle(50, 10, 5, ST7735_BLACK);
        tft_display.setCursor(14, 40);
        tft_display.setTextColor(0x0000);
        tft_display.print(old_weather_temperature);
      }
      /* Erase old value of two signs */
      tft_display.setCursor(8, 40);
      tft_display.setTextColor(0x0000);
      tft_display.print(old_weather_temperature);
    
      /* Draw new value of degree */
      tft_display.fillCircle(x, y, 5, ST7735_WHITE);
      tft_display.fillCircle(x, y, 3, ST7735_BLACK);
      tft_display.setCursor(8, 40);
      tft_display.setTextColor(0xFFFF);
      tft_display.print(abs(temperature));  
    } else {
      /* Erase old value of two signs */
      if (old_weather_temperature > 9) {
        tft_display.fillCircle(x, y, 5, 0x0000); /* Erase degree sign */
        tft_display.setCursor(8, 40);
        tft_display.setTextColor(0x0000);
        tft_display.print(old_weather_temperature);
      }
      /* Erase old valume of one sign */
      tft_display.setCursor(14, 40);
      tft_display.setTextColor(0x0000);
      tft_display.print(old_weather_temperature);

      uint8_t x = 50, y = 10;
      tft_display.fillCircle(x, y, 5, ST7735_WHITE);
      tft_display.fillCircle(x, y, 3, ST7735_BLACK);
      tft_display.setCursor(14, 40);
      tft_display.setTextColor(0xFFFF);
      tft_display.print(abs(temperature));
    }
    old_weather_temperature = abs(temperature);
    tft_display.setFont();
    refresh_temperature = false;
  }
}

void drawWeatherIcon(uint16_t id) {
  static uint16_t old_id = 0;

  /* Position the icon on the main screen */
  uint8_t x = 60, y = 3;
  if (old_id != id || refresh_weather_icon) {
    /* Erase old picture */
    tft_display.fillRect(x, y, 100, 101, 0x0000);
    switch (id) {
      /* Clear */
      case static_cast<uint16_t>(WeatherId::kSkc_d):
        drawBigSun(x, y);
        break;

      /* Clear sky and night */
      case static_cast<uint16_t>(WeatherId::kSkc_n):
        drawBigMoon(x, y);
        break;

      /* Cloudy */
      case static_cast<uint16_t>(WeatherId::kOvc):
        drawCloudBehind(x, y);
        drawCloud(x, y);
        break;

      /* Cloudy with clarifications at day */
      case static_cast<uint16_t>(WeatherId::kBkn_d):
        drawSmallSun(x, y);
        drawCloud(x, y);
        break;
      
      /* Cloudy with clarifications at night */
      case static_cast<uint16_t>(WeatherId::kBkn_n):
        drawMoon(x, y);
        drawCloud(x, y);
        break;

      /* Cloudy with light rain */
      case static_cast<uint16_t>(WeatherId::kOvc_minus_ra):
        drawCloudBehind(x, y);
        drawCloud(x, y);
        drawTwoDrops(x, y);
        break;

      /* Rain */
      case static_cast<uint16_t>(WeatherId::kOvc_ra):
        drawCloudBehind(x, y);
        drawCloud(x, y);
        drawThreeDrops(x, y);
        break;
      
      default:
        tft_display.setFont();
        tft_display.setCursor(62, 23);
        tft_display.print("NO WEATHER ICON");
        break;
      }
      
      old_id = id;
      refresh_hours = true;
      refresh_minutes = true;
      refresh_temperature = true;

      refresh_weather_icon = false;
  }
}

void drawBlinkDots(void) {
  static bool dots_blink_flag = false;
  if (blinkDots.getStatus() && dots_blink_flag) {
    tft_display.setFont(&FreeSans18pt7b);
    tft_display.setTextColor(0x0000);
    tft_display.setCursor(72, 120);
    tft_display.print(":");
    dots_blink_flag = false;
    tft_display.setTextColor(0xFFFF);
  } else if (!blinkDots.getStatus() && !dots_blink_flag) {
    tft_display.setFont(&FreeSans18pt7b);
    tft_display.setTextColor(0xFFFF);
    tft_display.setCursor(72, 120);
    tft_display.print(":");
    dots_blink_flag = true;
  }
}

void displayTime(tm* time_info) {
  static uint8_t old_hours_value = 0;
  tft_display.setTextColor(0xFFFF);
  tft_display.setFont(&FreeSans18pt7b);

  /* Print the hours */
  if (old_hours_value != time_info->tm_hour || refresh_hours) {
    if (time_info->tm_hour > 9) {
      /* Erase old vaolues of hour where one sign */
      if (old_hours_value < 10 || old_hours_value == 0) {
        tft_display.setTextColor(0x0000);
        tft_display.setCursor(30, 120);
        tft_display.print('0');
        tft_display.print(old_hours_value);
      } else {
        /* Erase old vaolues of hour where two signs */
        tft_display.setCursor(30, 120);
        tft_display.setTextColor(0x0000);
        tft_display.print(old_hours_value);
      }
    
      tft_display.setCursor(30, 120);
      tft_display.setTextColor(0xFFFF);
      tft_display.print(time_info->tm_hour);
    } else {
      /* Erase old vaolues of hour where two signs */
      if (old_hours_value > 9) {
        tft_display.setTextColor(0x0000);
        tft_display.setCursor(30, 120);
        tft_display.print(old_hours_value);
      } else {
        /* Erase old vaolues of hour where one sign */
        tft_display.setTextColor(0x0000);
        tft_display.setCursor(30, 120);
        tft_display.print('0');
        tft_display.print(old_hours_value);
      }
      /* Draw new value of one sign hour with shadow 0 */
      tft_display.setTextColor(0x0000);
      tft_display.setCursor(30, 120);
      tft_display.print('0');
      tft_display.setTextColor(0xFFFF);
      tft_display.print(time_info->tm_hour);  
    }
    old_hours_value = time_info->tm_hour;
    refresh_hours = false;
  }

  /* Print the minutes */
  static uint8_t old_minutes_value = 0;
  if (old_minutes_value != time_info->tm_min || refresh_minutes) {
    if (time_info->tm_min > 9) {
      /* Erase old values where was one sign */
      if (old_minutes_value < 10) {
        tft_display.setCursor(85, 120);
        tft_display.setTextColor(0x0000);
        tft_display.print('0');
        tft_display.setCursor(105, 120);
        tft_display.print('9');
      } else {
        /* Erase old values where were two signs */
        tft_display.setCursor(85, 120);
        tft_display.setTextColor(0x0000);
        tft_display.print(old_minutes_value);
      }
      /* Print new values where are two signs */
      tft_display.setTextColor(0xFFFF);
      tft_display.setCursor(85, 120);
      tft_display.print(time_info->tm_min);
    } else {
      if (old_minutes_value > 9) {
        /* Erase old values where were two sign */
        tft_display.setTextColor(0x0000);
        tft_display.setCursor(85, 120);
        tft_display.print(old_minutes_value);
      } else {
        /* Erase old values where was one sign */
        tft_display.setTextColor(0x0000);
        tft_display.setCursor(85, 120);
        tft_display.print('0');
        tft_display.setCursor(105, 120);
        tft_display.print(old_minutes_value);
      }
      /* Pring new values where is one sign */
      tft_display.setTextColor(0xFFFF);
      tft_display.setCursor(85, 120);
      tft_display.print('0');
      tft_display.setCursor(105, 120);
      tft_display.print(time_info->tm_min);
    }
    old_minutes_value = time_info->tm_min;
    refresh_minutes = false;
  }
  drawBlinkDots();
}

void drawDateCard(tm* time_info) {
  static uint8_t past_day_month = 0;
  if (refresh_date_card || past_day_month != time_info->tm_mday) {
    tft_display.setFont(&FreeSans18pt7b);
    const char* week_days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    tft_display.fillRoundRect(13, 48, 45, 43, 3, ST7735_BLACK);
    tft_display.drawRoundRect(12, 47, 47, 45, 3 , ST7735_WHITE);
    if (time_info->tm_mday < 10) {
      tft_display.setCursor(25, 75);
    } else {
      tft_display.setCursor(15, 75);
    }
    tft_display.print(time_info->tm_mday);
    tft_display.setCursor(28, 87);
    tft_display.setFont();
    tft_display.print(week_days[time_info->tm_wday]);
    past_day_month = time_info->tm_mday;
    
    refresh_date_card = false;
  }
}

/*!
    @brief    Draw currency rate card
    @param    x Left-top x coordinate
    @param    y Left-top y coordinate
    @param    color 16-bit 5-6-5 Color
    @param    currencyName Name of currency(e.g. USD, EUR etc.)
    @param    currencyValue Value of currency
  */
void currencyCard(uint8_t x, uint8_t y, uint16_t color,
                  const char* currencyName, float& currencyValue) {
  tft_display.setFont(&FreeSans9pt7b);
  tft_display.drawRoundRect(x, y, 54, 45, 3, color);
  tft_display.fillRoundRect(x + 1, y + 1, 52, 43, 3, 0x3A2C);
  tft_display.setCursor(x + 4, y + 19);
  tft_display.printf("%.2f", currencyValue);
  tft_display.setCursor(x + 8, y + 37);
  tft_display.setFont(&FreeSansBold9pt7b);
  tft_display.print(currencyName);
}

void drawCurrencyRates(tm* time_info, float& usd, float& eur) {
  static float past_usd_currency = 0.0;
  if (refresh_currency_rate || past_usd_currency != usd) {
    tft_display.setFont(&FreeSans6pt8b);
    tft_display.setCursor(2, 15);
    tft_display.setTextColor(ST7735_GREEN);
    tft_display.print("Центральный банк России");
    tft_display.setTextColor(ST7735_WHITE);

    /* Draw the date */
    tft_display.setFont(&FreeSans9pt7b);
    tft_display.setCursor(40, 36);
    tft_display.printf("%d.%d.%d", time_info->tm_mday, 
      time_info->tm_mon + 1, time_info->tm_year + 1900);
    
    currencyCard(20, 46, 0xFFFF, "USD", usd);
    currencyCard(88, 46, 0xFFFF, "EUR", eur);

    past_usd_currency = usd;
    refresh_currency_rate = false;
  }
}

/* Calendar */
const char* monthList[] = { "January", "February", "March", "April", "May",
	"June", "July", "August", "September", "October", "November", "December" };
uint8_t day_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/* The leap year detection function */
bool isLeapYear(int year) {
	if (year % 4 != 0) {
		return false;
	} else if (year % 100 != 0) {
		return true;
	} else if (year % 400 != 0) {
		return false;
	} else {
		return true;
	}
}

/* Calculate day of week */
uint8_t dayOfWeek(int d, int m, int y) {
  int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  y -= m < 3;
  return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

void drawCalendar(tm* time_info) {
  if (refresh_calendar) {
    tft_display.setFont();
    tft_display.setCursor(5, 5);
    tft_display.printf("%s  %d\n", monthList[time_info->tm_mon], time_info->tm_year + 1900);
    tft_display.fillRect(0, 21, 160, 12, 0x3A2C);
    tft_display.setCursor(0, 23);
    tft_display.println("Mn  Tu  Wd  Th  Fr  Sa  Su");

    tft_display.setCursor(0, 40);
    if (isLeapYear(time_info->tm_year + 1900U)) 
      day_in_month[2] = 29U;
    else
      day_in_month[2] = 28U;

    uint8_t item_pos = 1;
    uint8_t day_of_the_week = dayOfWeek(1, 
                                        time_info->tm_mon + 1,
                                        time_info->tm_year + 1900) - 1;
    for (uint8_t i{0}; i < day_of_the_week; i++, item_pos++)
      tft_display.print("    ");
    for (uint8_t day{1}; day <= day_in_month[time_info->tm_mon]; day++) {
      if (day < 10) tft_display.print(" ");
      
      if (day == time_info->tm_mday) {
        tft_display.setTextColor(ST7735_GREEN);
        tft_display.print(day);
        tft_display.setTextColor(0xFFFF);
      } else if (day < time_info->tm_mday) {
        tft_display.setTextColor(0x8C71);
        tft_display.print(day);
        tft_display.setTextColor(0xFFFF);
      } else {
        tft_display.print(day);
      }

      tft_display.print("  ");
      if (item_pos % 7 == 0) tft_display.print('\n');
      item_pos++;
    }
    refresh_calendar = false;
  }
}
#endif /* _PROJECT_DRAWER_FUNCTIONS_ */