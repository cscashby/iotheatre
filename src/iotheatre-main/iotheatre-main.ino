#include <ArduinoOSC.h>
#include "config.h"       // My configuration parameters, etc.
#include "Monitor.h"      // LED flashing / status monitor
#include "Network.h"      // Networking - mostly a wrap for WifiManager
#include "Web.h"          // Web - handle web requests and online configuration
#include "Motor.h"        // Motor - stepper motor support

// We're using singletons here as the classes need to use each others' methods
static Network& net = Network::get();
static Monitor& mon = Monitor::get();
static Web& web = Web::get();
static Motor& mot = Motor::get();

void setup() {
  if (Serial) {
    Serial.begin(SERIAL_BAUD);
  }
  #ifdef DEBUG
    esp_log_level_set("*", ESP_LOG_DEBUG);
  #elif defined INFO
    esp_log_level_set("*", ESP_LOG_INFO);
  #elif defined WARN
    esp_log_level_set("*", ESP_LOG_WARN);
  #endif
  
  net.begin();
  mon.begin();
  web.begin();
  mot.begin();
}

void loop() {
  net.loop();
  mon.loop();  
// - Web loop runs in the monitor ticker rather than here
  mot.loop();
}
