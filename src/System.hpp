#pragma once

#include <string>
// Za��czenie wszystkich modu��w TO-DO

class System {
  public:
    System();
    void run();
    void shutdown();
    void crash( const std::string& errorMessage );
  private:
    void displayIntro();
    // Do usuni�cia w ostatecznej wersji
    void testRunLoop();
    bool running_;
    // Wszystkie modu�y TO-DO
};