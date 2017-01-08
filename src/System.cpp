#include <iostream>
#include "System.hpp"

// Inicjalizacja wszystkich modu³ów w liœcie inicjalizacyjnej TO-DO
<<<<<<< HEAD
System::System() : running_( false ) {}
=======
System::System() :
    interpreter_( &processManager_, &cpu_, &hardDrive_, &pipes_ ),
    shell_( *this ), running_( false ) {}
>>>>>>> 8e9ff84... bababa
void System::run() {
  running_ = true;
  try {
    displayIntro();
    while( running_ ) {
<<<<<<< HEAD
      testRunLoop();
      // TO-DO
      // Praca planisty
      // Wywo³anie interpretera
      // Wywo³anie shella (proœba o input od u¿ytkownika oraz obs³u¿enie owego)
=======
      std::cout << "\nI'm pretending that I'm doing something\n";
      cpu_.Scheduler( processManager_.processes() );
      //useInterpreter();
      useShell();
>>>>>>> 8e9ff84... bababa
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
<<<<<<< HEAD
=======
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
>>>>>>> 8e9ff84... bababa
void System::testRunLoop() {
  std::string command;
  std::cout << "\n> ";
  std::cin >> command;
  if( command == "shutdown" )
    shutdown();
}