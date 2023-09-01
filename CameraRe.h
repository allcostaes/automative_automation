#ifndef CameraRe_h
#define CameraRe_h
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "Re.h"
#include "Linha15.h"
#include <util/atomic.h>
//#include "ControleRemoto.h"



class CameraRe
{
  public:
	CameraRe();
  void CameraRe::LigarDesligarCameraRe();
  int portaAV1AV2Monitor;
  boolean reLigada;
  Re re;
  Linha15 linha15;
  
};
// code goes here
#endif
