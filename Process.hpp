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
    // Getter(y?) dla rejestrów TO-DO
    int getInstructionCounter() const;
    int getCurrentPriorityDuration() const;
    void restoreOriginalPriority();
    void increasePriority();
    // Zamiast poniższego, powrót do koncepcji osobnych metod do ustawiania
    // każdego stanu i wykonania "ewentualnych dodatkowych, związanych z tym
    // operacji"?
    void setState( const State& state );
    // Settery dla rejestrów TO-DO
    void setInstructionCounter( int instructionCounter );
    void increaseCurrentPriorityDuration();
  private:
    void setPriority( unsigned int priority );
    void resetCurrentPriorityDuration();
    // Nazwa procesu jest jednocześnie jego identyfikatorem
    std::string name_;
    unsigned int originalPriority_, currentPriority_;
    State state_;
    Undefined pageTable_;
    // Może lepiej umieścić rejestry w jakimś kontenerze?
    Undefined A_, B_, C_, D_;
    int instructionCounter_,
        currentPriorityDuration_;
    // Poza tym - składowe potrzebne do komunikacji, ale wyglądu tych już
    // kompletnie nie znam. Potrzebuję info od Jakuba.
};