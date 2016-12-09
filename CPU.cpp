#include "CPU.h"

CPU::CPU()
	:running(nullptr), guzikZPetelka(5)
{
}

void CPU::Scheduler(std::vector<Process>& processes)
{
	Process* processWithBiggestPriority = &processes[0];
	for (auto p: processes)
	{
		if (p.getState() == Process::State::Ready)
		{
			if (running != nullptr)
			{
				p.increaseCurrentPriorityDuration();
				
				if (p.getCurrentPriorityDuration() >= guzikZPetelka)
				{
					p.increasePriority();
				}
			}


			if (p.getCurrentPriority() > processWithBiggestPriority->getCurrentPriority) //zapewnia fifo
			{
				processWithBiggestPriority = &p; 
			}
		}
	}

	if (processWithBiggestPriority != running)
	{
		if (running != nullptr)
		{
			running->setState(Process::State::Ready);
			running->restoreOriginalPriority();
			running->setRegistersBackup(registers);
			processWithBiggestPriority->setState(Process::State::Running);
			registers = processWithBiggestPriority->getRegistersBackup();
			running = processWithBiggestPriority;
		}
	}
}

