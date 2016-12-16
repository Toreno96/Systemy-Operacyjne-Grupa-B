#include "CPU.h"


CPU::CPU()
{
}

void CPU::Scheduler(std::list<Process>& processes)
{
	Process* p = nullptr;
	const int instructionsToIncreasePriority = 3;

	for (auto& element : processes)
	{
		if (element.getState() == Process::State::Running || element.getState() == Process::State::Ready)
		{
			if (element.getState() == Process::State::Ready)
			{
				element.increaseCurrentPriorityDuration();
				if (element.getCurrentPriorityDuration() == instructionsToIncreasePriority)
				{
					element.increasePriority();
				}
			}

			if (p == nullptr)
			{
				p = &element;
			}
			else
			{
				if (element.getCurrentPriority() > p->getCurrentPriority())
				{
					if (p->getState() == Process::State::Running)
					{
						p->restoreOriginalPriority();
						p->setState(Process::State::Ready);
						p->setRegistersBackup(registers);
					}
					p = &element;
				}
				else
				{
					if (element.getState() == Process::State::Running)
					{
						element.restoreOriginalPriority();
						element.setState(Process::State::Ready);
						element.setRegistersBackup(registers);
					}
				}
			}
		}	
	}

	if (p->getState() == Process::State::Running)
	{
		if (p->getCurrentPriority() > p->getOriginalPriority())
		{
			p->decreasePriority();
		}
		return;
	}
	else
	{
		p->setState(Process::State::Running);
		registers = p->getRegistersBackup();
		return;
	}

}

Registers * CPU::getRegisters()
{
	return &registers;
}

