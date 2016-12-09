#pragma once

#include <string>
#include "Undefined.hpp"

class Process {
  public:
    // Nazwy stanów na podstawie materia³ów z wa¿niaka (Jestem otwarty na
    // wszelkie sugestie, dotycz¹ce zmiany nazw czy umieszczenia dodatkowych
    // stanów)
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
    // Zamiast poni¿szego, powrót do koncepcji osobnych metod do ustawiania
    // ka¿dego stanu i wykonania "ewentualnych dodatkowych, zwi¹zanych z tym
    // operacji"?
    void setState( const State& state );
    // Settery dla rejestrów TO-DO
    void setInstructionCounter( int instructionCounter );
    void increaseCurrentPriorityDuration();
  private:
    void setPriority( unsigned int priority );
    void resetCurrentPriorityDuration();
    // Nazwa procesu, a jednoczeœnie i jego identyfikator
    std::string name_;
    // Oryginalny i aktualny priorytet procesu
    unsigned int originalPriority_, currentPriority_;
    // Aktualny stan procesu
    State state_;
    // Tablica stron, w której znajduj¹ siê informacje o ulokowaniu kodu
    // programu
    Undefined pageTable_;
    // Rejestry. (1) Mo¿e lepiej umieœciæ je w jakimœ kontenerze?
    Undefined A_, B_, C_, D_;
    // Licznik rozkazów
    int instructionCounter_,
        currentPriorityDuration_;
    // Poza tym - sk³adowe potrzebne do komunikacji, ale wygl¹du tych ju¿
    // kompletnie nie znam. Potrzebujê info od Jakuba.
};