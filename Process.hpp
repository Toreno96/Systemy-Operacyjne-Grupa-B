#pragma once

#include <string>
#include "Undefined.hpp"


class Process {
  public:
    // Nazwy stan�w na podstawie materia��w z wa�niaka. Jestem otwarty na wszelkie
    // sugestie, dotycz�ce zmiany nazw czy umieszczenia dodatkowych stan�w.
    enum class State { New, Ready, Running, Waiting, Terminated };
    Process( std::string name );
    std::string getName() const;
    unsigned int getOriginalPriority() const;
    unsigned int getCurrentPriority() const;
    State getState() const;
    Undefined getPageTable() const;
    // Getter(y?) dla rejestr�w
    Undefined getInstructionCounter() const;
    void setCurrentPriority( unsigned int priority );
    void setState( State state ); // Zamiast tego powr�t do koncepcji osobnych
    // metod do ustawiania ka�dego stanu i wykonania "ewentualnych dodatkowych, zwi�zanych z tym operacji"?
    // Settery dla rejestr�w
    void setInstructionCounter( Undefined instructionCounter );
  protected:
    // Nazwa procesu, a jednocze�nie i jego identyfikator
    std::string name_;
    // Oryginalny i aktualny priorytet procesu
    unsigned int originalPriority_, currentPriority_;
    // Aktualny stan procesu
    State state_;
    // Tablica stron, w kt�rej znajduj� si� informacje o ulokowaniu kodu
    // programu.
    Undefined pageTable;
    // Rejestry. Ile ich? Mo�e lepiej zrobi� z tego tablic�?
    Undefined A_, B_, C_;
    // Licznik rozkaz�w. Zamieni� na typ int? Nazw� na programCounter/inn�?
    Undefined instructionCounter_;
    // Poza tym - sk�adowe potrzebne do komunikacji, ale wygl�du tych ju�
    // kompletnie nie znam. Potrzebuj� info od Jakuba.
};