#include "Interpreter.h"

const std::array<char, 3U> ext{ 't','x','t' };

void Interpreter::initInstructions()
{
	instruction["HLT"] = [this](std::vector<std::string> arguments) {
		processManager_->getRunningProcess().terminate();
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
		std::string programCode;
		if(hardDrive_->read_file(convertToFileName(arguments[1]),ext,programCode))
		processManager_->createProcess(arguments[0],programCode);
	};

	instruction["XD"] = [this](std::vector<std::string> arguments) {
		processManager_->getProcess(arguments[0]).terminate();
	};

	instruction["XR"] = [this](std::vector<std::string> arguments) {
		pipes_.receiveMessage(processManager_->getRunningProcess());
	};

	instruction["XS"] = [this](std::vector<std::string> arguments) {
		pipes_.sendMessage(arguments[0], arguments[1]);
	};

	instruction["XN"] = [this](std::vector<std::string> arguments) {
		for (auto& process: processManager_->processes())
		{
			if (process.getName() == arguments[0]) {
				cpu_->getRegisters()->moveToRegister(Register::A, 1);
				return;
			}
		}
		cpu_->getRegisters()->moveToRegister(Register::A, 0);

	};

	instruction["XY"] = [this](std::vector<std::string> arguments) {
		processManager_->getProcess(arguments[0]).ready();
	};

	instruction["XZ"] = [this](std::vector<std::string> arguments) {
		processManager_->getProcess(arguments[0]).wait();
	};

	instruction["JM"] = [this](std::vector<std::string> arguments) {
		
		processManager_->getRunningProcess().setInstructionCounter(processManager_->getRunningProcess().getLabelAddress(arguments[0]));
	};

	instruction["MV"] = [this](std::vector<std::string> arguments) {
		cpu_->getRegisters()->moveToRegister(interpreteRegister(arguments[0]), interpreteRegister(arguments[1]));
	};

	instruction["MN"] = [this](std::vector<std::string> arguments) {
		cpu_->getRegisters()->moveToRegister(interpreteRegister(arguments[0]), std::stoi(arguments[1]));
	};

	instruction["MF"] = [this](std::vector<std::string> arguments) {
		hardDrive_->create_empty_file(convertToFileName(arguments[0]), ext);
	};

	instruction["WF"] = [this](std::vector<std::string> arguments) {
		hardDrive_->append_string_to_file(convertToFileName(arguments[0]), ext, arguments[1]);
	};

	instruction["WR"] = [this](std::vector<std::string> arguments) {
		hardDrive_->append_string_to_file(convertToFileName(arguments[0]), ext, std::to_string(cpu_->getRegisters()->getRegister(interpreteRegister(arguments[1]))));
	};

	instruction["DF"] = [this](std::vector<std::string> arguments) {
		hardDrive_->delete_file(convertToFileName(arguments[0]), ext);
	};

	instruction["PO"] = [this](std::vector<std::string> arguments) {
		std::cout << arguments[0] << std::endl; //???
	};

}


Interpreter::Interpreter(ProcessManager * pm, CPU * cpu_, HardDrive* hd, Pipes* pp)
	:processManager_(pm),cpu_(cpu_),hardDrive_(hd),pipes_(pp)
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
	typ_tablicy_stron pageTable;
	
			adress = processManager_->getRunningProcess().getInstructionCounter();
			pageTable = processManager_->getRunningProcess().pageTable();
		
	

	while (ch != '\n')
	{
	ch = daj_mi_litere(adress, pageTable);
	adress++;
		if (ch == '\n')
		{

		}
		else if (ch == ' ' ||ch==',')
		{
			ins.push_back(last);
		}
		else if (ch == ':')
		{
			processManager_->getRunningProcess().saveLabelAddress(last,adress+1);
			return std::vector <std::string> {};
		}
		else
		{
			last.push_back(ch);
		}
	}

	processManager_->getRunningProcess().setInstructionCounter(adress);

	return ins;

}

std::array<char, 8U> Interpreter::convertToFileName(std::string fileName)
{
	std::array <char, 8U> fileName_converted;
	for (int i = 0; i < 8; i++)
	{
		fileName_converted[i] = fileName[i];
	}

	return fileName_converted;
}

void Interpreter::doInstruction(std::string name, std::vector<std::string>arguments)
{
	instruction.at(name)(arguments);
}

void Interpreter::work()
{
	std::vector<std::string> ins_ = loadInstruction();
	if (ins_.empty()) return;
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
