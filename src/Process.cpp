#include "Process.hpp"

const unsigned int Process::minPriority = 0;
const unsigned int Process::maxPriority = 7;

Process::changeOfStateImpossible::changeOfStateImpossible(
    const std::string& processName, const std::string& targetState ) :
        std::logic_error( "Change of \"" + processName +
            "\" process' state to \"" + targetState + "\" impossible" ) {}
Process::addressOfLabelOutOfRange::addressOfLabelOutOfRange(
    const std::string& processName, const std::string& label ) :
        std::out_of_range( "Address of label \"" + label +
            "\" isn't saved in control block of \"" + processName +
            "\" process" ) {}

Process::Process( const std::string& name, unsigned int priority,
    typ_tablicy_stron& pageTable ) :
        name_( name ), originalPriority_( priority ),
        currentPriority_( priority ), state_( Process::State::New ),
        pageTable_( std::ref( pageTable ) ), instructionCounter_( 0 ),
        currentPriorityDuration_( 0 ) {}
std::string Process::getName() const {
  return name_;
}
unsigned int Process::getOriginalPriority() const {
  return originalPriority_;
}
unsigned int Process::getCurrentPriority() const {
  return currentPriority_;
}
Process::State Process::getState() const {
  return state_;
}
std::string Process::convertStateToString() const {
  switch( state_ ) {
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
typ_tablicy_stron& Process::pageTable() {
  return pageTable_.get();
}
Registers Process::getRegistersBackup() const {
  return registersBackup_;
}
int Process::getInstructionCounter() const {
  return instructionCounter_;
}
int Process::getCurrentPriorityDuration() const {
  return currentPriorityDuration_;
}
int Process::getLabelAddress( const std::string& label ) const {
  try {
    return labelsAddresses_.at( label );
  }
  catch( std::out_of_range& e ) {
    throw addressOfLabelOutOfRange( label, name_ );
  }
}
std::string Process::getLastReceivedMessage() const {
  return lastReceivedMessage_;
}
std::string Process::getProcessInfo() const {
  return std::string(
      "Name/ID: " + name_ + '\n' +
      "State: " + convertStateToString() + '\n' +
      "Original priority: " + std::to_string( originalPriority_ ) + '\n' +
      "Current priority: " + std::to_string( currentPriority_ ) + '\n' +
      "Current priority duration: " + std::to_string( currentPriorityDuration_ ) + '\n' +
      "Instruction counter: " + std::to_string( instructionCounter_ ) ) + '\n';
}
std::string Process::getPageTableContent() const {
  std::string pageTableContent;
  for( auto& integers : pageTable_.get() ) {
    for( auto integer : integers )
      pageTableContent += std::to_string( integer ) + ' ';
    pageTableContent += '\n';
  }
  return pageTableContent;
}
void Process::restoreOriginalPriority() {
  setPriority( originalPriority_ );
}
void Process::increasePriority() {
  if( currentPriority_ < maxPriority )
    setPriority( currentPriority_ + 1 );
}
void Process::decreasePriority() {
  if( currentPriority_ > minPriority )
    setPriority( currentPriority_ - 1 );
}
void Process::ready() {
  if( state_ == State::New || state_ == State::Running ||
      state_ == State::Waiting )
    state_ = State::Ready;
  else
    throw changeOfStateImpossible( name_, "Ready" );
}
void Process::run() {
  if( state_ == State::Ready )
    state_ = State::Running;
  else
    throw changeOfStateImpossible( name_, "Running" );
}
void Process::wait() {
  if( state_ == State::Running )
    state_ = State::Waiting;
  else
    throw changeOfStateImpossible( name_, "Waiting" );
}
void Process::terminate() {
  if( state_ == State::Running )
    state_ = State::Terminated;
  else
    throw changeOfStateImpossible( name_, "Terminated" );
}
void Process::setRegistersBackup( const Registers& registers ) {
  registersBackup_ = registers;
}
void Process::setInstructionCounter( int instructionCounter ) {
  instructionCounter_ = instructionCounter;
}
void Process::increaseCurrentPriorityDuration() {
  ++currentPriorityDuration_;
}
void Process::setPriority( unsigned int priority ) {
  currentPriority_ = priority;
  resetCurrentPriorityDuration();
}
void Process::resetCurrentPriorityDuration() {
  currentPriorityDuration_ = 0;
}
void Process::saveLabelAddress( const std::string& label, int address ) {
  labelsAddresses_[ label ] = address;
}
void Process::setLastReceivedMessage( const std::string& message ) {
  lastReceivedMessage_ = message;
}