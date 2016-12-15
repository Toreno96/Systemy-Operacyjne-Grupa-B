#include <algorithm>
#include <stdexcept>
#include "ProcessManager.hpp"
// Za³¹czenie modu³u zarz¹dzania pamiêci¹ operacyjn¹ TO-DO

std::vector< Process >& ProcessManager::processes() {
  return processes_;
}
void ProcessManager::createProcess( const std::string& name,
    const Undefined& programCode, unsigned int priority ) {
  if( isNameUsed( name ) )
    throw std::invalid_argument( "Process' name has to be unique" );
  // W przysz³oœci pojawi siê inicjalizacja obiektem zwróconym przez tê funkcjê
  // modu³u zarz¹dzania pamiêci¹ operacyjn¹, która odpowiedzialna jest za
  // przeniesienie kodu programu z pamiêci dyskowej do pamiêci RAM. TO-DO
  Undefined pageTable;
  processes_.push_back( Process( name, priority, pageTable ) );
}
bool ProcessManager::isNameUsed( const std::string& name ) {
  return std::any_of( processes_.begin(), processes_.end(),
      [ name ]( const Process& process ) {
        return process.getName() == name;
      } );
}
void ProcessManager::removeTerminatedProcesses() {
  auto isTerminated = []( const Process& process ) {
      return process.getState() == Process::State::Terminated; };
  processes_.erase( std::remove_if( processes_.begin(), processes_.end(),
      isTerminated ), processes_.end() );
}