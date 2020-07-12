#ifndef Motor_h
#define Motor_h

#include <TMCStepper.h>
#include "config.h"

#define NO_MOTION  -1

class Motor {
  public:
    Motor();
    void begin();
    void loop();

    void enable();
    void disable();
    void forward(float revs = 1.0f);
    void backward(float revs = 1.0f);
    void rotate(float revs = 1.0f);

    static Motor& get() {
      static Motor instance;
      return instance;
    }                        
  private:
    bool enableState = false;

    long motionCounter = NO_MOTION; // -1 = no motion at present
};

#endif // Motor_h
