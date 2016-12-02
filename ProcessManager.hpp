#pragma once

#include <vector>
#include "Process.hpp"

class ProcessManager {
  public:
    std::vector< Process >& processes();
    void createProcess( const std::string& name,
        const Undefined& programCode );
    void removeTerminatedProcesses();
  private:
    std::vector< Process > processes_;
};

// Je�li modu� zarz�dzania pami�ci� operacyjn� zostanie ubrany w klas� (bardzo
// pewne), jego funkcje (a wtedy ju� metody) przestan� mie� globalny zakres i
// pojawi si� wym�g przekazywania obiektu wy�ej wspomnianej klasy do niekt�rych
// metod klasy ProcessManager jako argument.
//
// Przy za�o�eniu, �e klasa IZP = klasa implementuj�ca modu� zarz�dzania pami�cia operacyjn�:
//
// Aby to zniwelowa�, mo�na by pokusi� si� o uczynienie metod klasy IZP
// statycznymi, ale nawet lepszym pomys�em by�oby umie�ci� w�r�d sk�adowych
// klasy ProcessManager odwo�anie (wska�nik/referencj�) do obiektu klasy IZP.
//
// Wtedy nale�a�oby takie odwo�anie zapewni� np. przez konstruktor klasy
// ProcessManager przy tworzeniu instancji tej klasy w klasie zespalaj�cej
// wszystkie modu�y ca�ego systemu operacyjnego.