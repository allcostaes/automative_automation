#ifndef RelogioDigital_h
#define RelogioDigital_h
#include "Arduino.h" 
#include <Arduino_FreeRTOS.h>
// Date and time functions using a PCF8563 RTC connected via I2C and Wire lib
#include "RTClib.h"
// Display de 4 dígitos 
#include <TM1637Display.h>

class RelogioDigital
{
  public:
      RelogioDigital();
      void RelogioDigital::atualizarDisplay();
      // RTC PCF8563000000000000000001117425456ddfgdfgdfgdfgdfg
};


#endif
