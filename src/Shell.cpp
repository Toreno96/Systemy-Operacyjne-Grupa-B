#include <algorithm>
#include <cctype>
#include "filesystemUI.h"
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
  commandsFunctions[ "createProcess" ] =
      [ this ]( const Command::tArguments& arguments ) {
        if( arguments.size() < 3 ) {
          std::cout << "Insufficient number of arguments\n";
          return;
        }

        unsigned priority;
        bool randomPriority;
        if( arguments.size() >= 4 ) {
          randomPriority = false;
          if( std::all_of( arguments[ 3 ].begin(), arguments[ 3 ].end(), ::isdigit ) ) {
            priority = std::stoi( arguments[ 3 ] );
            if( !( priority >= Process::minPriority &&
                priority <= Process::maxPriority ) ) {
              std::cout << "Invalid argument: Priority\n";
              return;
            }
          }
          else {
            std::cout << "Invalid argument: Priority\n";
            return;
          }
        }
        else
          randomPriority = true;

        std::string programCode;
        if( filesystemUI::system_read_file( system_.get().hardDrive_,
            arguments[ 1 ], arguments[ 2 ], programCode ) != 1 ) {
          std::cout << "Invalid argument: File\n";
          return;
        }

        try {
          if( randomPriority )
            system_.get().processManager_.createProcess( arguments[ 0 ], programCode );
          else
            system_.get().processManager_.createProcess( arguments[ 0 ], programCode, priority );
        }
        catch( const ProcessManager::ProcessAlreadyExist& e ) {
          std::cout << "Invalid argument: " << e.what() << '\n';
        }
      };

  commandsFunctions[ "readyProcess" ] =
      [ this ]( const Command::tArguments& arguments ) {
        if( arguments.size() < 1 ) {
          std::cout << "Insufficient number of arguments\n";
          return;
        }

        try {
          Process& process = system_.get().processManager_.getProcess( arguments[ 0 ] );
          if( process.getState() == Process::State::New )
            process.ready();
          else
            std::cout << "Process isn't in the \"New\" state\n";
        }
        catch( const ProcessManager::ProcessDoesntExist& e ) {
          std::cout << "Invalid argument: " << e.what() << '\n';
        }
      };
	  
	    commandsFunctions[ "cpuRegisters" ] =
	  [ this ](const Command::tArguments& arguments) {
	  std::cout << system_.get().cpu_.getRegisters();
  };

  commandsFunctions [ "loadFile" ] =
	  [this] (const Command::tArguments& arguments){
	  filesystemUI::load_file_from_Windows_and_save_on_harddrive(system_.get().hardDrive_);
  };

  commandsFunctions["deleteFile"] =
	  [this](const Command::tArguments& arguments){
	  filesystemUI::delete_file(system_.get().hardDrive_);
  };

  commandsFunctions["fileContent"] =
	  [this](const Command::tArguments& arguments){
	  filesystemUI::display_file(system_.get().hardDrive_);
  };

  commandsFunctions["filesList"] =
	  [this](const Command::tArguments& arguments){
    std::list< FCB > filesList = system_.get().hardDrive_.get_file_list();
	  filesystemUI::display_file_list( filesList );
  };

  commandsFunctions["hardDriveContent"] =
	  [this](const Command::tArguments& arguments){
    if (arguments.size() > 0)
	  {
		  if (arguments[0] == "bitvector")
			  filesystemUI::display_harddrive(system_.get().hardDrive_, 1);
		  else std::cout << "Invalid argument. Please try again";
	  }
	  else filesystemUI::display_harddrive(system_.get().hardDrive_, 0);
	  
  };

  commandsFunctions["lockedProcesses"] =
	  [this](const Command::tArguments& arguments){
	  system_.get().pipes_.lock_.showListOfProcesses();
  };

  commandsFunctions["firstLockedProcess"] =
	  [this](const Command::tArguments& arguments){
	  system_.get().pipes_.lock_.displayProcessName();
  };

}