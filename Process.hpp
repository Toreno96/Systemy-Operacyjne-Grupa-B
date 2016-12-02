#pragma once

#include <string>
#include "Undefined.hpp"

class Process {
  public:
    // Nazwy stanów na podstawie materia³ów z wa¿niaka (Jestem otwarty na
    // wszelkie sugestie, dotycz¹ce zmiany nazw czy umieszczenia dodatkowych
    // stanów)
    enum class State { New, Ready, Running, Waiting, Terminated };
    Process( const std::string& name, const Undefined& pageTable );
    std::string getName() const;
    unsigned int getOriginalPriority() const; // Zbêdne?
    unsigned int getCurrentPriority() const;
    State getState() const;
    Undefined getPageTable() const;
    // Getter(y?) dla rejestrów TO-DO
    Undefined getInstructionCounter() const;
    void restoreOriginalPriority(); // "Minimal" zamiast "Original"?
    void setPriority( unsigned int priority ); // Inkrementacja zamiast
    // swobodnej modyfikacji?
    // Zamiast tego, powrót do koncepcji osobnych metod do ustawiania ka¿dego
    // stanu i wykonania "ewentualnych dodatkowych, zwi¹zanych z tym operacji"?
    void setState( const State& state );
    // Settery dla rejestrów TO-DO
    void setInstructionCounter( Undefined instructionCounter );
  protected:
    // Nazwa procesu, a jednoczeœnie i jego identyfikator
    std::string name_;
    // Oryginalny i aktualny priorytet procesu
    unsigned int originalPriority_, currentPriority_;
    // Aktualny stan procesu
    State state_;
    // Tablica stron, w której znajduj¹ siê informacje o ulokowaniu kodu
    // programu
    Undefined pageTable_;
    // Rejestry. Mo¿e lepiej umieœciæ je w jakimœ kontenerze?
    Undefined A_, B_, C_, D_;
    // Licznik rozkazów. Zamieniæ na typ int? Nazwê na programCounter/inn¹?
    Undefined instructionCounter_;
    // Poza tym - sk³adowe potrzebne do komunikacji, ale wygl¹du tych ju¿
    // kompletnie nie znam. Potrzebujê info od Jakuba.
};