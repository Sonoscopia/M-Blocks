#include <Rotary.h>
#define ENC_A 2
#define ENC_B 3

Rotary rotary = Rotary(ENC_A, ENC_B);
volatile byte counter = 0; 

void setup() {
  // Rotary interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_A), readRotary, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), readRotary, CHANGE);
  }

void loop() {}

void readRotary() {
  volatile unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
  } else if (result == DIR_CCW) {
    counter--;
  }
}
