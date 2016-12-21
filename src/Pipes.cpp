#include "Pipes.hpp"

Pipes::Pipes() {
}

Pipes::~Pipes() {
	//Destruktor usuwający wszystkie pliki komunikacyjne
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

bool Pipes::isWaiting(std::string path) {
	for (auto it : waitingForMessage_) {
		if (it == path) {
			return true;
		}
	}

	return false;
}

void Pipes::messageReady(std::string path) {
	int i = 0;
	for (auto it : waitingForMessage_) {
		if (it == path) {
			waitingForMessage_.erase(waitingForMessage_.begin() + i);
			waitingForMessage_.shrink_to_fit();
			break;
		}
		i++;
	}
}

void Pipes::sendMessage(Process &runningProcess, Process &process, std::string message) {
	lock_.lock(runningProcess);
	if (runningProcess.getState() == Process::State::Running) {
		std::string path = process.getName().append(".pipe");

		//Jeżeli potok pusty, to utwórz nowy
		if (isEmpty(path)) {
			newPipe(path);
			std::ofstream fifo;
			fifo.open(path, std::ios::app);
			fifo << message;
			fifo.close();
			//Jeżeli potok nie jest pusty, to pisz kolejną wiadomość
		}
		else {
			std::ofstream fifo;
			fifo.open(path, std::ios::app);
			fifo << std::endl << message;
			fifo.close();
		}
		lock_.unlock(runningProcess);

		//Jeżeli jakiś proces czeka na tą wiadomość to wywołać u niego czytanie wiadomości
		if (isWaiting(path)) {
			messageReady(path);
			process.ready();
			receiveMessage(process);
		}
	}
	else {
		lock_.unlock(runningProcess);
	}
}

void Pipes::receiveMessage(Process &runningProcess) {
	lock_.lock(runningProcess);
	if (runningProcess.getState() == Process::State::Running) {
		std::string path = runningProcess.getName().append(".pipe");

		//Jeżeli potok nie jest pusty to czytaj
		if (!isEmpty(path)) {
			std::string buffer;
			buffer = getFirstMessage(path);
			runningProcess.setLastReceivedMessage(buffer);

			//Jeżeli potok został opróżniony to zamknji potok
			if (isEmpty(path)) {
				closePipe(path);
			}
			//Jeżeli potok jest pusty to utwórz nowy
		}
		else if (isEmpty(path)) {
			newPipe(path);
			waitingForMessage_.push_back(path);
			runningProcess.wait();
		}
		//lock_.unlock(runningProcess);
	}
	else {
		lock_.unlock(runningProcess);
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