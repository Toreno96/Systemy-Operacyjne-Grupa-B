#pragma once
#include "pcb.h"

class CPUScheduling
{
private:
	PCB* RUNNING;				//WSKA�NIK DO BLOKU PCB W�A�NIE WYKONYWANEGO
	PCB* NEXTTRY;				//WSKA�NIK DO BLOKU PCB, KT�RY ZAWIADOWCA B�DZIE STARA� SI� USTAWI� JAKO NAST�PNY = RUNNING->NEXT_PCB_ALL
	bool NEXTTRY_MODIFIED;		//R�WNY ZERU, JE�LI WSKA�NIK NEXTTRY NIE ZMIANIA� SI� OD CHWILI NADANIA MU WARTO�CI PRZEZ ZAWIADOWC�


public:
	CPUScheduling();
	
	PCB* get_RUNNING();
	PCB* get_NEXTTRY();
	void set_NEXTTRY(PCB* new_NEXTTRY);

};