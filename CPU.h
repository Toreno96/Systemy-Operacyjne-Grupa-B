#pragma once
#include "Registers.h"
#include "Process.hpp"
#include <vector>
class CPU
{
private:
	Registers registers;
	Process* running;

public:
	CPU();
	void Scheduler(std::vector<Process>& processes);
};