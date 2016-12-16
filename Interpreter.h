#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "ProcessManager.hpp"
#include "CPU.h"
#include <locale>
#include "ZarzadzaniePamiecia.h"
//+ stumyki i pamiêæ

class Interpreter
{
private:
	ProcessManager* processManager_;
	CPU* cpu_;
	ZarzadzaniePamiecia* zarzadzaniePamiecia_;
	//analogicznie pliki i komunikacja
	std::map<std::string, std::function<void(std::vector<std::string>)>> instruction;
	void initInstructions();
	bool is_number(const std::string& s);
	Register interpreteRegister(std::string reg);
	std::vector<std::string> loadInstruction();
	void doInstruction(std::string name, std::vector<std::string>);

public:
	Interpreter(ProcessManager* pm, CPU* cpu_, ZarzadzaniePamiecia* zp);	
	void work();
};