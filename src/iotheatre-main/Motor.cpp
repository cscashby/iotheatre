#include "Motor.h"

TMC2209Stepper driver(&STEPPER_SERIAL, STEPPER_RSENSE, STEPPER_ADDRESS);

Motor::Motor() {
}

void Motor::begin() {
  pinMode(STEPPER_PIN_EN, OUTPUT);
  // We start disabled
  digitalWrite(STEPPER_PIN_EN, HIGH);
  pinMode(STEPPER_PIN_STEP, OUTPUT);
  pinMode(STEPPER_PIN_DIR, OUTPUT);

  STEPPER_SERIAL.begin(115200, SERIAL_8N1, STEPPER_PIN_RX, STEPPER_PIN_TX);      // HW UART drivers with ESP32 redirect

  driver.begin();
  driver.toff(STEPPER_TOFF);              // Not sure if a TOFF value is needed to be calibrated (for SpreadCycle use)
  driver.rms_current(STEPPER_RMSCURR);    // Set motor RMS current
  driver.microsteps(STEPPER_USTEPS);      // Set microsteps to 1/16th
  driver.en_spreadCycle(false);
  driver.pwm_autoscale(true);

  #ifdef DEBUG
    Serial.print("Motor initiated status: ");
    Serial.println(driver.DRV_STATUS(), BIN);
    Serial.print("Step delay: ");
    Serial.print(STEPPER_STEPDELAY);
    Serial.print(", uSteps per revolution: ");
    Serial.println(STEPPER_REVUSTEPS);
  #endif
}

void Motor::loop() {
  if( motionCounter-- > 0 ) { 
    digitalWrite(STEPPER_PIN_STEP, HIGH);
    delayMicroseconds(STEPPER_STEPDELAY);
    digitalWrite(STEPPER_PIN_STEP, LOW);
    delayMicroseconds(STEPPER_STEPDELAY);
  } else {
    // Explicit definition just to make more readable
    motionCounter = NO_MOTION;
  }
}

void Motor::enable() {
  // We stop any motion anyway
  motionCounter = NO_MOTION;
  if( !enableState ) {
    digitalWrite(STEPPER_PIN_EN, LOW);
    DEBUG_PRINT(("Motor enabled"));
  }
  enableState = true;
}

void Motor::disable() {
  // We stop any motion anyway
  motionCounter = NO_MOTION;
  if( enableState ) {
    digitalWrite(STEPPER_PIN_EN, HIGH);
    DEBUG_PRINT(("Motor disabled"));
  }
  enableState = false;
}

void Motor::forward(float revs) {
  driver.shaft(STEPPER_DIRECTION);
  this->rotate(revs);
}

void Motor::backward(float revs) {
  driver.shaft(!STEPPER_DIRECTION);
  this->rotate(revs);
}

void Motor::rotate(float revs) {
  motionCounter = STEPPER_REVUSTEPS * revs;
}
