#pragma once
#ifndef  Pipes

#include <iostream>
#include <string>
#include <fstream>
#include "Process.hpp"
#include "Locks.hpp"

class Pipes {
private:
	std::vector<string>pipesPaths_;
	Lock lock_;
	void newPipe(std::string path);
	std::string getFirstMessage(std::string path);
	void closePipe(std::string path);
	bool isEmpty(std::string path);

public:
	Pipes();
	~Pipes();
	void sendMessage(Process &process, std::string message);
	void receiveMessage(Process &runningProcess);
	void displayExistingPipes();
	void displayPipeContent(Process &process);
};

#endif
