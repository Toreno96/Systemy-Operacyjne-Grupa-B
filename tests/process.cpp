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

   typ_tablicy_stron& p2PageTable = Porcjuj_i_wloz(
      "I'll be back\n" );

  Process p2( "p2", Process::minPriority, p2PageTable );

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
  p2.ready();
  p1.run();
  
  p1.restoreOriginalPriority();
  p1.terminate();
  printProcessData( p1 );

  for( int logicAddress = 0; logicAddress < 45; ++logicAddress )
    std::cout << daj_mi_litere( logicAddress, p1.pageTable() );
  std::cout << '\n';

  for( int logicAddress = 0; logicAddress < 12; ++logicAddress )
    std::cout << daj_mi_litere( logicAddress, p2.pageTable() );
  std::cout << '\n';

  std::cout << "p1' page table content:\n\n" << p1.getPageTableContent()
      << '\n';

  //WYPISZ_PLIK_WYMIANY();
}