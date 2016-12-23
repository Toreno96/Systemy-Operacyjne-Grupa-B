#pragma once

#include <string>
#include <vector>

class Command {
  public:
    Command( const std::string& rawCommand );
    const std::string& name();
    const std::vector< std::string > arguments();
  private:
    void parseRawCommand( const std::string& rawCommand );
    std::string name_;
    std::vector< std::string > arguments_;
};