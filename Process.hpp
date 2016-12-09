#pragma once

#include <string>
#include "Undefined.hpp"

class Process {
  public:
    // Nazwy stan�w na podstawie materia��w z wa�niaka (Jestem otwarty na
    // wszelkie sugestie, dotycz�ce zmiany nazw czy umieszczenia dodatkowych
    // stan�w)
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
    // Nazwa procesu, a jednocze�nie i jego identyfikator
    std::string name_;
    // Oryginalny i aktualny priorytet procesu
    unsigned int originalPriority_, currentPriority_;
    // Aktualny stan procesu
    State state_;
    // Tablica stron, w kt�rej znajduj� si� informacje o ulokowaniu kodu
    // programu
    Undefined pageTable_;
    // Rejestry. (1) Mo�e lepiej umie�ci� je w jakim� kontenerze?
    Undefined A_, B_, C_, D_;
    // Licznik rozkaz�w
    int instructionCounter_,
        currentPriorityDuration_;
    // Poza tym - sk�adowe potrzebne do komunikacji, ale wygl�du tych ju�
    // kompletnie nie znam. Potrzebuj� info od Jakuba.
};