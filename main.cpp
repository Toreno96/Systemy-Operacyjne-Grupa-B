#include "Registers.h"
#include <iostream>
#include "Interpreter.h"
#include "ProcessManager.hpp"
#include "HardDrive.h"
int main()
{
	CPU cpus;
	ProcessManager pm;
	HardDrive hd;
	Interpreter interpreter(&pm, &cpus, &hd);
	pm.createProcess("kapec", "1", 3);
	pm.createProcess("szlafrok", "2", 4);
	pm.createProcess("hultaj", "3", 4);
	
	for (auto& a : pm.processes())

	{
		a.ready();
	}
	
	for (int i = 0; i < 10; i++)
	{
		cpus.Scheduler(pm.processes());
		interpreter.doInstruction("SB", std::vector<std::string>{"B", "5"});
		std::cout << *cpus.getRegisters();
	}
	


	std::cin.ignore();
	
	return 0;
}