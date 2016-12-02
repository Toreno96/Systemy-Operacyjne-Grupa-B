#include "Process.hpp"

// Process::Process( const std::string& name, const Undefined& pageTable ) : Process::name_( name ), Process::pageTable_( pageTable )
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
Undefined Process::getInstructionCounter() const {
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
void Process::setInstructionCounter( Undefined instructionCounter ) {
  instructionCounter_ = instructionCounter;
}