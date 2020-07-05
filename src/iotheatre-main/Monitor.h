#ifndef Monitor_h
#define Monitor_h

#include "config.h"
#include "Network.h"

// Reference: Singleton design pattern here: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class Monitor {
  public:
    Monitor();
    void begin();
    void loop();

    static Monitor& get() {
      static Monitor instance;
      return instance;
    }        
  private:
    Network net;
  
    static void blink(int pin);
    static void tick();
};

#endif
