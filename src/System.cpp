#include <iostream>
#include "System.hpp"

// Inicjalizacja wszystkich modu��w w li�cie inicjalizacyjnej TO-DO
System::System() :
    interpreter_( &processManager_, &cpu_, &hardDrive_, &pipes_ ),
    shell_( *this ), running_( false ) {}
void System::run() {
  running_ = true;
  try {
    inicjalizacja_PLIKU_WYMIANY();
    inicjalizacja_RAMU();
    displayIntro();
    while( running_ ) {
      useShell();
      cpu_.Scheduler( processManager_.processes() );
      if( processManager_.runningProcessExist() )
        interpreter_.work();
      processManager_.removeTerminatedProcesses();
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
  std::cout << "\nUnexpected system shutdown\nCause: " << errorMessage << '\n';
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
void System::useShell() {
  Command inputCommand = shell_.promptUserForCommand();
  if( shell_.commandExist( inputCommand.name() ) )
    shell_.runCommand( inputCommand );
  else
    std::cout << "Unknown command: " << inputCommand.name() << '\n';
}