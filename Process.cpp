#include "Process.hpp"

Process::Process( const std::string& name, const Undefined& pageTable ) :
        Process( name, 0u, Process::State::Ready, pageTable ) {}
Process::Process( const std::string& name, unsigned int originalPriority,
    const State& state, const Undefined& pageTable ) :
        name_( name ), originalPriority_( originalPriority ),
        currentPriority_( originalPriority ), state_( state ),
        pageTable_( pageTable ) {}
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
void Process::restoreOriginalPriority() {
  currentPriority_ = originalPriority_;
}
void Process::setPriority( unsigned int priority ) {
  currentPriority_ = priority;
}
void Process::setState( const Process::State& state ) {
  state_ = state;
}
void Process::setInstructionCounter( int instructionCounter ) {
  instructionCounter_ = instructionCounter;
}