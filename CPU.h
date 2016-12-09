#pragma once
#include "Registers.h"
#include "Process.hpp"
#include <vector>
class CPU
{
private:
	Registers registers;
	Process* running;

	const int guzikZPetelka; //mo¿e inna nazwa by siê przyda³a, bo ta mo¿e nie byæ oczywista

public:
	CPU();
	void Scheduler(std::vector<Process>& processes);


};