#include "Registers.h"
#include <iostream>
#include "Interpreter.h"
#include "ZarzadzaniePamiecia.h"
#include "ProcessManager.hpp"

int main()
{
	CPU cpus;
	ProcessManager pm;
	Interpreter interpreter(&pm, &cpus, nullptr);
	pm.createProcess("kapec", Undefined(), 3);
	pm.createProcess("szlafrok", Undefined(), 4);
	pm.createProcess("hultaj", Undefined(), 4);
	
	for (auto& a : pm.processes())

	{
		a.setState(Process::State::Ready);
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