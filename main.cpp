#include "Registers.h"
#include <iostream>
#include "Interpreter.h"

int main()
{
	CPU cpus;
	Interpreter interpreter(nullptr, &cpus);
	ProcessManager pm;
	pm.createProcess("pierwszy", Undefined(), 3);
	pm.createProcess("drugi", Undefined(), 5);
	pm.createProcess("trzeci", Undefined(), 5);


	int i = 30;
	while(i>0)
	{
		cpus.Scheduler(pm.processes());
		for (auto p : pm.processes())
		{
			if (p.getState() == Process::State::Running)
				std::cout << p.getName() << " " << p.getCurrentPriority() << std::endl;
				
		}

		i--;
		
	}


	std::cin.ignore();
	return 0;
}