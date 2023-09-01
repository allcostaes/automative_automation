#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "Trava.h"



//-------------------------------------------------   MÓDULO RELÉ    -----------------------------------------------------------
//  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// DISPOSITIVO: 
// PORTA ARDUINO: 2       RELE IN:2         COR DO FIO:  MARRON
int portaRele2 = 2;
int portaRele3 = 3;
int portaRele4 = 4;
int portaRele5 = 5; 


// Botão para ligar e desligar a trava manualmente
#define botaoTravaManual 36  



Trava::Trava()
{
  //status=0;
  // Define pinos para o rele como saída
  pinMode(portaRele2, OUTPUT); 
  pinMode(portaRele3, OUTPUT); 
  pinMode(portaRele4, OUTPUT); 
  pinMode(portaRele5, OUTPUT); 
// Inicializa relés desligados
  digitalWrite(portaRele2, HIGH);
  digitalWrite(portaRele3, HIGH);
  digitalWrite(portaRele4, HIGH);
  digitalWrite(portaRele5, HIGH);
  // botão para acionamento manual da trava
  pinMode(botaoTravaManual, INPUT_PULLUP);
};

boolean Trava::checarTravaLigada()   // DETECTA SE A TRAVA FOI ACIONADA PELO ALARME OU MANUALMENTE
{
    float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
    float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
    float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
    float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
    int leituraSensorTensao = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO

    for(int i=0;i<500;i++)
    {
      analogRead(A10);
      leituraSensorTensao = analogRead(A10); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
      tensaoEntrada = (leituraSensorTensao * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
      tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
      if(tensaoMedida>1)
        break;
    }
    
    //Serial.print("TRAVA   -  Pino A10: ");
    //Serial.print(tensaoMedida);
    //Serial.print("\n");



    if (  (tensaoMedida>1)  ||  ((digitalRead(botaoTravaManual)==0) ) )
    { 
       status=1;
       return true;
    }else
    {
       return false;
    }
};

boolean Trava::checarTravaDesligada()   // DETECTA SE A TRAVA FOI DESLIGADA PELO ALARME OU MANUALMENTE
{
    float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
    float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
    float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
    float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
    int leituraSensorTensao = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO

    
    for(int i=0;i<500;i++)
    {
      analogRead(A11);
      leituraSensorTensao = analogRead(A10); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
      tensaoEntrada = (leituraSensorTensao * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
      tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
      if(tensaoMedida>1)
        break;
    }
    //Serial.print("DESTRAVA - Pino A11: ");
    //Serial.print(tensaoMedida);
    //Serial.print("\n");
   if ( (tensaoMedida>1) || ((digitalRead(botaoTravaManual)==0) && (status==1))  )
    { 
        status=0;
        return true;
    }else
    {
        return false;
    }
};


void Trava::ligarTrava()   // LIGAR A TRAVA
{
    digitalWrite(portaRele4, LOW);
    digitalWrite(portaRele5, LOW);
    vTaskDelay(100);
    digitalWrite(portaRele4, HIGH);
    digitalWrite(portaRele5, HIGH);
    this->status=1;
    vTaskDelay(100);
};

void Trava::desligarTrava()   // DESLIGAR A TRAVA
{
    digitalWrite(portaRele2, LOW);
    digitalWrite(portaRele3, LOW);
    vTaskDelay(100);
    digitalWrite(portaRele2, HIGH);
    digitalWrite(portaRele3, HIGH);
    this->status=0;    
    vTaskDelay(100);
};


int Trava::getStatus()
{
    return this->status;  
};

void Trava::setStatus(int status)
{
    this->status=status;
};
/*
void Trava::LigarDesligarTravaManual()
{
      
      byte buttonState = digitalRead(botaoTravaManual);
      
      if (buttonState == LOW) 
      {
            //Serial.println("Button is pressed");
            if (getStatus()==0)
            { 
                ligarTrava();
            }    
            
            else //(trava.getStatus()==1)
            { 
                desligarTrava();
            }
      }
      else 
      {
            //Serial.println("Button is not pressed");
      }
      delay(50);
};

*/
