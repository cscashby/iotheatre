#ifndef Config_h
#define Config_h

#include <Arduino.h>

// ==== General setup
#define SERIAL_BAUD         115200
#define DEBUG

// ==== Network configuration
// WifiManager configuration
#define WM_CONNECT_TIMEOUT  10  // seconds
#define WM_PORTAL_TIMEOUT   300
#define WM_SSID             "iotheatre"
#define WM_KEY              "iotheatre"

// I don't like 192 as default, so going with a 10. address instead (but a /24 to be nice)
#define WM_IP               IPAddress(10,0,1,1)
#define WM_GW               IPAddress(10,0,1,1)
#define WM_MASK             IPAddress(255,255,255,0)

#define WM_HOSTNAME         "iotheatre"

// Uncomment the line below if you want to reset wifi config on boot
//#define WM_RESET_WIFI

// TODO: Play nice with WifiManager
// (i.e. wait for it to complete and release the port then open :80)
// for now we go with :81 to avoid WifiManager
#define NET_PORT            81

// ==== Monitor configuration
// Pins (GPIO numbers)
#define PIN_STATUS_LED      15  // Pin 21
#define PIN_WIFI_LED        14  // Pin 17
#define PIN_HEARTBEAT_LED   4   // Pin 24

// Monitor timings
#define MONITOR_TICKER      100 // ms base timer
#define MONITOR_OKCOUNTER   20  // Counts of ticker to identify OK
#define MONITOR_WAITCOUNTER 1   // Counts of ticker to identify 'user intervention required'

// ==== Stepper configuration
// Pins (GPIO numbers)
#define STEPPER_PIN_EN      5   // Pin 34
#define STEPPER_PIN_STEP    18  // Pin 35
#define STEPPER_PIN_DIR     19  // Pin 38
#define STEPPER_PIN_RX      21  // Pin 42
#define STEPPER_PIN_TX      22  // Pin 39
#define STEPPER_SERIAL Serial2  // We remap hardware serial to pins for RX/TX
// Stepper motor settings
#define STEPPER_RSENSE    0.11f // ohm 
#define STEPPER_ADDRESS   0b00  // MS1/2 pins to gnd
#define STEPPER_TOFF        5
#define STEPPER_RMSCURR  1200   //mA
#define STEPPER_USTEPS      16   // Microsteps (1/n)
#define STEPPER_DIRECTION  true // 'shaft' param for forwards
// Stepper motor timings
#define STEPPER_REVSTEPS    200 // steps per Revolution
#define STEPPER_SPEED       200 // RPM (max 200?)
// Stepper motor calcs
#define STEPPER_REVUSTEPS   (STEPPER_USTEPS * STEPPER_REVSTEPS)
#define STEPPER_STEPDELAY   (1000000.0 * ((60.0 / STEPPER_SPEED) / STEPPER_REVUSTEPS) / 2.0) // microseconds delay per half step

// ==== Debug stuff
#ifdef DEBUG
  #define DEBUG_PRINT(X) Serial.print("D "); \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(X); \
    Serial.print(" ("); \
    Serial.print(__FUNCTION__); \
    Serial.print("() in "); \
    Serial.print(__FILE__); \
    Serial.print(':'); \
    Serial.print(__LINE__); \
    Serial.println(")");
  #define INFO
#else
  #define DEBUG_PRINT(X)
#endif
#ifdef INFO
  #define INFO_PRINT(X) Serial.print("I "); \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(X); \
    Serial.print(" ("); \
    Serial.print(__FUNCTION__); \
    Serial.print("() in "); \
    Serial.print(__FILE__); \
    Serial.print(':'); \
    Serial.print(__LINE__); \
    Serial.println(")");
  #define WARN
#else
  #define INFO_PRINT(X)
#endif
#ifdef WARN
  #define WARN_PRINT(X) Serial.print("W "); \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(X); \
    Serial.print(" ("); \
    Serial.print(__FUNCTION__); \
    Serial.print("() in "); \
    Serial.print(__FILE__); \
    Serial.print(':'); \
    Serial.print(__LINE__); \
    Serial.println(")");
#else
  #define WARN_PRINT(X)
#endif
#define ERROR_PRINT(X) Serial.print("E "); \
  Serial.print(millis()); \
  Serial.print(": "); \
  Serial.print(X); \
  Serial.print(" ("); \
  Serial.print(__FUNCTION__); \
  Serial.print("() in "); \
  Serial.print(__FILE__); \
  Serial.print(':'); \
  Serial.print(__LINE__); \
  Serial.println(")");

#endif
