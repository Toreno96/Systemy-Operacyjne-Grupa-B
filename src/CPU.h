#pragma once
#include "Registers.h"
#include "Process.hpp"
#include <list>
class CPU
{
private:
	Registers registers;

public:
	CPU();
	void Scheduler(std::list<Process>& processes);
	Registers* getRegisters();

};