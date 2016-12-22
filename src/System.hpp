#pragma once

#include <string>
// Za³¹czenie wszystkich modu³ów TO-DO

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
    bool running_;
    // Wszystkie modu³y TO-DO
};