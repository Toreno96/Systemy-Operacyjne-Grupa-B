#include "Pipes.hpp"

Pipes::Pipes() {
}

void Pipes::newPipe(std::string path) {
	//Utwórz nowy plik fifo
	std::ofstream fifo_;
	fifo_.open(path, std::ios::trunc);
	fifo_.close();
	pipesPaths_.push_back(path);
}

std::string Pipes::getFirstMessage(std::string path) {
	//Pobierz pierwsz¹ wiadomoœæ
	std::string message;
	std::fstream fifo_;
	fifo_.open(path, std::ios::in | std::ios::out | std::ios::app);
	fifo_ >> message;

	//Pobierz resztê wiadomoœci do vectora
	std::vector<std::string>lines;
	std::string line;
	while (!fifo_.eof()) {
		fifo_ >> line;
		lines.push_back(line);
	}
	fifo_.close();

	//Wyczyœæ plik i wpisz wszystkie wiadomoœci oprócz pierwszej
	fifo_.open(path, std::ios::in | std::ios::out | std::ios::trunc);
	for (auto it = lines.begin(); it != lines.end(); it++) {
		fifo_ << *it;
	}

	return message;
}

void Pipes::closePipe(std::string path) {
	//Usuñ plik
	int i = 0;
	for (auto it = pipesPaths_.begin(); it != pipesPaths_.end(); it++, i++) {
		if (*it == path) {
			pipesPaths_.erase(pipesPaths_.begin() + i);
			pipesPaths_.shrink_to_fit();
			break;
		}
	}
	remove(path.c_str());
}

bool Pipes::isEmpty(std::string path) {
	//SprawdŸ czy potok jest pusty
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
	//Je¿eli istnieje potok o podanej œcie¿ce to wyœlij wiadomoœæ,
	//jeœli nie to utwórz nowy potok i wyœlij wiadomoœæ
	std::string path = process.getName().append(".pipe");

	if (isEmpty(path)) {
		newPipe(path);
	}

	//Wpisz message do pliku
	std::ofstream fifo_;
	fifo_.open(path, std::ios::app);
	if (fifo_.eof()) {
		fifo_ << message;
		lock_.unlock(process);
	}
	else {
		fifo_ << std::endl << message;
		fifo_.close();
	}
}

void Pipes::receiveMessage(Process &runningProcess) {
	//Je¿eli istnieje potok o podanej œcie¿ce to wywo³aj czytanie,
	//jeœli nie to utwórz nowy potok i wywyo³aj czytanie
	std::string path = runningProcess.getName().append(".pipe");
	std::string buffer;

	if (isEmpty(path)) {
		newPipe(path);
	}

	//Wczytaj wiadomoœæ z pliku
	std::fstream fifo_;
	fifo_.open(path, std::ios::in | std::ios::out | std::ios::app);
	if (fifo_.eof()) {
		lock_.lock(runningProcess);
	}
	fifo_.close();
	buffer = getFirstMessage(path);
	runningProcess.setLastReceivedMessage(buffer);

	//Zamknij potok je¿eli zosta³ opró¿niony
	if (isEmpty(path)) {
		closePipe(path);
	}
}

void Pipes::displayExistingPipes() {
	std::cout << "Existing pipes:\n";
	for (auto it = pipesPaths_.begin(); it != pipesPaths_.end(); it++) {
		std::cout << "\t" << *it << "\n";
	}
}

void Pipes::displayPipeContent(Process &process) {
	std::string processName = process.getName();
	std::string path = processName.append(".pipe");

	std::cout << processName << " pipe content:\n";
	for (auto it = pipesPaths_.begin(); it != pipesPaths_.end(); it++) {
		if (*it == path) {
			std::ifstream fifo_;
			fifo_.open(path, std::ios::app);
			std::string line;
			while (!fifo_.eof()) {
				fifo_ >> line;
				std::cout << "\t" << line << "\n";
			}
			fifo_.close();
		}
	}
}