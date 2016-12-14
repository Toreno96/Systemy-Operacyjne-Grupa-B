#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "ProcessManager.hpp"
#include "CPU.h"
#include <locale>
//+ pliki i pamiêæ

class Interpreter
{
private:
	ProcessManager* processManager_;
	CPU* cpu_;
	//analogicznie pliki i pamiêæ
	std::map<std::string, std::function<void(std::vector<std::string>)>> instruction;
	void initInstructions();
	bool is_number(const std::string& s);

public:
	Interpreter();
	Interpreter(ProcessManager* pm, CPU* cpu_);
	Register interpreteRegister(std::string reg);
	void loadInstruction();
	void makeInstruction(std::string name, std::vector<std::string>);
	
};