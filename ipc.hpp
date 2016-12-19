#pragma once
#ifndef  ipc

#include <iostream>
#include <string>
#include <fstream>
#include "Process.hpp"
#include "Locks.hpp"

class Pipes {
private:
	Lock lock_;
	void newPipe(std::string path);
	void closePipe(std::string path);
	bool isEmpty(std::string path);

public:
	Pipes();
	void sendMessage(Process &process, std::string message);
	void receiveMessage(Process &runningProcess);
};

#endif // ! ipc
