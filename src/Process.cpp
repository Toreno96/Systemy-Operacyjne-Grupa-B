#include "Process.hpp"

const unsigned int Process::minPriority = 0;
const unsigned int Process::maxPriority = 7;

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
  return labelsAddresses_.at( label );
}
std::string Process::getLastReceivedMessage() const {
  return lastReceivedMessage_;
}
std::string Process::getProcessInfo() const {
  throw std::logic_error( "Not implemented yet" );
}
std::string Process::getPageTableContent() const {
  throw std::logic_error( "Not implemented yet" );
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
// Zmiana pojawiajacego siê ni¿ej wyj¹tku na w³asny, dziedzicz¹cy po
// standardowym?
void Process::ready() {
  if( state_ == State::New || state_ == State::Running ||
      state_ == State::Waiting )
    state_ = State::Ready;
  else
    throw std::logic_error( "State change impossible" );
}
void Process::run() {
  if( state_ == State::Ready )
    state_ = State::Running;
  else
    throw std::logic_error( "State change impossible" );
}
void Process::wait() {
  if( state_ == State::Running )
    state_ = State::Waiting;
  else
    throw std::logic_error( "State change impossible" );
}
void Process::terminate() {
  if( state_ == State::Running )
    state_ = State::Terminated;
  else
    throw std::logic_error( "State change impossible" );
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