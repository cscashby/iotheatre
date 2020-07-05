#ifndef Web_h
#define Web_h

#include "config.h"

class Web {
  public:
    Web();
    void begin();
    void loop();

    static Web& get() {
      static Web instance;
      return instance;
    }                        
  private:
    
};

#endif
