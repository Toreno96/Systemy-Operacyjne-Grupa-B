#include "CPU.h"


CPU::CPU()
	:running(nullptr)
{
}

void CPU::Scheduler(std::vector<Process>& processes)
{
	const int instructionsToIncreasePriority = 5;

	Process* processWithBiggestPriority = &processes[0];

	for (auto p: processes)
	{
		if (p.getState() == Process::State::Ready)
		{
			if (running != nullptr)
			{
				p.increaseCurrentPriorityDuration();
				
				if (p.getCurrentPriorityDuration() >= instructionsToIncreasePriority)
				{
					p.increasePriority();
				}
			}

			if (p.getCurrentPriority() > processWithBiggestPriority->getCurrentPriority()) //zapewnia FIFO, dla procesów o równych priorytetach
			{
				processWithBiggestPriority = &p; 
			}
		}
	}

	if (processWithBiggestPriority->getName() != running->getName())
	{
		if (running != nullptr)
		{
			if(running->getState()==Process::State::Running)    //tu¿ po zablokowaniu procesu on nadal jest pod running*
			running->setState(Process::State::Ready);
			running->restoreOriginalPriority();
			running->setRegistersBackup(registers);
		}

		running = processWithBiggestPriority;
		running->setState(Process::State::Running);
		registers = running->getRegistersBackup();
	}
}

