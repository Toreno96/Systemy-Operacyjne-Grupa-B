#include<iostream>
#include<deque>
#include<list>
#include<string>

using namespace std;

struct Process
{
	string ID;
	
	bool stan = 1; //ready
};

class Lock
{
public:
	string blocking_ID;
	int value=1;
	deque <Process> waiting_process_list;
	deque <string> blocking_IDs_list;

	void GetValue()
	{
		cout << "Number of processes in queue: " << value << endl;
	}
	void GetProcessName()
	{
		cout << "Name of current process: " << blocking_ID << endl;
	}
	void show_list_of_processes();
	void lock(Process &process);
	void unlock(Process &process);
};
void Lock::show_list_of_processes()
{
	cout << "Names of processes under lock: " << endl;
	int i = 1;
	for (auto process : waiting_process_list)
	{
		cout <<i<<". "<<process.ID  << endl;
		i++;
	}
}
void Lock::lock(Process& process)
{
	
	value--;

	if (value < 0)
	{
		waiting_process_list.push_back(process);
		
		process.stan = 0; //waiting
	}
	
	blocking_IDs_list.push_back(process.ID);

	cout << value << endl;
}

void Lock::unlock(Process &process)
{
	

	if (blocking_IDs_list.front() == process.ID)
	{
		if (value < 1)
		{
			value = value + 1;
		}
		if (value <= 0)
		{
			waiting_process_list.pop_front();
			blocking_IDs_list.pop_front();
			process.stan = 1; //ready
		}
		cout << value << endl;
	}
	else
	{
		cout << "Error" << endl;
	}
}

int main()
{
	Process pro1; pro1.ID = 'a';
	Process pro2; pro2.ID = 'b';
	Process pro3; pro3.ID = 'c';



	Lock zamek1;
	zamek1.lock(pro1);
	zamek1.lock(pro2);
	zamek1.lock(pro3);
	zamek1.show_list_of_processes();
	zamek1.unlock(pro3);
	zamek1.unlock(pro2);
	zamek1.show_list_of_processes();

	getchar();
	getchar();
	return 0;
}