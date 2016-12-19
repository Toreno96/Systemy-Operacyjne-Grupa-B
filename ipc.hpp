#pragma once
#ifndef  ipc

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Process.hpp"
#include "Locks.hpp"

class Pipe {
private:
	std::string path_;
public:
	Pipe(std::string path);
	void newPipe();
	void read(std::string &buffer, Lock &lock, Process &process);
	void write(std::string message, Lock &lock, Process &process);
	void closePipe();
	bool isPipe(std::string path);
	bool isEmpty();
};

class NamedPipes {
private:
	std::vector<Pipe> pipes_;
	Pipe * findPipe(std::string path);
	Lock lock;
public:
	NamedPipes();
	void sendMessage(Process &process, std::string message);
	void receiveMessage(Process &runningProcess);
	void checkPipes();
};

#endif // ! ipc
