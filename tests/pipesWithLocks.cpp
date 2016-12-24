#include <iostream>
#include "../src/ProcessManager.hpp"
#include "../src/helpers.hpp"
#include "../src/Pipes.hpp"

int main() {
	inicjalizacja_PLIKU_WYMIANY();
	ProcessManager processManager;
	Pipes pipes;

	//Utworzenie 3 proces�w
	processManager.createProcess("p1", std::string());
	processManager.createProcess("p2", std::string(), 1);
	processManager.createProcess("p3", std::string(), 2);

	processManager.getProcess("p1").ready();
	processManager.getProcess("p2").ready();
	processManager.getProcess("p3").ready();

	processManager.getProcess("p1").run();
	processManager.getProcess("p2").run();
	processManager.getProcess("p3").run();

	//Wysy�anie wiadomo�ci do r�nych proces�w
	pipes.sendMessage(processManager.getProcess("p1"), processManager.getProcess("p2"), "hello");
	pipes.sendMessage(processManager.getProcess("p1"), processManager.getProcess("p2"), "world");
	pipes.sendMessage(processManager.getProcess("p2"), processManager.getProcess("p1"), "usun mnie");

	//Wy�wietlenie potok�w i zawarto�ci dla ka�dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomo�ci przez proces p2
	pipes.receiveMessage(processManager.getProcess("p2"));
	std::cout << "p2 last received message: " << processManager.getProcess("p2").getLastReceivedMessage() << std::endl;

	//Wy�wietlenie potok�w i zawarto�ci dla ka�dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomo�ci przez proces p1
	pipes.receiveMessage(processManager.getProcess("p1"));
	std::cout << "p1 last received message: " << processManager.getProcess("p1").getLastReceivedMessage() << std::endl;

	//Wy�wietlenie potok�w i zawarto�ci dla ka�dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomo�ci przez proces p1
	pipes.receiveMessage(processManager.getProcess("p3"));
	std::cout << "p3 last received message: " << processManager.getProcess("p3").getLastReceivedMessage() << std::endl;

	//Wy�wietlenie potok�w i zawarto�ci dla ka�dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	//Odczyt wiadomo�ci przez proces p1
	pipes.sendMessage(processManager.getProcess("p1"), processManager.getProcess("p3"), "Czy sosna rozdarta?");
	std::cout << "p3 last received message: " << processManager.getProcess("p3").getLastReceivedMessage() << std::endl;

	//Wy�wietlenie potok�w i zawarto�ci dla ka�dego procesu
	pipes.displayExistingPipes();
	pipes.displayPipeContent(processManager.getProcess("p1"));
	pipes.displayPipeContent(processManager.getProcess("p2"));
	pipes.displayPipeContent(processManager.getProcess("p3"));

	std::cin.ignore(2);
}