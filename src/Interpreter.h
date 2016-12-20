#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "ProcessManager.hpp"
#include "CPU.h"
#include <locale>
#include "HardDrive.h"
#include "ZarzadzaniePamiecia.h"
#include "ipc.hpp"

class Interpreter
{
private:
	ProcessManager* processManager_;
	CPU* cpu_;
	HardDrive* hardDrive_;
	Pipes* pipes_;
	std::map<std::string, std::function<void(std::vector<std::string>)>> instruction;
	std::vector <std::string> lastInstruction;

	void initInstructions();
	bool is_number(const std::string& s);
	Register interpreteRegister(std::string reg);
	std::vector<std::string> loadInstruction();
	std::array <char, 8U> convertToFileName(std::string fileName);
	void doInstruction(std::string name, std::vector<std::string>);

public:
	Interpreter(ProcessManager* pm, CPU* cpu_, HardDrive* hd, Pipes* pp);	
	
	std::string getLastInstruction();
	void work();
};