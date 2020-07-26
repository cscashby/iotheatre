#include "Monitor.h"
#include <Arduino.h>
#include <TinyPICO.h> // We might need to wrap this elsewhere
#include <Ticker.h> // This is the ESP32 ticker library which uses the ESP32 built in timer, so no interrupts or loop() requirement
#include "Web.h"

Monitor::Monitor() {
}

TinyPICO tp = TinyPICO();

Ticker statusTicker;
int statusCounter = 0;
int wifiCounter = 0;
int heartbeatCounter = 0;
int batteryCounter = 0;

void Monitor::blink(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void Monitor::tick() {
  wifiCounter++;
  //heartbeatCounter++;
  batteryCounter++;

  // We do the web loop in here as it's short and will not be impacted
  // by longer running loop() functions like motor control
  Web::get().loop();

  int c = (Network::get().isConnected() ? MONITOR_OKCOUNTER : MONITOR_WAITCOUNTER);
  if( wifiCounter > c ) {
    wifiCounter = 0;
    blink(PIN_WIFI_LED); 
  } 
  #ifdef INFO
    if( batteryCounter > MONITOR_BATSTATUS ) {
      batteryCounter = 0;
      if (Serial) {
        Serial.print("Battery status: ");
        Serial.print(tp.IsChargingBattery() ? "charging" : "not charging");
        Serial.print(" ");
        Serial.print(tp.GetBatteryVoltage());
        Serial.println("v");
      }
    }
  #endif
}

void Monitor::begin() {
  // ===== Setup I/O
  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_WIFI_LED, OUTPUT);
  pinMode(PIN_HEARTBEAT_LED, OUTPUT);

  // Status LED is 'OK' is on, off is something wrong
  digitalWrite(PIN_STATUS_LED, LOW);
  digitalWrite(PIN_WIFI_LED, HIGH);
  digitalWrite(PIN_HEARTBEAT_LED, HIGH);

  // Start the ticker
  statusTicker.attach_ms(MONITOR_TICKER, Monitor::tick);
}

void Monitor::loop() {
  // We'll add some to this with logical and but for now just network connectivity
  bool ok = Network::get().isConnected();
  
  digitalWrite(PIN_STATUS_LED, !ok);
}
