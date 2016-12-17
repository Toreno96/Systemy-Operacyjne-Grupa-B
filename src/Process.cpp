#include "Process.hpp"

const unsigned int Process::minPriority = 0;
const unsigned int Process::maxPriority = 7;

Process::Process( const std::string& name, unsigned int priority,
    Undefined& pageTable ) :
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
Undefined& Process::pageTable() {
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
  return labelsAddresses.at( label );
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
}
void Process::run() {
  if( state_ == State::Ready )
    state_ = State::Running;
}
void Process::wait() {
  if( state_ == State::Running )
    state_ = State::Waiting;
}
void Process::terminate() {
  if( state_ == State::Running )
    state_ = State::Terminated;
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
  labelsAddresses[ label ] = address;
}