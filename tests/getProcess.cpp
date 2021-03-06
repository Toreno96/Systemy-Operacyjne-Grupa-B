// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/ZarzadzaniePamiecia.cpp src/Process.cpp src/ProcessManager.cpp tests/helpers.cpp tests/getProcess.cpp -o tests/getProcess.exe

#include <algorithm>
#include <iostream>
#include <list>
#include "../src/ProcessManager.hpp"
#include "helpers.hpp"

int main() {
  inicjalizacja_PLIKU_WYMIANY();
  ProcessManager processManager;

  processManager.createProcess( "p1", std::string() );
  processManager.createProcess( "p2", std::string(), 1 );
  processManager.createProcess( "p3", std::string(), 2 );
  std::cout << "List of processes after adding three processes:\n\n";
  std::list< Process >& processes = processManager.processes();
  std::for_each( processes.begin(), processes.end(), printProcessData );

  processManager.getProcess( "p2" ).ready();
  processManager.getProcess( "p3" ).ready();
  std::cout << "List of processes after readying all processes:\n\n";
  std::for_each( processes.begin(), processes.end(), printProcessData );

  processManager.getProcess( "p2" ).run();
  std::cout << "List of processes after running process \"p2\":\n\n";
  std::for_each( processes.begin(), processes.end(), printProcessData );

  std::cout << "Running process' name: " << processManager.getRunningProcess().getName() << '\n';
}