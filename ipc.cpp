#include "ipc.hpp"

Pipes::Pipes() {
}

void Pipes::newPipe(std::string path) {
	//Utwórz nowy plik fifo
	std::ofstream fifo_;
	fifo_.open(path, std::ios::trunc);
	fifo_.close();
}

void Pipes::closePipe(std::string path) {
	//Usuñ plik
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
		lock_.lock(process);
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

	//Wczytaj wiadomoœæ z pliku do buffera
	std::fstream fifo_;
	fifo_.open(path, std::ios::in | std::ios::out | std::ios::app);
	if (fifo_.eof()) {
		lock_.lock(runningProcess);
	}
	fifo_ >> buffer;

	//Pobierz wszystkie wiadomoœci
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

	runningProcess.setLastReceivedMessage(buffer);

	if (isEmpty(path)) {
		closePipe(path);
	}
}