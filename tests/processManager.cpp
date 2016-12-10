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
  // Wymóg dodania w ProcessManager::createProcess sprawdzania, czy nie
  // powtarza siê nazwa procesu
  processManager.createProcess( "p2", Undefined(), 2 );
  const std::vector< Process >& processes = processManager.processes();
  std::for_each( processes.begin(), processes.end(), printProcessData );
}