#pragma once

#include <functional>
#include <map>
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
    // W przypadku podania etykiety, której adres nie jest zapisany w bloku
    // PCB, rzucony zostaje wyj¹tek std::out_of_range
    int getLabelAddress( const std::string& label ) const;
    std::string getLastReceivedMessage() const;
    void restoreOriginalPriority();
    void increasePriority();
    void decreasePriority();
    void ready();
    void run();
    void wait();
    void terminate();
    void setRegistersBackup( const Registers& registers );
    void setInstructionCounter( int instructionCounter );
    void increaseCurrentPriorityDuration();
    void saveLabelAddress( const std::string& label, int address );
    void setLastReceivedMessage( const std::string& message );
  private:
    void setPriority( unsigned int priority );
    void resetCurrentPriorityDuration();
    // Nazwa procesu jest jednoczeœnie jego identyfikatorem, gdy¿ jest ona
    // unikatowa, ze wzglêdu na istnienie tylko jednej grupy procesów w naszym
    // systemie
    std::string name_;
    unsigned int originalPriority_, currentPriority_;
    State state_;
    std::reference_wrapper< Undefined > pageTable_;
    Registers registersBackup_;
    int instructionCounter_,
        currentPriorityDuration_;
    std::map< std::string, int > labelsAddresses;
    std::string lastReceivedMessage_;
};