// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/ZarzadzaniePamiecia.cpp src/Process.cpp src/ProcessManager.cpp tests/helpers.cpp tests/pointerToProcess.cpp -o tests/pointerToProcess.exe

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
  processManager.createProcess( "p3", std::string(), 4 );
  processManager.createProcess( "p4", std::string() );
  std::cout << "List of processes after adding four processes:\n\n";
  std::list< Process >& processes = processManager.processes();
  std::for_each( processes.begin(), processes.end(), printProcessData );

  auto itProcess = std::find_if( processes.begin(), processes.end(),
      []( const Process& process ){ return process.getName() == "p3"; } );
  Process* pProcess = &( *itProcess );
  pProcess->ready();

  std::cout << "List of processes after changing third process' state:\n\n";
  std::for_each( processes.begin(), processes.end(), printProcessData );
}