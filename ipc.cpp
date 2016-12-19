#include "ipc.hpp"
#include <string>

Pipe::Pipe(std::string path) {
	path_ = path.append(".pipe");
}

void Pipe::newPipe() {
	//Utw�rz nowy plik fifo
	std::ofstream fifo_;
	fifo_.open(path_, std::ios::trunc);
	fifo_.close();
}

void Pipe::read(std::string &buffer, Lock &lock, Process &process) {
	//Wczytaj wiadomo�� z pliku do buffera
	std::fstream fifo_;
	fifo_.open(path_, std::ios::in | std::ios::out | std::ios::app);
	if (fifo_.eof()) {
		lock.lock(process);
	}
	fifo_ >> buffer;

	//Pobierz wszystkie wiadomo�ci
	std::vector<std::string>lines;
	std::string line;
	while (!fifo_.eof()) {
		fifo_ >> line;
		lines.push_back(line);
	}
	fifo_.close();

	//Wyczy�� plik i wpisz wszystkie wiadomo�ci opr�cz pierwszej
	fifo_.open(path_, std::ios::in | std::ios::out | std::ios::trunc);
	for (auto it = lines.begin(); it != lines.end(); it++) {
		fifo_ << *it;
	}
}

void Pipe::write(std::string message, Lock &lock, Process &process) {
	//Wpisz message do pliku
	std::ofstream fifo_;
	fifo_.open(path_, std::ios::app);
	if (fifo_.eof()) {
		fifo_ << message;
		lock.unlock(process);
	}
	else {
		fifo_ << std::endl << message;
		fifo_.close();
	}
}

void Pipe::closePipe() {
	//Usu� plik
	remove(path_.c_str());
}

bool Pipe::isPipe(std::string path) {
	//sprawd� czy podana scie�ka zgadza si� z t� �cie�k�
	if (path_ == path.append(".pipe")) {
		return true;
	}
	else {
		return false;
	}
}

bool Pipe::isEmpty(){
	//Sprawd� czy potok jest pusty
	std::ifstream fifo_;
	fifo_.open(path_);
	if (fifo_.peek() == std::ifstream::traits_type::eof()) {
		fifo_.close();
		return true;
	}
	else {
		return false;
	}
}

NamedPipes::NamedPipes() {

}

Pipe * NamedPipes::findPipe(std::string path) {
	//Zwr�� wska�nik na potok o podanej �cie�ce
	for (auto it = pipes_.begin(); it != pipes_.end(); it++) {
		if (it->isPipe(path)) {
			return &(*it);
		}
	}

	return nullptr;
}

void NamedPipes::sendMessage(Process &process, std::string message) {
	//Je�eli istnieje potok o podanej �cie�ce to wy�lij wiadomo��,
	//je�li nie to utw�rz nowy potok i wy�lij wiadomo��
	std::string path = process.getName();
	Pipe * pipe = findPipe(path);

	if (pipe == nullptr) {
		pipe = new Pipe(path);
		pipes_.push_back(*pipe);
		pipe = findPipe(path);
		pipe->newPipe();
	}

	pipe->write(message, lock, process);
}

void NamedPipes::receiveMessage(Process &runningProcess) {
	//Je�eli istnieje potok o podanej �cie�ce to wywo�aj czytanie,
	//je�li nie to utw�rz nowy potok i wywyo�aj czytanie
	std::string path = runningProcess.getName();
	std::string buffer;

	Pipe * pipe = findPipe(path);

	if (pipe == nullptr) {
		pipe = new Pipe(path);
		pipes_.push_back(*pipe);
		pipe = findPipe(path);
		pipe->newPipe();
	}

	pipe->read(buffer, lock, runningProcess);
	runningProcess.setLastReceivedMessage(buffer);
}

void NamedPipes::checkPipes() {
	//Usu� potok je�eli pusty
	int i = 0;
	for (auto it = pipes_.begin(); it != pipes_.end(); it++, i++) {
		if (it->isEmpty()) {
			it->closePipe();
			pipes_.erase(pipes_.begin() + i);
			pipes_.shrink_to_fit();
			it = pipes_.begin();
		}
	}
}