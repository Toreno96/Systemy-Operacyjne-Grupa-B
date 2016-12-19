#pragma once

#include <list>
#include <random>
#include "Process.hpp"

// TO-DO Zmieni� nazw� klasy na ProcessesManager? Je�li tak, to dopiero przy
// sk�adaniu systemu, korzystaj�c z dobrodziejstw globalnego (tzn. operuj�cego
// na ca�ym projekcie, a nie tylko pojedynczym pliku) find-and-replace
class ProcessManager {
  public:
    ProcessManager();
    std::list< Process >& processes();
    void createProcess( const std::string& name,
        const std::string& programCode );
    void createProcess( const std::string& name,
        const std::string& programCode, unsigned int priority );
    Process& getProcess( const std::string& name );
    Process& getRunningProcess();
    std::string getFormattedProcessesList() const;
    void removeTerminatedProcesses();
  private:
    Process& getProcess(
        std::function< bool( const Process& process ) > unaryPredicate );
    bool isNameUsed( const std::string& name );
    std::random_device::result_type generateSeed();
    std::mt19937 randomNumberGenerator_;
    std::list< Process > processes_;
};