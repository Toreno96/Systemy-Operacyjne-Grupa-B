#include "Registers.h"
#include <iostream>
#include "Interpreter.h"

int main()
{
	CPU cpus;
	Interpreter interpreter(nullptr, &cpus);
	std::cout << *cpus.getRegisters();
	interpreter.makeInstruction("AD", std::vector<std::string>{"A", "10"});
	std::cout << *cpus.getRegisters();
	interpreter.makeInstruction("AD", std::vector<std::string>{"B", "8"});
	std::cout << *cpus.getRegisters();
	interpreter.makeInstruction("SB", std::vector<std::string>{"A", "B"});
	std::cout << *cpus.getRegisters();
	interpreter.makeInstruction("MU", std::vector<std::string>{"A", "B"});
	std::cout << *cpus.getRegisters();
	std::cin.ignore();
	return 0;
}