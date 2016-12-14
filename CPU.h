#pragma once
#include "Registers.h"
#include "Process.hpp"
#include <vector>
class CPU
{
private:
	Registers registers;

public:
	CPU();
	void Scheduler(std::vector<Process>& processes);
	Registers* getRegisters();

};