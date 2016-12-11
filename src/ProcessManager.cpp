#include <algorithm>
#include "ProcessManager.hpp"
// Za��czenie modu�u zarz�dzania pami�ci� operacyjn� TO-DO

std::vector< Process >& ProcessManager::processes() {
  return processes_;
}
void ProcessManager::createProcess( const std::string& name,
    const Undefined& programCode, unsigned int priority ) {
  // W przysz�o�ci pojawi si� inicjalizacja obiektem zwr�conym przez t� funkcj�
  // modu�u zarz�dzania pami�ci� operacyjn�, kt�ra odpowiedzialna jest za
  // przeniesienie kodu programu z pami�ci dyskowej do pami�ci RAM. TO-DO
  Undefined pageTable;
  processes_.push_back( Process( name, priority, pageTable ) );
}
void ProcessManager::removeTerminatedProcesses() {
  auto isTerminated = []( const Process& process ) {
      return process.getState() == Process::State::Terminated; };
  processes_.erase( std::remove_if( processes_.begin(), processes_.end(),
      isTerminated ), processes_.end() );
}