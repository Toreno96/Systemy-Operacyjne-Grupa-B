#pragma once

#include <functional>
#include <map>
#include <string>
#include "Registers.h"
#include "ZarzadzaniePamiecia.h"

class Process {
  public:
    static const unsigned int minPriority;
    static const unsigned int maxPriority;
    enum class State { New, Ready, Running, Waiting, Terminated };
    Process( const std::string& name, unsigned int priority,
        typ_tablicy_stron& pageTable );
    std::string getName() const;
    unsigned int getOriginalPriority() const;
    unsigned int getCurrentPriority() const;
    State getState() const;
    std::string convertStateToString() const;
    typ_tablicy_stron& pageTable();
    Registers getRegistersBackup() const;
    int getInstructionCounter() const;
    int getCurrentPriorityDuration() const;
    // W przypadku podania etykiety, kt�rej adres nie jest zapisany w bloku
    // PCB, rzucony zostaje wyj�tek std::out_of_range
    int getLabelAddress( const std::string& label ) const;
    std::string getLastReceivedMessage() const;
    // Inna nazwa?
    std::string getProcessInfo() const;
    std::string getPageTableContent() const;
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
    // Nazwa procesu jest jednocze�nie jego identyfikatorem, gdy� jest ona
    // unikatowa, ze wzgl�du na istnienie tylko jednej grupy proces�w w naszym
    // systemie
    std::string name_;
    unsigned int originalPriority_, currentPriority_;
    State state_;
    std::reference_wrapper< typ_tablicy_stron > pageTable_;
    Registers registersBackup_;
    int instructionCounter_,
        currentPriorityDuration_;
    std::map< std::string, int > labelsAddresses_;
    std::string lastReceivedMessage_;
};