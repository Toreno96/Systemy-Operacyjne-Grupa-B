#pragma once

#include <string>
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
    // Getter(y?) dla rejestr�w TO-DO
    int getInstructionCounter() const;
    int getCurrentPriorityDuration() const;
    void restoreOriginalPriority();
    void increasePriority();
    // Zamiast poni�szego, powr�t do koncepcji osobnych metod do ustawiania
    // ka�dego stanu i wykonania "ewentualnych dodatkowych, zwi�zanych z tym
    // operacji"?
    void setState( const State& state );
    // Settery dla rejestr�w TO-DO
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
    // Mo�e lepiej umie�ci� rejestry w jakim� kontenerze?
    Undefined A_, B_, C_, D_;
    int instructionCounter_,
        currentPriorityDuration_;
    // Poza tym - sk�adowe potrzebne do komunikacji, ale wygl�du tych ju�
    // kompletnie nie znam. Potrzebuj� info od Jakuba.
};