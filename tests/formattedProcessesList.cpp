// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/ZarzadzaniePamiecia.cpp src/Process.cpp src/ProcessManager.cpp tests/formattedProcessesList.cpp -o tests/formattedProcessesList.exe

#include <algorithm>
#include <iostream>
#include <list>
#include "../src/ProcessManager.hpp"

int main() {
  inicjalizacja_PLIKU_WYMIANY();
  ProcessManager processManager;

  processManager.createProcess( "proces1", std::string() );
  processManager.createProcess( "p2", std::string(), 1 );
  processManager.createProcess( "0123456789A", std::string(), 2 );
  std::cout << "List of processes after adding three processes:\n\n";
  std::cout << processManager.getFormattedProcessesList() << '\n';

  processManager.getProcess( "p2" ).ready();
  processManager.getProcess( "0123456789A" ).ready();
  std::cout << "List of processes after readying all processes:\n\n";
  std::cout << processManager.getFormattedProcessesList() << '\n';

  processManager.getProcess( "p2" ).run();
  std::cout << "List of processes after running process \"p2\":\n\n";
  std::cout << processManager.getFormattedProcessesList() << '\n';

  processManager.getProcess( "p2" ).terminate();
  std::cout << "List of processes after terminating process \"p2\":\n\n";
  std::cout << processManager.getFormattedProcessesList() << '\n';

  // Klauzul try-catch powinno byæ oczywiœcie wiêcej, powy¿ej, ale to tylko kod
  // testowy
  try {
    std::cout << "Running process' name: " << processManager.getRunningProcess().getName() << '\n';
  }
  catch( std::logic_error& e ) {
    std::cout << "There's no running process in the system\n";
  }
}