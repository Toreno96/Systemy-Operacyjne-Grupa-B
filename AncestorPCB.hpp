#pragma once

#include <functional>
#include <vector>
#include <string>
#include "Undefined.hpp"

class Process;

// Nazwy stan�w na podstawie materia��w z wa�niaka. Jestem otwarty na wszelkie
// sugestie, dotycz�ce zmiany nazw czy umieszczenia dodatkowych stan�w.
enum class ProcessState { New, Ready, Running, Waiting, Terminated };

class AncestorPCB {
  protected:
    // Referencja na wektor wszystkich, utworzonych dot�d proces�w, znajduj�cy
    // si� w klasie ProcessManager
    std::reference_wrapper< std::vector< Process > > allProcesses_;
    // Nazwa procesu. Zamieni� na std::array< char, 8 >?
    std::string name_;
    // Identyfikator, a tak�e oryginalny i aktualny priorytet procesu
    unsigned int ID_,
                 originalPriority_, currentPriority_;
    // Aktualny stan procesu
    ProcessState state_;
    // Wektor referencji na procesy pochodne
    std::vector< std::reference_wrapper< Process > > children_;
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
    AncestorPCB( std::reference_wrapper< std::vector< Process > > allProcesses, std::string name );
    // Poza tym - helluva getter�w i setter�w...
};

// Kr�tkie podsumowanie r�nic mi�dzy AncestorPCB, a standardowym PCB:
//
// Brak informacji o procesie rodzicielskim, gdy� mamy do czynienia z procesem,
// bed�cym przodkiem wszystkich innych proces�w, tj. nie posiadaj�cym w�asnego
// rodzica.
//
// Nie jestem pewien, czy niekt�re z ju� wpisanych sk�adowych s� tutaj
// potrzebne - chocia�by stan czy priorytety procesu.