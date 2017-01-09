#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "ProcessManager.hpp"

ProcessManager::ProcessAlreadyExist::ProcessAlreadyExist(
    const std::string& processName ) :
        std::logic_error( "Process with name \"" + processName +
            "\" already exist" ) {}
ProcessManager::ProcessDoesntExist::ProcessDoesntExist(
    const std::string& what_arg ) : std::out_of_range( what_arg ) {}
ProcessManager::ProcessDoesntExist::ProcessDoesntExist(
    const char* what_arg ) : std::out_of_range( what_arg ) {}

ProcessManager::ProcessManager() :
    randomNumberGenerator_( std::mt19937( generateSeed() ) ) {}
std::list< Process >& ProcessManager::processes() {
  return processes_;
}
void ProcessManager::createProcess( const std::string& name,
        const std::string& programCode ) {
  std::uniform_int_distribution< unsigned int > distribution(
      Process::minPriority, Process::maxPriority );
  unsigned int randomPriority = distribution( randomNumberGenerator_ );
  createProcess( name, programCode, randomPriority );
}
void ProcessManager::createProcess( const std::string& name,
    const std::string& programCode, unsigned int priority ) {
  if( isNameUsed( name ) )
    throw ProcessAlreadyExist( name );
  typ_tablicy_stron& pageTable = Porcjuj_i_wloz( programCode );
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
std::random_device::result_type ProcessManager::generateSeed() {
  std::random_device randomDevice;
  return randomDevice();
}
Process& ProcessManager::getProcess( const std::string& name ) {
  auto itProcess = findProcess( [ &name ]( const Process& process ) {
    return process.getName() == name;
  } );
  if( itProcess != processes_.end() )
    return *itProcess;
  else
    throw ProcessDoesntExist( "There's no process with name \"" + name + '\"' );
}
Process& ProcessManager::getRunningProcess() {
  auto itProcess = findProcess( []( const Process& process ) {
    return process.getState() == Process::State::Running;
  } );
  if( itProcess != processes_.end() )
    return *itProcess;
  else
    throw ProcessDoesntExist( "There's no running process" );
}
bool ProcessManager::runningProcessExist() const {
  return std::find_if( processes_.begin(), processes_.end(),
      []( const Process& process ) {
        return process.getState() == Process::State::Running;
      } ) != processes_.end();
}
std::list< Process >::iterator ProcessManager::findProcess(
    std::function< bool( const Process& process ) > unaryPredicate ) {
  return std::find_if( processes_.begin(), processes_.end(),
      unaryPredicate );
}
std::string ProcessManager::getFormattedProcessesList() const {
  std::ostringstream formattedProcessesList;
  const int width = 14;
  formattedProcessesList << std::left << std::setw( width ) << "Name/ID"
      << std::setw( width ) << "Priority"
      << std::setw( width ) << "State"
      << "\n======================================\n";
  for( const auto& process : processes_ ) {
    formattedProcessesList << std::left << std::setw( width ) << process.getName()
        << std::setw( width ) << std::to_string( process.getCurrentPriority() )
        << std::setw( width ) << process.convertStateToString() << '\n';
  }
  return formattedProcessesList.str();
}