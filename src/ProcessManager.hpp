#pragma once

#include <list>
#include <random>
#include "Process.hpp"

class ProcessManager {
  public:
    ProcessManager();
    std::list< Process >& processes();
    void createProcess( const std::string& name,
        const Undefined& programCode );
    void createProcess( const std::string& name,
        const Undefined& programCode, unsigned int priority );
    void removeTerminatedProcesses();
  private:
    bool isNameUsed( const std::string& name );
    std::random_device::result_type generateSeed();
    std::mt19937 randomNumberGenerator_;
    std::list< Process > processes_;
};

// Jeœli modu³ zarz¹dzania pamiêci¹ operacyjn¹ zostanie ubrany w klasê (bardzo
// pewne), jego funkcje (a wtedy ju¿ metody) przestan¹ mieæ globalny zakres i
// pojawi siê wymóg przekazywania obiektu wy¿ej wspomnianej klasy do niektórych
// metod klasy ProcessManager jako argument.
//
// Przy za³o¿eniu, ¿e klasa IZP = klasa implementuj¹ca modu³ zarz¹dzania pamiêcia operacyjn¹:
//
// Aby to zniwelowaæ, mo¿na by pokusiæ siê o uczynienie metod klasy IZP
// statycznymi, ale nawet lepszym pomys³em by³oby umieœciæ wœród sk³adowych
// klasy ProcessManager odwo³anie (wskaŸnik/referencjê) do obiektu klasy IZP.
//
// Wtedy nale¿a³oby takie odwo³anie zapewniæ np. przez konstruktor klasy
// ProcessManager przy tworzeniu instancji tej klasy w klasie zespalaj¹cej
// wszystkie modu³y ca³ego systemu operacyjnego.