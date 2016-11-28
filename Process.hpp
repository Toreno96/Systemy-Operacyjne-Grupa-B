#pragma once

#include <string>
#include "Undefined.hpp"


class Process {
  public:
    // Nazwy stan�w na podstawie materia��w z wa�niaka. Jestem otwarty na wszelkie
    // sugestie, dotycz�ce zmiany nazw czy umieszczenia dodatkowych stan�w.
    enum class State { New, Ready, Running, Waiting, Terminated };
    Process( std::string name );
    // Poza tym - helluva getter�w i setter�w...
  protected:
    // Nazwa procesu, a jednocze�nie i jego identyfikator
    std::string name_;
    // Oryginalny i aktualny priorytet procesu
    unsigned int originalPriority_, currentPriority_;
    // Aktualny stan procesu
    State state_;
    // Rozmiar i pocz�tek tablicy stron, w kt�rej znajduj� si� informacje o
    // ulokowaniu kodu programu. Zamieni� na typ int w przypadku tego
    // pierwszego?
    Undefined pageTableSize_,
              pageTableBeginning_;
    // Rejestry. Ile ich?
    Undefined A_, B_, C_;
    // Licznik rozkaz�w. Zamieni� na typ int? Nazw� na programCounter/inn�?
    Undefined instructionCounter_;
    // Poza tym - sk�adowe potrzebne do komunikacji, ale wygl�du tych ju�
    // kompletnie nie znam. Potrzebuj� info od Jakuba.
};