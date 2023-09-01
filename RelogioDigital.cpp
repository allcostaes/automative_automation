#include "RelogioDigital.h"

RelogioDigital::RelogioDigital()
{


}

void RelogioDigital::atualizarDisplay()   
{

     RTC_PCF8563 rtc;
     char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};  
     // Modulo Display de 4 dígitos  - TM1637
     int clk = 14;
     int dio = 15;
     TM1637Display display = TM1637Display(clk,dio);
     //TM1637Display display(clk, dio);
     unsigned long changeTime; 


    rtc.begin();

    // January 21, 2014 at 3am you would call:
    // this->rtc.adjust(DateTime(2021, 3, 3, 9, 45, 0));
    rtc.start();

    // Display de 4 dígitos
    display.setBrightness(0x0F);
    display.clear();


    for(;;)
    {
        changeTime = 0;
        DateTime now = rtc.now();
        int decimaltime = now.hour() * 100 + now.minute();
        if ((millis() - changeTime) > 2000) {
          
              display.showNumberDecEx(decimaltime, (0x80 >> 1), true, 4, 0);
              changeTime = 0;
              vTaskDelay(100);
            }
          
            if ((millis() - changeTime) > 1000) 
            {
              display.showNumberDec(decimaltime, true, 4, 0);
              changeTime = millis();
              vTaskDelay(100);
            }
    }
}
