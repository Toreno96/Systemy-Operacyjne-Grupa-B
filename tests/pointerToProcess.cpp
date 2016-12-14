#include <algorithm>
#include <iostream>
#include <vector>
#include "../src/Process.hpp"
#include "../src/ProcessManager.hpp"
#include "../src/Undefined.hpp"
#include "helpers.hpp"

int main() {
  ProcessManager processManager;
  
  processManager.createProcess( "p1", Undefined() );
  processManager.createProcess( "p2", Undefined(), 1 );
  processManager.createProcess( "p3", Undefined(), 4 );
  processManager.createProcess( "p4", Undefined() );
  std::cout << "Vector of processes after adding three processes:\n\n";
  std::vector< Process >& processes = processManager.processes();
  std::for_each( processes.begin(), processes.end(), printProcessData );

  auto itProcess = std::find_if( processes.begin(), processes.end(),
      []( const Process& process ){ return process.getName() == "p3"; } );
  Process* pProcess = &( *itProcess );
  pProcess->setState( Process::State::Running );

  std::cout << "Vector of processes after changing third process' state:\n\n";
  std::for_each( processes.begin(), processes.end(), printProcessData );
}