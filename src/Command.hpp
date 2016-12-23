#pragma once

#include <string>
#include <vector>

class Command {
  public:
    typedef std::vector< std::string > tArguments;
    Command( const std::string& rawCommand );
    const std::string& name();
    const tArguments arguments();
  private:
    void parseRawCommand( const std::string& rawCommand );
    std::string name_;
    tArguments arguments_;
};