#pragma once

#include <vector>
#include "Process.hpp"

class ProcessManager {
  public:
    std::vector< Process >& processes();
    void createProcess( const std::string& name,
        const Undefined& programCode );
    void removeTerminatedProcesses();
  private:
    std::vector< Process > processes_;
};