#include <iostream>
#include "System.hpp"

// Inicjalizacja wszystkich modu³ów w liœcie inicjalizacyjnej TO-DO
System::System() :
    interpreter_( &processManager_, &cpu_, &hardDrive_, &pipes_ ),
    shell_( *this ), running_( false ) {}
void System::run() {
  running_ = true;
  try {
    displayIntro();
    while( running_ ) {
      std::cout << "\nI'm pretending that I'm doing something\n";
      cpu_.Scheduler( processManager_.processes() );
      //useInterpreter();
      useShell();
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
void System::useInterpreter() {
  try {
    interpreter_.work();
  }
  catch( /* Do zmiany na wyj¹tki specyficzne dla interpretera TO-DO */ ... ) {}
}
void System::useShell() {
  try {
    Command inputCommand = shell_.promptUserForCommand();
    if( shell_.commandExist( inputCommand.name() ) )
      shell_.runCommand( inputCommand );
    else
      std::cout << "Unknown command: " << inputCommand.name() << '\n';
  }
  catch( /* Do zmiany na wyj¹tki specyficzne dla shella TO-DO */ ... ) {}
}
void System::testRunLoop() {
  std::string command;
  std::cout << "\n> ";
  std::cin >> command;
  if( command == "shutdown" )
    shutdown();
}