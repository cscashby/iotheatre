#ifndef Web_h
#define Web_h
#include <WebServer.h>
#include "Network.h"
#include "config.h"

class Web {
  public:
    Web();
    void begin();
    void loop();

    void startServer();
    void stopServer();

    static Web& get() {
      static Web instance;
      return instance;
    }                        
  private:
    bool running;
};

#endif // Web_h
