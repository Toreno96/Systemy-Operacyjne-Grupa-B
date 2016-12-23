#include <iostream>
#include "../src/ProcessManager.hpp"
#include "../src/helpers.hpp"
#include "../src/Pipes.hpp"

int main() {
	inicjalizacja_PLIKU_WYMIANY();
	ProcessManager processManager;
	Pipes pipes;

	//Utworzenie 3 procesów
	processManager.createProcess("p1", std::string());
	processManager.createProcess("p2", std::string(), 1);
	processManager.createProcess("p3", std::string(), 2);

	processManager.getProcess("p1").ready();
	processManager.getProcess("p2").ready();
	processManager.getProcess("p3").ready();

	processManager.getProcess("p1").run();
	processManager.getProcess("p2").run();
	processManager.getProcess("p3").run();

	//Wysy³anie wiadomoœci do ró¿nych procesów
	pipes.sendMessage(processManager.getProcess("p1"), processManager.getProcess("p2"), "hello");
	pipes.sendMessage(processManager.getProcess("p1"), processManager.getProcess("p2"), "world");
	pipes.sendMessage(processManager.getProcess("p2"), processManager.getProcess("p1"), "usun mnie");

	//Wyœwietlenie potoków i zawartoœci dla ka¿dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomoœci przez proces p2
	pipes.receiveMessage(processManager.getProcess("p2"));
	std::cout << "p2 last received message: " << processManager.getProcess("p2").getLastReceivedMessage() << std::endl;

	//Wyœwietlenie potoków i zawartoœci dla ka¿dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomoœci przez proces p1
	pipes.receiveMessage(processManager.getProcess("p1"));
	std::cout << "p1 last received message: " << processManager.getProcess("p1").getLastReceivedMessage() << std::endl;

	//Wyœwietlenie potoków i zawartoœci dla ka¿dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomoœci przez proces p1
	pipes.receiveMessage(processManager.getProcess("p3"));
	std::cout << "p3 last received message: " << processManager.getProcess("p3").getLastReceivedMessage() << std::endl;

	//Wyœwietlenie potoków i zawartoœci dla ka¿dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomoœci przez proces p1
	pipes.sendMessage(processManager.getProcess("p1"), processManager.getProcess("p3"), "Czy sosna rozdarta?");
	std::cout << "p3 last received message: " << processManager.getProcess("p3").getLastReceivedMessage() << std::endl;

	//Wyœwietlenie potoków i zawartoœci dla ka¿dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	std::cin.ignore(2);
}