#pragma once

#include <string>
#include "Undefined.hpp"

// Nazwy stan�w na podstawie materia��w z wa�niaka. Jestem otwarty na wszelkie
// sugestie, dotycz�ce zmiany nazw czy umieszczenia dodatkowych stan�w.
enum class ProcessState { New, Ready, Running, Waiting, Terminated };

class Process {
  protected:
    // Nazwa procesu. Zamieni� na std::array< char, 8 >?
    std::string name_;
    // Identyfikator, a tak�e oryginalny i aktualny priorytet procesu
    unsigned int ID_,
                 originalPriority_, currentPriority_;
    // Aktualny stan procesu
    ProcessState state_;
    // Warto�� identyfikatora procesu, jak� przyjmie kolejny, utworzony proces
    static unsigned int IDForNextCreatedProcess_;
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
  public:
    Process( std::string name );
    // Poza tym - helluva getter�w i setter�w...
};