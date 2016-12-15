#include <iostream>
#include "helpers.hpp"

std::string convertProcessStateToString( Process::State state ) {
  switch( state ) {
    case Process::State::New:
      return "New";
    case Process::State::Ready:
      return "Ready";
    case Process::State::Running:
      return "Running";
    case Process::State::Waiting:
      return "Waiting";
    case Process::State::Terminated:
      return "Terminated";
  }
}
void printProcessData( const Process& process ) {
  std::cout << "Name: " << process.getName() << '\n'
      << "Original priority: " << process.getOriginalPriority() << '\n'
      << "Current priority: " << process.getCurrentPriority() << '\n'
      << "Current Priority Duration: " << process.getCurrentPriorityDuration() << '\n'
      << "State: " << convertProcessStateToString( process.getState() ) << "\n\n";
}