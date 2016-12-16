#include "Registers.h"
#include <iostream>
#include "Interpreter.h"
#include "ZarzadzaniePamiecia.h"

int main()
{
	CPU cpus;
	ProcessManager pm;
	//ZarzadzaniePamiecia zp;
	//Interpreter interpreter(&pm, &cpus, nullptr);
	pm.createProcess("kapec", Undefined(), 6);
	pm.createProcess("szlafrok", Undefined(), 8);
	pm.createProcess("hultaj", Undefined(), 7);
	cpus.Scheduler(pm.processes());
	//cpus.Scheduler(pm.processes());
	//std::cout << cpus.getRegisters();


	std::cin.ignore();
	
	return 0;
}