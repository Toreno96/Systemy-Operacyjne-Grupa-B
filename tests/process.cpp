// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/Process.cpp tests/helpers.cpp tests/process.cpp -o tests/process.exe

#include <iostream>
#include "../src/Process.hpp"
#include "../src/Undefined.hpp"
#include "helpers.hpp"

int main() {
  Undefined p1PageTable;

  Process p1( "p1", Process::minPriority, p1PageTable );
  printProcessData( p1 );

  p1.increaseCurrentPriorityDuration();
  p1.ready();
  printProcessData( p1 );

  p1.increaseCurrentPriorityDuration();
  p1.run();
  printProcessData( p1 );

  p1.increasePriority();
  p1.wait();
  printProcessData( p1 );

  p1.ready();
  p1.run();
  
  p1.restoreOriginalPriority();
  p1.terminate();
  printProcessData( p1 );
}