#ifndef Network_h
#define Network_h
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

#include "config.h"
#include "Web.h"

class Network {
  public:
    Network();
    void begin();
    void loop();
    void reset();

    bool isConnected() { return connected; }
    bool isPortalActive() { return portalActive; }

    static Network& get() {
      static Network instance;
      return instance;
    }                
  private:
    WiFiManager wifiManager;
    bool portalActive = false;
    bool connected = false;

    long lastConnected = -1; // millis() when device was last online
};

#endif // Network_h
