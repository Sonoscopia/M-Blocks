#define ADDR 8 // I2C address
#include <Wire.h>

char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte leds[4] = {2, 3, 4, 7}; // LED PINS 
boolean toggle[4] = {0, 0, 0, 0};
boolean bstate[4] = {0, 0, 0, 0};
boolean _bstate[4] = {1, 1, 1, 1};
byte compare = 0; // used to check if button values have changed 

void setup() {
  Wire.begin(ADDR);                // join i2c bus with address number
  Wire.onRequest(requestEvent); // register event

  // hardware setup
  for (int i = 0; i < 4; i++){
    pinMode(inputs[i], INPUT_PULLUP); // button setup
    pinMode(leds[i], OUTPUT); // led setup 
    digitalWrite(leds[i], LOW); // turn all leds off
  }
}

void loop() {
  //delay(100);
  for (int i = 0; i < 4; i++){
    bstate[i] = digitalRead(inputs[i]);
    if( bstate[i] < 1 && _bstate[i] > 0 ){
      toggle[i] = !toggle[i];
      compare++;
    }
    _bstate[i] = bstate[i];
    digitalWrite(leds[i], toggle[i]);
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  if(compare > 0){ // if there is a change in the toggle array send via I2C
    for(int i = 0; i < 4; i++){
      Wire.write(toggle[i]);
    }
  }
  compare = 0; // reset
}
