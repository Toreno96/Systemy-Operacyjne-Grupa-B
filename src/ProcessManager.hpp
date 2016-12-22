#pragma once

#include <list>
#include <random>
#include "Process.hpp"

// TO-DO Zmieni� nazw� klasy na ProcessesManager? Je�li tak, to dopiero przy
// sk�adaniu systemu, korzystaj�c z dobrodziejstw globalnego (tzn. operuj�cego
// na ca�ym projekcie, a nie tylko pojedynczym pliku) find-and-replace
class ProcessManager {
  public:
    class ProcessAlreadyExist : public std::logic_error {
      public:
        ProcessAlreadyExist( const std::string& processName );
    };
    class ProcessDoesntExist : public std::out_of_range {
      public:
        ProcessDoesntExist( const std::string& what_arg );
        ProcessDoesntExist( const char* what_arg );
    };

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
    std::list< Process >::iterator findProcess(
        std::function< bool( const Process& process ) > unaryPredicate );
    bool isNameUsed( const std::string& name );
    std::random_device::result_type generateSeed();
    std::mt19937 randomNumberGenerator_;
    std::list< Process > processes_;
};