#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "Command.hpp"

class System;

// Klasa jeszcze bez jakichkolwiek testów!!! TO-DO
class Shell {
  public:
    Shell() = delete;
    Shell( System& system );
    Command promptUserForCommand();
    bool commandExist( const std::string& commandName );
    void runCommand( const Command& command );
  private:
    typedef std::function< void( const Command::tArguments& ) >
        tCommandFunction;
    void initializeCommandsFunctions();
    std::map< std::string, tCommandFunction > commandsFunctions;
    std::reference_wrapper< System > system_;
    unsigned int promptDelay_;
};