#pragma once

#include <functional>
#include <string>
#include "Registers.h"
#include "Undefined.hpp"

class Process {
  public:
    static const unsigned int minPriority;
    static const unsigned int maxPriority;
    enum class State { New, Ready, Running, Waiting, Terminated };
    Process( const std::string& name, unsigned int priority,
        Undefined& pageTable );
    std::string getName() const;
    unsigned int getOriginalPriority() const;
    unsigned int getCurrentPriority() const;
    State getState() const;
    Undefined& pageTable();
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
    // Nazwa procesu jest jednocze�nie jego identyfikatorem, gdy� jest ona
    // unikatowa, ze wzgl�du na istnienie tylko jednej grupy proces�w w naszym
    // systemie
    std::string name_;
    unsigned int originalPriority_, currentPriority_;
    State state_;
    std::reference_wrapper< Undefined > pageTable_;
    Registers registersBackup_;
    int instructionCounter_,
        currentPriorityDuration_;
    // Poza tym - sk�adowe potrzebne do komunikacji, ale wygl�du tych ju�
    // kompletnie nie znam. Potrzebuj� info od Jakuba.
};