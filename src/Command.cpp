#include <sstream>
#include "Command.hpp"

Command::Command( const std::string& rawCommand ) {
  parseRawCommand( rawCommand );
}
const std::string& Command::name() {
  return name_;
}
const Command::tArguments Command::arguments() {
  return arguments_;
}
void Command::parseRawCommand( const std::string& rawCommand ) {
  if( !rawCommand.empty() ) {
    std::istringstream iss( rawCommand );
    iss >> name_;
    std::string buffer;
    while( iss >> buffer )
      arguments_.push_back( buffer );
  }
}