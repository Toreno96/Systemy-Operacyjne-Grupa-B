#pragma once

#include <string>
#include "Registers.h"
#include "Undefined.hpp"

class Process {
  public:
    static const unsigned int minPriority;
    static const unsigned int maxPriority;
    enum class State { Ready, Running, Waiting, Terminated };
    Process( const std::string& name, unsigned int priority,
        const Undefined& pageTable );
    std::string getName() const;
    unsigned int getOriginalPriority() const;
    unsigned int getCurrentPriority() const;
    State getState() const;
    Undefined getPageTable() const;
    Registers getRegistersBackup() const;
    int getInstructionCounter() const;
    int getCurrentPriorityDuration() const;
    void restoreOriginalPriority();
    void increasePriority();
    void decreasePriority();
    // Zamiast poni�szego, powr�t do koncepcji osobnych metod do ustawiania
    // ka�dego stanu i wykonania "ewentualnych dodatkowych, zwi�zanych z tym
    // operacji"?
    void setState( const State& state );
    void setRegistersBackup( const Registers& registers );
    void setInstructionCounter( int instructionCounter );
    void increaseCurrentPriorityDuration();
  private:
    void setPriority( unsigned int priority );
    void resetCurrentPriorityDuration();
    // Nazwa procesu jest jednocze�nie jego identyfikatorem
    std::string name_;
    unsigned int originalPriority_, currentPriority_;
    State state_;
    Undefined pageTable_;
    Registers registersBackup_;
    int instructionCounter_,
        currentPriorityDuration_;
    // Poza tym - sk�adowe potrzebne do komunikacji, ale wygl�du tych ju�
    // kompletnie nie znam. Potrzebuj� info od Jakuba.
};