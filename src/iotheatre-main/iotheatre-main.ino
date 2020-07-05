#include <ArduinoOSC.h>
#include <TinyPICO.h>
#include <WebServer.h>
#include "config.h"       // My configuration parameters, etc.
#include "Monitor.h"      // LED flashing / status monitor
#include "Network.h"      // Networking - mostly a wrap for WifiManager
#include "Web.h"          // Web - handle web requests and online configuration

WebServer server(NET_PORT);

// We're using singletons here as the classes need to use each others' methods
static Network& net = Network::get();
static Monitor& mon = Monitor::get();
static Web& web = Web::get();

void setup() {
  Serial.begin(SERIAL_BAUD);
  
  net.begin();
  mon.begin();
  
  // ===== Setup web server
  server.on("/", []() {
    server.send(200, "text/plain", "hello from iotheatre!");
  });
  server.on("/reset", []() {
    ERROR_PRINT(("Reset requested"));
    net.reset();
    server.send(200, "text/plain", "Rebooting");
    ESP.restart();
  });
  server.on("/reboot", []() {
    ERROR_PRINT(("Reboot requested"));
    server.send(200, "text/plain", "Resetting");
    ESP.restart();
  });

  server.begin();
  INFO_PRINT(("HTTP server started"));
}

void loop() {
  server.handleClient();
  net.loop();
  mon.loop();  
}
