#include <iostream>
#include "System.hpp"

// Inicjalizacja wszystkich modu³ów w liœcie inicjalizacyjnej TO-DO
System::System() : running_( false ) {}
void System::run() {
  running_ = true;
  try {
    displayIntro();
    while( running_ ) {
      testRunLoop();
      // TO-DO
      // Praca planisty
      // Wywo³anie interpretera
      // Wywo³anie shella (proœba o input od u¿ytkownika oraz obs³u¿enie owego)
      // Inne?
    }
  }
  catch( std::exception& e ) {
    crash( e.what() );
  }
}
void System::shutdown() {
  running_ = false;
}
void System::crash( const std::string& errorMessage ) {
  std::cout << "Unexpected system shutdown\n\nCause: " << errorMessage << '\n';
}
void System::displayIntro() {
  // TO-DO
  // Wszystko poni¿sze prawdopodobnie zostanie zrealizowane wywo³aniem
  // odpowiednich komend shella
  //
  // Wyœwietlenie informacji o systemie (nazwa, ewentualne logo)
  // Wyœwietlenie twórców
  // Wyœwietlenie pomocy
}
void System::testRunLoop() {
  std::string command;
  std::cout << "\n> ";
  std::cin >> command;
  if( command == "shutdown" )
    shutdown();
}