#include "ControleRemoto.h"

#define DISABLE_CODE_FOR_RECEIVER // Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not used.
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

ControleRemoto::ControleRemoto() 
{
    IrSender.begin(DISABLE_LED_FEEDBACK); // Start with IR_SEND_PIN as send pin and disable feedback LED at default feedback LED pin
}

void ControleRemoto::acionarHDMI() 
{

    IrSender.sendNECRaw(0xE01FBF00, 1);
    delay(50);  

}

void ControleRemoto::acionarVGA()
{
    IrSender.sendNECRaw(0xE31DBF00, 1);
    delay(50);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal  
}
