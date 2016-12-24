#include<iostream>
#include<deque>
#include<string>
#include"Process.hpp"
#include"Locks.hpp"
void Lock::showListOfProcesses()
{
	std::cout << "Names of processes under lock: " << std::endl;
	int i = 1;
	for (auto process : waiting_process_list)
	{
		std::cout << i << ". " << process.get().getName() << std::endl;
		i++;
	}
}
std::string Lock::getProcessName()
{
		return blocking_IDs_list.front();
}
void Lock::displayProcessName()
{
		std::cout << "Name of first process under lock: " << blocking_IDs_list.front() << std::endl;
}
int Lock::getValue()
{
		return abs(value);
}
void Lock::displayValue()
{
	std::cout << "Number of processes in queue: " << abs(value) << std::endl;
}

void Lock::lock(Process& process)
{

	value--;

	if (value < 0)
	{
		waiting_process_list.push_back(std::ref(process));
		blocking_IDs_list.push_back(process.getName());
		process.wait();//oczekuje
	}
}
bool Lock::unlock(Process &process)
{
	if (blocking_IDs_list.empty())
	{
		value++;
		return 0;
	}
	else
	{
		if (blocking_IDs_list[0] == process.getName())
		{
			if (value < 1)
			{
				value++;
			}
			if (value <= 0)
			{
				waiting_process_list.pop_front();
				blocking_IDs_list.pop_front();
				process.ready();//gotowosc
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
