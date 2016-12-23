#include <algorithm>
#include <cctype>
#include "Shell.hpp"
#include "System.hpp"

Shell::Shell( System& system ) : system_( system ), promptDelay_( 0 ) {
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
void Shell::runCommand( const Command& command ) {
    // Dodaæ obs³ugê wyj¹tku std::out_of_range? TO-DO
    commandsFunctions.at( command.name() )( command.arguments() );
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
          if( std::all_of( count.begin(), count.end(), ::isdigit ) )
            promptDelay_ = std::stoi( count );
          else
            // Stworzyæ w³asny wyj¹tek i rzucaæ w ka¿dej takiej sytuacji?
            std::cout << "Invalid argument\n";
        }
      };
}