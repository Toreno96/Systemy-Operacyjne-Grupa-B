#include <algorithm>
#include <cctype>
#include "Shell.hpp"
#include "System.hpp"

Shell::Shell( System& system ) : system_( system ), delay_( 0 ) {
  initializeCommandsFunctions();
}
Command Shell::promptUserForCommand() const {
  if( delay_ == 0 ) {
    std::cout << "\n> ";
    std::string input;
    // Dla bezpiecze�stwa doda� tutaj czyszczenie buforu strumienia? TO-DO
    std::getline( std::cin, input );
    return Command( input );
  }
  else
    return Command{};
}
void Shell::runCommand( const Command& command ) {
  if( delay_ == 0 )
    // Doda� obs�ug� wyj�tku std::out_of_range? TO-DO
    commandsFunctions.at( command.name() )( command.arguments() );
  else
    --delay_;
}
void Shell::initializeCommandsFunctions() {
  commandsFunctions[ "shutdown" ] =
      [ this ]( const Command::tArguments& arguments ) {
        system_.get().shutdown();
      };
  commandsFunctions[ "next" ] =
      [ this ]( const Command::tArguments& arguments ) {
        // Doda� obs�ug� wyj�tk�w? TO-DO
        std::string count = arguments.at( 0 );
        if( std::all_of( count.begin(), count.end(), ::isdigit ) )
          delay_ = std::stoi( count );
        else
          // Stworzy� w�asny wyj�tek i rzuca� w ka�dej takiej sytuacji?
          std::cout << "Invalid argument\n";
      };
}