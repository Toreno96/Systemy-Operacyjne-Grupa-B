// Compile with:
// clang++ -std=c++14 -Wall -Wextra -Wshadow -Wpedantic src/Registers.cpp src/ZarzadzaniePamiecia.cpp src/Process.cpp tests/helpers.cpp tests/process.cpp -o tests/process.exe

#include <iostream>
#include "../src/Process.hpp"
#include "../src/ZarzadzaniePamiecia.h"
#include "helpers.hpp"

int main() {
  inicjalizacja_PLIKU_WYMIANY();
  
  typ_tablicy_stron& p1PageTable = Porcjuj_i_wloz(
      "A long time ago in a galaxy far, far away....\n" );

  Process p1( "p1", Process::minPriority, p1PageTable );
  printProcessData( p1 );

  p1.increaseCurrentPriorityDuration();
  p1.ready();
  printProcessData( p1 );

  p1.increaseCurrentPriorityDuration();
  p1.run();
  printProcessData( p1 );

  p1.increasePriority();
  p1.wait();
  printProcessData( p1 );

  // Zakomentowanie poni¿szych dwóch linijek powoduje rzucenie wyj¹tku
  p1.ready();
  p1.run();
  
  p1.restoreOriginalPriority();
  p1.terminate();
  printProcessData( p1 );

  std::cout << "p1' page table content:\n\n" << p1.getPageTableContent()
      << '\n';

  //WYPISZ_PLIK_WYMIANY();
}