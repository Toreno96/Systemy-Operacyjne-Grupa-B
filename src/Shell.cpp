#include <algorithm>
#include <cctype>
#include "Shell.hpp"
#include "System.hpp"

Shell::Shell( System& system ) : system_( std::ref( system ) ), promptDelay_( 0 ) {
  initializeCommandsFunctions();
}
Command Shell::promptUserForCommand() {
  if( promptDelay_ == 0 ) {
    std::cout << "\n> ";
    std::string input;
    // Dla bezpieczeñstwa dodaæ tutaj czyszczenie buforu strumienia? TO-DO
    std::getline( std::cin, input );
    return Command( input );
  }
  else {
    --promptDelay_;
    return Command( "next" );
  }
}
bool Shell::commandExist( const std::string& commandName ) {
  return commandsFunctions.find( commandName ) != commandsFunctions.end();
}
void Shell::runCommand( const Command& command ) {
  commandsFunctions[ command.name() ]( command.arguments() );
}
void Shell::initializeCommandsFunctions() {
  commandsFunctions[ "shutdown" ] =
      [ this ]( const Command::tArguments& arguments ) {
        system_.get().shutdown();
      };
  commandsFunctions[ "next" ] =
      [ this ]( const Command::tArguments& arguments ) {
        if( arguments.size() > 0 ) {
          std::string count = arguments[ 0 ];
          if( std::all_of( count.begin(), count.end(), ::isdigit ) &&
              std::stoi( count ) > 0 )
            promptDelay_ = std::stoi( count ) - 1;
          else
            // Stworzyæ w³asny wyj¹tek i rzucaæ w ka¿dej takiej sytuacji?
            std::cout << "Invalid argument\n";
        }
      };
  commandsFunctions[ "merryChristmas" ] =
      [ this ]( const Command::tArguments& arguments ) {
        std::cout << "Merry Christmas and Happy New Year!\n";
      };
}