#include "CameraRe.h"

//-------------------------------------------------   MÓDULO RELÉ    -----------------------------------------------------------
//  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// DISPOSITIVO: 
// PORTA ARDUINO: 7       RELE IN:7         
int portaRele7 = 7;


CameraRe::CameraRe()
{
  Serial.begin(9600);
  re = Re();
  linha15 = Linha15();
  // Define pinos para o rele como saída
  pinMode(portaRele7, OUTPUT); 
  digitalWrite(portaRele7, HIGH);
  //controleremoto = ControleRemoto();
}

void CameraRe::LigarDesligarCameraRe()   
{
     
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
           while(re.checarReLigada()==true)
           {
               Serial.write(2); //VGA
               digitalWrite(portaRele7, LOW);
           }
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
           while(re.checarReLigada()==false)
           {
               Serial.write(1); // HDMI
               digitalWrite(portaRele7, HIGH);
           }
    }
}

          
      
