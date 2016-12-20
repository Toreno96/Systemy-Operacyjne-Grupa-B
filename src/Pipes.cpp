#include "Pipes.hpp"

Pipes::Pipes() {
}

Pipes::~Pipes() {
	for (auto it : pipesPaths_) {
		remove(it.c_str());
	}
}

void Pipes::newPipe(std::string path) {
	//Utw�rz nowy plik fifo
	std::ofstream fifo_;
	fifo_.open(path, std::ios::trunc);
	fifo_.close();
	pipesPaths_.push_back(path);
}

std::string Pipes::getFirstMessage(std::string path) {
	//Pobierz pierwsz� wiadomo��
	std::fstream fifo_;
	fifo_.open(path, std::ios::in | std::ios::out | std::ios::app);
	std::string message;
	std::getline(fifo_, message);

	//Pobierz reszt� wiadomo�ci do vectora
	std::vector<std::string>lines;
	std::string line;
	while (std::getline(fifo_, line)) {
		lines.push_back(line);
	}
	fifo_.close();

	//Wyczy�� plik i wpisz wszystkie wiadomo�ci opr�cz pierwszej
	fifo_.open(path, std::ios::in | std::ios::out | std::ios::trunc);
	bool begin = true;
	for (auto it : lines) {
		if (!begin) {
			fifo_ << std::endl << it;
		}
		else {
			fifo_ << it;
			begin = false;
		}
	}

	return message;
}

void Pipes::closePipe(std::string path) {
	//Usu� plik
	int i = 0;
	for (auto it : pipesPaths_) {
		if (it == path) {
			pipesPaths_.erase(pipesPaths_.begin() + i);
			pipesPaths_.shrink_to_fit();
			break;
		}
		i++;
	}
	remove(path.c_str());
}

bool Pipes::isEmpty(std::string path) {
	//Sprawd� czy potok jest pusty
	std::ifstream fifo_;
	fifo_.open(path);
	if (fifo_.peek() == std::ifstream::traits_type::eof()) {
		fifo_.close();
		return true;
	}
	else {
		return false;
	}
}

void Pipes::sendMessage(Process &process, std::string message) {
	//Je�eli istnieje potok o podanej �cie�ce to wy�lij wiadomo��,
	//je�li nie to utw�rz nowy potok i wy�lij wiadomo��
	std::string path = process.getName().append(".pipe");

	if (isEmpty(path)) {
		newPipe(path);
		std::ofstream fifo_;
		fifo_.open(path, std::ios::app);
		fifo_ << message;
		//lock_.unlock(process);
		fifo_.close();
	}else {
		std::ofstream fifo_;
		fifo_.open(path, std::ios::app);
		fifo_ << std::endl << message;
		fifo_.close();
	}
}

void Pipes::receiveMessage(Process &runningProcess) {
	//Je�eli istnieje potok o podanej �cie�ce to wywo�aj czytanie,
	//je�li nie to utw�rz nowy potok i wywyo�aj czytanie
	std::string path = runningProcess.getName().append(".pipe");
	std::string buffer;

	if (isEmpty(path)) {
		newPipe(path);
		//lock_.lock(runningProcess);
	}

	buffer = getFirstMessage(path);
	runningProcess.setLastReceivedMessage(buffer);

	//Zamknij potok je�eli zosta� opr�niony
	if (isEmpty(path)) {
		closePipe(path);
	}
}

void Pipes::displayExistingPipes() {
	std::cout << "Existing pipes:\n";
	for (auto it : pipesPaths_) {
		std::cout << "\t" << it << "\n";
	}
}

void Pipes::displayPipeContent(Process &process) {
	std::string processName = process.getName();
	std::string path = processName;
	path.append(".pipe");

	std::cout << processName << " pipe content:\n";
	for (auto it : pipesPaths_) {
		if (it == path) {
			std::ifstream fifo_;
			fifo_.open(path, std::ios::app);
			std::string line;
			while (std::getline(fifo_, line)) {
				std::cout << "\t" << line << "\n";
			}
			fifo_.close();
		}
	}
}