#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "Luz.h"


//-------------------------------------------------   MÓDULO RELÉ    -----------------------------------------------------------
//  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// DISPOSITIVO: 
// PORTA ARDUINO: 8       RELE IN:8         COR DO FIO:  LARANJA
int portaRele8 = 8;

Luz::Luz()
{
  // Define pinos para o rele como saída
  pinMode(portaRele8, OUTPUT); 
  digitalWrite(portaRele8, HIGH);
};



void Luz::ligarLuz(int segundos)   // LIGAR A LUZ POR ALGUNS SEGUNDOS
{
    
    digitalWrite(portaRele8, LOW);
    vTaskDelay(segundos);
    digitalWrite(portaRele8, HIGH);
};
