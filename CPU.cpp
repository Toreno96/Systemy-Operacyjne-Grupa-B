#include "CPU.h"


CPU::CPU()
{
}

void CPU::Scheduler(std::list<Process>& processes)
{
	Process* processWithBiggestPriority = nullptr;
	const int instructionsToIncreasePriority = 3;

	for (auto& process : processes)
	{
		if (process.getState() == Process::State::Running || process.getState() == Process::State::Ready)
		{
			if (process.getState() == Process::State::Ready)
			{
				process.increaseCurrentPriorityDuration();
				if (process.getCurrentPriorityDuration() == instructionsToIncreasePriority)
				{
					process.increasePriority();
				}
			}

			if (processWithBiggestPriority == nullptr)
			{
				processWithBiggestPriority = &process;
			}
			else
			{
				if (process.getCurrentPriority() > processWithBiggestPriority->getCurrentPriority())
				{
					if (processWithBiggestPriority->getState() == Process::State::Running)
					{
						processWithBiggestPriority->restoreOriginalPriority();
						processWithBiggestPriority->setState(Process::State::Ready);
						processWithBiggestPriority->setRegistersBackup(registers);
					}
					processWithBiggestPriority = &process;
				}
				else
				{
					if (process.getState() == Process::State::Running)
					{
						process.restoreOriginalPriority();
						process.setState(Process::State::Ready);
						process.setRegistersBackup(registers);
					}
				}
			}
		}	
	}

	if (processWithBiggestPriority == nullptr) return;

	if (processWithBiggestPriority->getState() == Process::State::Running)
	{
		if (processWithBiggestPriority->getCurrentPriority() > processWithBiggestPriority->getOriginalPriority())
		{
			processWithBiggestPriority->decreasePriority();
		}
		return;
	}
	else
	{
		processWithBiggestPriority->setState(Process::State::Running);
		registers = processWithBiggestPriority->getRegistersBackup();
		return;
	}

}

Registers * CPU::getRegisters()
{
	return &registers;
}

