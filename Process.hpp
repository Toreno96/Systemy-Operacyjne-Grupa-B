#pragma once

#include <functional>
#include <vector>
#include <string>
#include "Undefined.hpp"

// Nazwy stanów na podstawie materia³ów z wa¿niaka. Jestem otwarty na wszelkie
// sugestie, dotycz¹ce zmiany nazw czy umieszczenia dodatkowych stanów.
enum class ProcessState { New, Ready, Running, Waiting, Terminated };

class Process {
  protected:
    // Referencja na wektor wszystkich, utworzonych dot¹d procesów, znajduj¹cy
    // siê w klasie ProcessManager
    std::reference_wrapper< std::vector< Process > > allProcesses_;
    // Nazwa procesu. Zamieniæ na std::array< char, 8 >?
    std::string name_;
    // Identyfikator, a tak¿e oryginalny i aktualny priorytet procesu
    unsigned int ID_,
                 originalPriority_, currentPriority_;
    // Aktualny stan procesu
    ProcessState state_;
    // Wektor referencji na procesy pochodne
    std::vector< std::reference_wrapper< Process > > children_;
    // Wartoœæ identyfikatora procesu, jak¹ przyjmie kolejny, utworzony proces
    static unsigned int IDForNextCreatedProcess_;
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
  public:
    Process( std::reference_wrapper< std::vector< Process > > allProcesses, std::string name );
    // Poza tym - helluva getterów i setterów...
};