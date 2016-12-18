#include<iostream>
#include<deque>
#include<string>
#include"Process.hpp"
#include"Undefined.hpp"
#include"Locks.hpp"
void Lock::Show_List_of_Processes()
{
	std::cout << "Names of processes under lock: " << std::endl;
	int i = 1;
	for (auto process : waiting_process_list)
	{
		std::cout << i << ". " << process.get().getName() << std::endl;
		i++;
	}
}
std::string Lock::GetProcessName()
{
		std::cout << "Name of first process under lock: " << blocking_IDs_list.front() << std::endl;
		return blocking_IDs_list.front();
}
int Lock::GetValue()
{
		std::cout << "Number of processes in queue: " << abs(value) << std::endl;
		return abs(value);
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
void Lock::unlock(Process &process)
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
		}
		else
		{
			std::cout << "Error" << std::endl;
		}
}

