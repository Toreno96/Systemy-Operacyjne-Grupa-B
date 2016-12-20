#include "Pipes.hpp"

Pipes::Pipes() {
}

Pipes::~Pipes() {
	for (auto it : pipesPaths_) {
		remove(it.c_str());
	}
}

void Pipes::newPipe(std::string path) {
	//Utwórz nowy plik fifo
	std::ofstream fifo;
	fifo.open(path, std::ios::trunc);
	fifo.close();
	pipesPaths_.push_back(path);
}

std::string Pipes::getFirstMessage(std::string path) {
	//Pobierz pierwszą wiadomość
	std::fstream fifo;
	fifo.open(path, std::ios::in | std::ios::out | std::ios::app);
	std::string message;
	std::getline(fifo, message);

	//Pobierz resztę wiadomości do vectora
	std::vector<std::string>lines;
	std::string line;
	while (std::getline(fifo, line)) {
		lines.push_back(line);
	}
	fifo.close();

	//Wyczyść plik i wpisz wszystkie wiadomości oprócz pierwszej
	fifo.open(path, std::ios::in | std::ios::out | std::ios::trunc);
	bool begin = true;
	for (auto it : lines) {
		if (!begin) {
			fifo << std::endl << it;
		}
		else {
			fifo << it;
			begin = false;
		}
	}

	return message;
}

void Pipes::closePipe(std::string path) {
	//Usuń path z prywatnego vectora
	int i = 0;
	for (auto it : pipesPaths_) {
		if (it == path) {
			pipesPaths_.erase(pipesPaths_.begin() + i);
			pipesPaths_.shrink_to_fit();
			break;
		}
		i++;
	}

	//Usuń plik
	remove(path.c_str());
}

bool Pipes::isEmpty(std::string path) {
	//Sprawdź czy plik jest pusty
	std::ifstream fifo;
	fifo.open(path);
	if (fifo.peek() == std::ifstream::traits_type::eof()) {
		fifo.close();
		return true;
	}
	else {
		return false;
	}
}

void Pipes::sendMessage(Process &process, std::string message) {
	//Jeżeli istnieje potok o podanej ścieżce to wyślij wiadomość,
	//jeśli nie to utwórz nowy potok i wyślij wiadomość
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
	//Jeżeli istnieje potok o podanej ścieżce to wywołaj czytanie,
	//jeśli nie to utwórz nowy potok i wywyołaj czytanie
	std::string path = runningProcess.getName().append(".pipe");
	std::string buffer;

	if (isEmpty(path)) {
		newPipe(path);
		//lock_.lock(runningProcess);
	}

	buffer = getFirstMessage(path);
	runningProcess.setLastReceivedMessage(buffer);

	//Zamknij potok jeżeli został opróżniony
	if (isEmpty(path)) {
		closePipe(path);
	}
}

void Pipes::displayExistingPipes() {
	//Wyświetl istniejące potoki
	std::cout << "Existing pipes:\n";
	for (auto it : pipesPaths_) {
		std::cout << "\t" << it << "\n";
	}
}

void Pipes::displayPipeContent(Process &process) {
	//Wyświetl zawartość potoku dla danego procesu
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
			break;
		}
	}
}