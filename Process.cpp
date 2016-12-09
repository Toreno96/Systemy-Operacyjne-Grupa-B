#include "Process.hpp"

const unsigned int Process::minPriority = 0;
const unsigned int Process::maxPriority = 7;

Process::Process( const std::string& name, unsigned int priority,
    const Undefined& pageTable ) :
        name_( name ), originalPriority_( priority ),
        currentPriority_( priority ), state_( Process::State::Ready ),
        pageTable_( pageTable ), instructionCounter_( 0 ),
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
Undefined Process::getPageTable() const {
  return pageTable_;
}
int Process::getInstructionCounter() const {
  return instructionCounter_;
}
int Process::getCurrentPriorityDuration() const {
  return currentPriorityDuration_;
}
void Process::restoreOriginalPriority() {
  setPriority( originalPriority_ );
}
void Process::increasePriority() {
  if( currentPriority_ < maxPriority )
    setPriority( currentPriority_ + 1 );
}
void Process::setState( const Process::State& state ) {
  state_ = state;
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