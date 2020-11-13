#include <Rotary.h>
#define ENC_A 2
#define ENC_B 3

Rotary rotary = Rotary(ENC_A, ENC_B);
volatile byte counter = 0; 
byte c = counter; 

void setup() {
  Serial.begin(9600);
  DDRF = 0b11111111; // analog A0 to A6 as outputs (leds)
  // Rotary interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_A), readRotary, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), readRotary, CHANGE);
}

void loop() {
  if(c != counter){
    c = counter;
    PORTF = c;
    Serial.println(c);
  }
}

void readRotary() {
  volatile unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
  } else if (result == DIR_CCW) {
    counter--;
  }
}
