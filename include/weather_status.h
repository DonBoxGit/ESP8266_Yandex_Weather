#ifndef _WEATHER_STATUS_H_
#define _WEATHER_STATUS_H_

#include <Arduino.h>

enum class WeatherId : uint16_t {
  kSkc_d = 466,  /* Clear */
  kSkc_n = 476,  /* Clear sky and night */
  kOvc   = 328,  /* Cloudy */
  kBkn_d = 460,  /* Cloudy with clarifications at day */
  kBkn_n = 470,  /* Cloudy with clarifications at night */
  kOvc_minus_ra = 1185, /* Cloudy with light rain */
  kOvc_ra = 584,        /* Rain */
};

#endif /* _WEATHER_STATUS_H_ */