#ifndef Trava_h
#define Trava_h
#include "Arduino.h" 


class Trava
{
	public:
		Trava();
    boolean checarTravaLigada();
    boolean checarTravaDesligada();
    void Trava::ligarTrava();
    void Trava::desligarTrava(); 
    int Trava::getStatus();
    void Trava::setStatus(int status);
    //void Trava::LigarDesligarTravaManual();
	private:
    //int status;    // status=0 (se a trava estiver desligada)     status=1  (se a trava estiver ligada)
};
// code goes here
#endif
