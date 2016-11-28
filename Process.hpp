#pragma once

#include <string>
#include "Undefined.hpp"


class Process {
  public:
    // Nazwy stanów na podstawie materia³ów z wa¿niaka. Jestem otwarty na wszelkie
    // sugestie, dotycz¹ce zmiany nazw czy umieszczenia dodatkowych stanów.
    enum class State { New, Ready, Running, Waiting, Terminated };
    Process( std::string name );
    // Poza tym - helluva getterów i setterów...
  protected:
    // Nazwa procesu, a jednoczeœnie i jego identyfikator
    std::string name_;
    // Oryginalny i aktualny priorytet procesu
    unsigned int originalPriority_, currentPriority_;
    // Aktualny stan procesu
    State state_;
    // Rozmiar i pocz¹tek tablicy stron, w której znajduj¹ siê informacje o
    // ulokowaniu kodu programu. Zamieniæ na typ int w przypadku tego
    // pierwszego?
    Undefined pageTableSize_,
              pageTableBeginning_;
    // Rejestry. Ile ich?
    Undefined A_, B_, C_;
    // Licznik rozkazów. Zamieniæ na typ int? Nazwê na programCounter/inn¹?
    Undefined instructionCounter_;
    // Poza tym - sk³adowe potrzebne do komunikacji, ale wygl¹du tych ju¿
    // kompletnie nie znam. Potrzebujê info od Jakuba.
};