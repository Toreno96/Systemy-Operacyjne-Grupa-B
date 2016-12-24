// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/ZarzadzaniePamiecia.cpp src/Process.cpp src/ProcessManager.cpp tests/helpers.cpp tests/customExceptions.cpp -o tests/customExceptions.exe

#include <iostream>
#include "../src/ProcessManager.hpp"

int main() {
  inicjalizacja_PLIKU_WYMIANY();
  ProcessManager processManager;

  try {
    processManager.createProcess( "Process1", "Process1's program code" );
    int check;
    std::cin >> check;
    switch( check ) {
      case 1:
        processManager.createProcess( "Process1", "Process1's program code" );
        break;
      case 2:
        processManager.getProcess( "Process2" );
        break;
      case 3:
        processManager.getRunningProcess();
        break;
      case 4:
        processManager.getProcess( "Process1" ).run();
        break;
      case 5:
        processManager.getProcess( "Process1" ).wait();
        break;
      case 6:
        processManager.getProcess( "Process1" ).terminate();
        break;
      case 7:
        processManager.getProcess( "Process1" ).ready();
        processManager.getProcess( "Process1" ).run();
        processManager.getProcess( "Process1" ).terminate();
        std::cout << "Transition from terminate to ready:\n";
        processManager.getProcess( "Process1" ).ready();
        break;
      default:
        break;
    }
  }
  catch( std::exception& e ) {
    std::cout << "Error: " << e.what() << "!\n";
  }
}