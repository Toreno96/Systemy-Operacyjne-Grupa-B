#include <iostream>
#include "helpers.hpp"

void printProcessData( const Process& process ) {
  std::cout << process.getProcessInfo() << '\n';
}