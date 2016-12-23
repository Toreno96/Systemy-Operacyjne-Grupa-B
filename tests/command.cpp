#include <iostream>
#include "../src/Command.hpp"

void testCommandClass( const std::string& rawCommand ) {
  Command command1( rawCommand );
  std::cout << command1.name() << '\n';
  const std::vector< std::string >& arguments = command1.arguments();
  for( auto& argument : arguments )
    std::cout << argument << '\n';
  std::cout << '\n';
}

int main() {
  testCommandClass( "createProcess    process1        helloWorld.txt" );
  testCommandClass( "createProcess process2 silnia.txt" );
  testCommandClass( "next 10" );
  testCommandClass( "processesList" );
  testCommandClass( std::string() );
}