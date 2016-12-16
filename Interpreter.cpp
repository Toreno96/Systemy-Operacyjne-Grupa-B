#include "Interpreter.h"

void Interpreter::initInstructions()
{
	instruction["HLT"] = [this](std::vector<std::string> arguments) {
		for (auto& a : processManager_->processes())
		{
			if (a.getState() == Process::State::Running)
				a.setState(Process::State::Terminated);
		}
	};

	instruction["AD"] = [this](std::vector<std::string> arguments) {

		bool isnumber = is_number(arguments[1]) ? true : false;
		if(isnumber)
		cpu_->getRegisters()->addToRegister(interpreteRegister(arguments[0]), std::stoi(arguments[1]));
		else
		cpu_->getRegisters()->addToRegister(interpreteRegister(arguments[0]), interpreteRegister(arguments[1]));
	};

	instruction["SB"] = [this](std::vector<std::string> arguments) {

		bool isnumber = is_number(arguments[1]) ? true : false;
		if (isnumber)
			cpu_->getRegisters()->subFromRegister(interpreteRegister(arguments[0]), std::stoi(arguments[1]));
		else
			cpu_->getRegisters()->subFromRegister(interpreteRegister(arguments[0]), interpreteRegister(arguments[1]));
	};

	instruction["MU"] = [this](std::vector<std::string> arguments) {

		bool isnumber = is_number(arguments[1]) ? true : false;
		if (isnumber)
			cpu_->getRegisters()->multiplyRegister(interpreteRegister(arguments[0]), std::stoi(arguments[1]));
		else
			cpu_->getRegisters()->multiplyRegister(interpreteRegister(arguments[0]), interpreteRegister(arguments[1]));
	};
	
	instruction["XC"] = [this](std::vector<std::string> arguments) {
	//	processManager_->createProcess(arguments[0], Undefined(programCode)); //****
	};

	instruction["XD"] = [this](std::vector<std::string> arguments) {
		for (auto& a : processManager_->processes())
		{
			if (a.getName() == arguments[0])
				a.setState(Process::State::Terminated);
		}
	};

	instruction["XR"] = [this](std::vector<std::string> arguments) {

	};

	instruction["XS"] = [this](std::vector<std::string> arguments) {

	};

	instruction["XN"] = [this](std::vector<std::string> arguments) {
		
	};

	instruction["XY"] = [this](std::vector<std::string> arguments) {
		for (auto& a : processManager_->processes())
		{
			if (a.getName() == arguments[0])
				a.setState(Process::State::Ready);
		}
	};

	instruction["XZ"] = [this](std::vector<std::string> arguments) {
		for (auto& a : processManager_->processes())
		{
			if (a.getName() == arguments[0])                                //*******
				a.setState(Process::State::Waiting);  
		}
	};

	instruction["JM"] = [this](std::vector<std::string> arguments) {

	};

	instruction["MV"] = [this](std::vector<std::string> arguments) {
		cpu_->getRegisters()->moveToRegister(interpreteRegister(arguments[0]), interpreteRegister(arguments[1]));
	};

	instruction["MN"] = [this](std::vector<std::string> arguments) {
		cpu_->getRegisters()->moveToRegister(interpreteRegister(arguments[0]), std::stoi(arguments[1]));
	};

	instruction["MF"] = [this](std::vector<std::string> arguments) {

	};

	instruction["WF"] = [this](std::vector<std::string> arguments) {

	};

	instruction["WR"] = [this](std::vector<std::string> arguments) {

	};

	instruction["DF"] = [this](std::vector<std::string> arguments) {

	};

	instruction["PO"] = [this](std::vector<std::string> arguments) {

	};

}


Interpreter::Interpreter(ProcessManager * pm, CPU * cpu_, ZarzadzaniePamiecia* zp)
	:processManager_(pm),cpu_(cpu_),zarzadzaniePamiecia_(zp)
{
	initInstructions();
}

Register Interpreter::interpreteRegister(std::string reg)
{
	if (reg == "A")
	{ 
		return Register::A;
	}
	else if (reg == "B")
	{
		return Register::B;
	}
	else if (reg == "C")
	{
		return Register::C;
	}
	else if (reg == "D")
	{
		return  Register::D;
	}


}

std::vector<std::string> Interpreter::loadInstruction()
{
	std::vector <std::string> ins;
	std::string last;
	char ch = '0';
	int adress;
	typ_tablicy_stron tablica_stron;
	for (auto& a : processManager_->processes())
	{
		if (a.getState() == Process::State::Running)
		{
			adress = a.getInstructionCounter();
			//tablica_stron = a.pageTable();
		}
	}

	while (ch != '\n')
	{
	//	ch = zarzadzaniePamiecia_->daj_mi_litere();
		if (ch == '\n');
		else if (ch == ' ' ||ch==',')
		{
			ins.push_back(last);
		}
		else
		{
			last.push_back(ch);
		}
	}

	return ins;

}

void Interpreter::doInstruction(std::string name, std::vector<std::string>arguments)
{
	instruction.at(name)(arguments);
}

void Interpreter::work()
{
	std::vector<std::string> ins_ = loadInstruction();
	std::string name_ = ins_[0];
	ins_.erase(ins_.begin());
	doInstruction(name_, ins_);
}

bool Interpreter::is_number(const std::string& s)
{
	auto it = s.begin();
	while (it != s.end() && ::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
