#pragma once

#include <string>
<<<<<<< HEAD
// Za³¹czenie wszystkich modu³ów TO-DO
=======
#include "CPU.h"
#include "HardDrive.h"
#include "Interpreter.h"
#include "Pipes.hpp"
#include "ProcessManager.hpp"
#include "ZarzadzaniePamiecia.h"
#include "Shell.hpp"
>>>>>>> 8e9ff84... bababa

class System {
  public:
    System();
    void run();
    void shutdown();
    void crash( const std::string& errorMessage );
<<<<<<< HEAD
  private:
    void displayIntro();
    // Do usuniêcia w ostatecznej wersji
    void testRunLoop();
    bool running_;
    // Wszystkie modu³y TO-DO
=======
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
>>>>>>> 8e9ff84... bababa
};