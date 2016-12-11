#include <algorithm>
#include "ProcessManager.hpp"
// Za³¹czenie modu³u zarz¹dzania pamiêci¹ operacyjn¹ TO-DO

std::vector< Process >& ProcessManager::processes() {
  return processes_;
}
void ProcessManager::createProcess( const std::string& name,
    const Undefined& programCode, unsigned int priority ) {
  // W przysz³oœci pojawi siê inicjalizacja obiektem zwróconym przez tê funkcjê
  // modu³u zarz¹dzania pamiêci¹ operacyjn¹, która odpowiedzialna jest za
  // przeniesienie kodu programu z pamiêci dyskowej do pamiêci RAM. TO-DO
  Undefined pageTable;
  processes_.push_back( Process( name, priority, pageTable ) );
}
void ProcessManager::removeTerminatedProcesses() {
  auto isTerminated = []( const Process& process ) {
      return process.getState() == Process::State::Terminated; };
  processes_.erase( std::remove_if( processes_.begin(), processes_.end(),
      isTerminated ), processes_.end() );
}