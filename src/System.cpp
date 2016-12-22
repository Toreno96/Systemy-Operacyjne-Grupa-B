#include <iostream>
#include "System.hpp"

// Inicjalizacja wszystkich modu��w w li�cie inicjalizacyjnej TO-DO
System::System() : running_( false ) {}
void System::run() {
  running_ = true;
  try {
    displayIntro();
    while( running_ ) {
      testRunLoop();
      // TO-DO
      // Praca planisty
      // Wywo�anie interpretera
      // Wywo�anie shella (pro�ba o input od u�ytkownika oraz obs�u�enie owego)
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
  // Wszystko poni�sze prawdopodobnie zostanie zrealizowane wywo�aniem
  // odpowiednich komend shella
  //
  // Wy�wietlenie informacji o systemie (nazwa, ewentualne logo)
  // Wy�wietlenie tw�rc�w
  // Wy�wietlenie pomocy
}
void System::testRunLoop() {
  std::string command;
  std::cout << "\n> ";
  std::cin >> command;
  if( command == "shutdown" )
    shutdown();
}