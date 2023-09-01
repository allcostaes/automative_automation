#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "Linha15.h"

Linha15::Linha15()
{
}

boolean Linha15::checarLinha15Ligada()   // LIGAR A LUZ POR ALGUNS SEGUNDOS
{
    float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
    float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
    float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
    float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
    int leituraSensorTensao = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO

    analogRead(A1);
    delay(20);
    leituraSensorTensao = analogRead(A1); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
    tensaoEntrada = (leituraSensorTensao * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
    tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR

    if (tensaoMedida>1)
    { 
       return true;
    }else
    {
       return false;
    }
};
