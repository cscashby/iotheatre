#include "Web.h"
#include "wwwroot.h"
#include "wwwmainjs.h"
#include "motor.h"

// TODO: This should be a private member variable
static WebServer server(NET_PORT);

Web::Web() {
  
}

void Web::startServer() {
  DEBUG_PRINT(("Starting webserver"));
  server.begin(NET_PORT);
  running = true;
}

void Web::stopServer() {
  DEBUG_PRINT(("Stopping webserver"));
  server.stop();
  running = false;
}

void Web::begin() {
  // ===== Setup web server
  server.on("/", []() {
    server.send(200, "text/html", WEBPAGE_ROOT);
  });
  server.on("/motor/move/1", []() {
    if (server.method() != HTTP_POST) {
      server.send(405, "text/plain", "Method Not Allowed");
    } else {
      INFO_PRINT(("Move requested for motor 1"));
      Motor::get().enable();
      float unitcount = String(server.arg("unitcount")).toFloat();
      float revs = MOTOR_REVS_PERUNIT * unitcount;
      if( revs == 0 ) revs = 1;
      #ifdef DEBUG
        if (Serial) { Serial.print(MOTOR_UNITS); Serial.print(": "); Serial.print(unitcount); Serial.print(" = revs: " ); Serial.println(revs); }
      #endif
      
      if( server.arg("direction") ==  "forward" ) {
        Motor::get().forward(revs);
      } else {
        Motor::get().backward(revs);
      }
      server.send(205, "text/plain");
    }
  });
  server.on("/motor/enable/1", []() {
    INFO_PRINT(("Motor enable requested for motor 1"));
    Motor::get().enable();
    server.send(205, "text/plain");
  });
  server.on("/motor/disable/1", []() {
    INFO_PRINT(("Motor disable requested for motor 1"));
    Motor::get().disable();
    server.send(205, "text/plain");
  });
  // Couple of useful reset capabilities
  // - reset wifi
  server.on("/reset", []() {
    ERROR_PRINT(("Reset requested"));
    Network::get().reset();
    server.send(200, "text/plain", "Rebooting");
    // TODO: Doesn't work???
    ESP.restart();
  });
  // - reboot (no reset)
  server.on("/reboot", []() {
    ERROR_PRINT(("Reboot requested"));
    server.send(200, "text/plain", "Resetting");
    // TODO: Doesn't work???
    ESP.restart();
  });
}

void Web::loop() {
  if( running ) 
    server.handleClient();
}
