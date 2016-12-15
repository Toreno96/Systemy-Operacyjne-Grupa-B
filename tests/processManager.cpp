#include <algorithm>
#include <iostream>
#include <vector>
#include "../src/Process.hpp"
#include "../src/ProcessManager.hpp"
#include "../src/Undefined.hpp"
#include "helpers.hpp"

int main() {
  ProcessManager processManager;
  Undefined p1PageTable, p2PageTable, p3PageTable;

  processManager.createProcess( "p1", p1PageTable );
  processManager.createProcess( "p2", p2PageTable, 1 );
  // Powoduje rzucenie wyj�tku
  //processManager.createProcess( "p2", pPageTable, 2 );
  processManager.createProcess( "p3", p3PageTable, 2 );
  std::cout << "Vector of processes after adding three processes:\n\n";
  std::vector< Process >& processes = processManager.processes();
  std::for_each( processes.begin(), processes.end(), printProcessData );

  auto changeStateToTerminated = []( Process& process ) {
        process.setState( Process::State::Terminated );
      };
  std::for_each( processes.begin(), processes.end(),
      changeStateToTerminated );
  std::cout << "Vector of processes after changing these processes' state to terminated:\n\n";
  std::for_each( processes.begin(), processes.end(), printProcessData );
  
  std::cout << "Vector of processes after removing all terminated processes:\n\n";
  processManager.removeTerminatedProcesses();
  std::for_each( processes.begin(), processes.end(), printProcessData );
}