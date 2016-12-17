// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/Process.cpp src/ProcessManager.cpp tests/helpers.cpp tests/processManager.cpp -o tests/processManager.exe

#include <algorithm>
#include <iostream>
#include <list>
#include "../src/Process.hpp"
#include "../src/ProcessManager.hpp"
#include "../src/Undefined.hpp"
#include "helpers.hpp"

int main() {
  ProcessManager processManager;

  processManager.createProcess( "p1", Undefined() );
  processManager.createProcess( "p2", Undefined(), 1 );
  // Powoduje rzucenie wyj¹tku
  //processManager.createProcess( "p2", pPageTable, 2 );
  processManager.createProcess( "p3", Undefined(), 2 );
  std::cout << "List of processes after adding three processes:\n\n";
  std::list< Process >& processes = processManager.processes();
  std::for_each( processes.begin(), processes.end(), printProcessData );

  auto changeStateToTerminated = []( Process& process ) {
        process.ready();
        process.run();
        process.terminate();
      };
  std::for_each( processes.begin(), processes.end(),
      changeStateToTerminated );
  std::cout << "List of processes after changing these processes' state to terminated:\n\n";
  std::for_each( processes.begin(), processes.end(), printProcessData );
  
  std::cout << "List of processes after removing all terminated processes:\n\n";
  processManager.removeTerminatedProcesses();
  std::for_each( processes.begin(), processes.end(), printProcessData );
}