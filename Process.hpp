#pragma once

#include <string>
#include "Undefined.hpp"

class Process {
  public:
    // Nazwy stanów na podstawie materia³ów z wa¿niaka (Jestem otwarty na
    // wszelkie sugestie, dotycz¹ce zmiany nazw czy umieszczenia dodatkowych
    // stanów)
    enum class State { Ready, Running, Waiting, Terminated };
    Process( const std::string& name, const Undefined& pageTable );
    std::string getName() const;
    // Zbêdne?
    unsigned int getOriginalPriority() const;
    unsigned int getCurrentPriority() const;
    State getState() const;
    Undefined getPageTable() const;
    // Getter(y?) dla rejestrów TO-DO
    int getInstructionCounter() const;
    int getCurrentPriorityDuration() const;
    // "Minimal" zamiast "Original"?
    void restoreOriginalPriority();
    // Inkrementacja zamiast swobodnej modyfikacji?
    void setPriority( unsigned int priority );
    // Zamiast poni¿szego, powrót do koncepcji osobnych metod do ustawiania
    // ka¿dego stanu i wykonania "ewentualnych dodatkowych, zwi¹zanych z tym
    // operacji"?
    void setState( const State& state );
    // Settery dla rejestrów TO-DO
    void setInstructionCounter( int instructionCounter );
    void increaseCurrentPriorityDuration();
  private:
    // Do tego rejestry, jeœli ostatecznie rzeczywiœcie umieszczone zostan¹ one
    // w kontenerze (1), a tak¿e licznik rozkazów, jeœli jego typem oka¿e siê
    // byæ typ fundamentalny
    Process( const std::string& name, unsigned int originalPriority,
        const State& state, const Undefined& pageTable );
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