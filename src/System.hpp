#pragma once

#include <string>
#include "CPU.h"
#include "HardDrive.h"
#include "Interpreter.h"
#include "Pipes.hpp"
#include "ProcessManager.hpp"
#include "ZarzadzaniePamiecia.h"

class System {
  public:
    System();
    void run();
    void shutdown();
    void crash( const std::string& errorMessage );
  private:
    void displayIntro();
    // Do usuniêcia w ostatecznej wersji
    void testRunLoop();
    CPU cpu_;
    HardDrive hardDrive_;
    ProcessManager processManager_;
    Pipes pipes_;
    Interpreter interpreter_;
    bool running_;
};