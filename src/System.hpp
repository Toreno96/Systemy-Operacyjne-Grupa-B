#pragma once

#include <string>
#include "CPU.h"
#include "HardDrive.h"
#include "Interpreter.h"
#include "Pipes.hpp"
#include "ProcessManager.hpp"
#include "ZarzadzaniePamiecia.h"
#include "Shell.hpp"

class System {
  public:
    System();
    void run();
    void shutdown();
    void crash( const std::string& errorMessage );
	CPU cpu_;
	HardDrive hardDrive_;
	ProcessManager processManager_;
	Pipes pipes_;
	Interpreter interpreter_;
	Shell shell_;
  private:
    void displayIntro();
    void useInterpreter();
    void useShell();
    // Do usuniêcia w ostatecznej wersji
    void testRunLoop();
    
    bool running_;
};