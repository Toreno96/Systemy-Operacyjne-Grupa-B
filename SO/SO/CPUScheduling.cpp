#include "CPUScheduling.h"

CPUScheduling::CPUScheduling()
	:RUNNING(nullptr), NEXTTRY(nullptr), NEXTTRY_MODIFIED(0)
{
}

PCB * CPUScheduling::get_RUNNING()
{
	return RUNNING;
}

PCB * CPUScheduling::get_NEXTTRY()
{
	return NEXTTRY;
}

void CPUScheduling::set_NEXTTRY(PCB * new_NEXTTRY)
{
	NEXTTRY = new_NEXTTRY;
	NEXTTRY_MODIFIED = 1;
}
