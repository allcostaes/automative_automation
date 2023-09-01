#include "Luz.h"
#include "Trava.h"
#include "Linha15.h"
#include "CameraRe.h"
#include "RelogioDigital.h"
#include <Arduino_FreeRTOS.h>


#include "ControleRemoto.h"
ControleRemoto controleremoto;


// Definição de objetos externos
Trava trava = Trava();
Linha15 linha15 = Linha15();
Luz luz = Luz();
CameraRe cameraRe = CameraRe();
RelogioDigital relogioDigital = RelogioDigital();


      
//--------------------------------- Assinatura de funções/tasks ---------------------------------------
void TaskAtualizarRelogioDigital(void *pvParameters); 
void TaskLigarDesligarCameraRe(void *pvParameters); 
void TaskLigarDesligarTrava(void *pvParameters); 
void TaskLigarDesligarLuz(void *pvParameters); 
void TaskTeste(void *pvParameters); 

//==========================================================================================

void setup() 
{
  Serial.begin(9600); 
  controleremoto = ControleRemoto();

  //---------------------------------------
  xTaskCreate(
    TaskAtualizarRelogioDigital
    ,  "TaskAtualizarRelogioDigital"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );
  //==========================================================================================



  //---------------------------------------
  xTaskCreate(
    TaskLigarDesligarCameraRe
    ,  "TaskLigarDesligarCameraRe"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );
  //==========================================================================================


 //---------------------------------------
  xTaskCreate(
    TaskLigarDesligarTrava
    ,  "TaskLigarDesligarTrava"
    ,  128  // Stack size
    ,  NULL
    ,  32  // Priority
    ,  NULL );
  //==========================================================================================



 //---------------------------------------
  xTaskCreate(
    TaskLigarDesligarLuz
    ,  "TaskLigarDesligarLuz"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );
  //==========================================================================================


  //---------------------------------------
  xTaskCreate(
    TaskTeste
    ,  "TaskTeste"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );
  //==========================================================================================

}
//////////////////////////////////////////// fim do setup//////////////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  
}





//-----------------------------------------------------------------------------------------------
void TaskAtualizarRelogioDigital(void *pvParameters)  
{
  (void) pvParameters;
  relogioDigital.atualizarDisplay();
}


//-----------------------------------------------------------------------------------------------
void TaskLigarDesligarCameraRe(void *pvParameters)  
{
  (void) pvParameters;
  for(;;)
    cameraRe.LigarDesligarCameraRe();
 
}
//-----------------------------------------------------------------------------------------------
void TaskLigarDesligarLuz(void *pvParameters)  
{
  (void) pvParameters;
  // Variável para armazenar se a linha 15 está ligada
  boolean carroLigado = false;

  for (;;) // A Task shall never return or exit.
  {

        boolean linha15ligada = linha15.checarLinha15Ligada();

        if (  (linha15ligada==false) && (carroLigado==true)  )
        {
          luz.ligarLuz(1000);  //liga a luz por 5 segundos
          carroLigado=false;
        }

        linha15ligada = linha15.checarLinha15Ligada();
        if (  (linha15ligada==true) && (carroLigado==false)  )
        {
          //luz.ligarLuz(200);  //liga a luz por 5 segundos
          carroLigado=true;
        }
  }
}

//-----------------------------------------------------------------------------------------------
void TaskLigarDesligarTrava(void *pvParameters)  
{
  int flagTrava1minuto=0, seg=0;
  (void) pvParameters;
  for (;;) // A Task shall never return or exit.
  {
      
      if (trava.checarTravaLigada()==true)
      { 
          trava.ligarTrava();
      }    
      
      if (trava.checarTravaDesligada()==true)
      { 
          trava.desligarTrava();
          luz.ligarLuz(500);  //liga a luz por 10 segundos
      }

      static unsigned long ult_tempo = 0;
      int tempo;
      if((linha15.checarLinha15Ligada()==true) && (flagTrava1minuto==0))
      {
          tempo = millis();
          if((tempo - ult_tempo) >= 1000)
          {
              ult_tempo = tempo;
              seg++; 
          }
          if(seg >= 60)
          {
            trava.ligarTrava();
            flagTrava1minuto=1;
          }
      }
      if(linha15.checarLinha15Ligada()==false)
      {
          flagTrava1minuto=0;
          seg=0;
      }
  }
}

 //-----------------------------------------------------------------------------------------------

 //-----------------------------------------------------------------------------------------------
void TaskTeste(void *pvParameters)  
{
     (void) pvParameters;
     
     for(;;)
     {
        Serial.println("Acionar HDMI");
        controleremoto.acionarHDMI();
        delay(5000);
        Serial.println("Acionar VGA");
        controleremoto.acionarVGA();
        delay(5000);
     }
}
 
