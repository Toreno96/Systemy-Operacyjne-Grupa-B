#include <iostream>
#include "../src/Process.hpp"
#include "../src/Undefined.hpp"
#include "helpers.hpp"

int main() {
  Undefined p1PageTable;

  Process p1( "p1", Process::minPriority, p1PageTable );
  printProcessData( p1 );

  p1.increaseCurrentPriorityDuration();
  p1.setState( Process::State::Ready );
  printProcessData( p1 );

  p1.increaseCurrentPriorityDuration();
  p1.setState( Process::State::Running );
  printProcessData( p1 );

  p1.increasePriority();
  p1.setState( Process::State::Waiting );
  printProcessData( p1 );
  
  p1.restoreOriginalPriority();
  p1.setState( Process::State::Terminated );
  printProcessData( p1 );
}