#pragma once
#ifndef  Pipes

#include <iostream>
#include <string>
#include <fstream>
#include "Process.hpp"
#include "Locks.hpp"

class Pipes {
private:
	std::vector<std::string>pipesPaths_;
	std::vector<std::string>waitingForMessage_;

	void newPipe(std::string path);
	std::string getFirstMessage(std::string path);
	void closePipe(std::string path);
	bool isEmpty(std::string path);
	bool isWaiting(std::string path);
	void messageReady(std::string path);

public:
	Pipes();
	~Pipes();
	Lock lock_;
	void sendMessage(Process &runningProcess, Process &process, std::string message);
	void receiveMessage(Process &runningProcess);
	void displayExistingPipes();
	void displayPipeContent(Process &process);
};

#endif
