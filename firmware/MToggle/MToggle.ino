/* 
 *  M-Toggle (Master Sender) using Arduino Mega
 *  
 *  Created: 24-08-2019
 *  Author: Tiago Ângelo (aka p1nh0)
*/

#define NUMBYTES 4 // number of bytes using in communication from M-Controllers to M-Brain
#define BRAIN 8 // Slave Receiver address (M-Brain)
#include <Wire.h>

char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte leds[4] = {2, 3, 4, 7}; // LED PINS 
byte toggle[4] = {0, 0, 0, 0};
boolean bstate[4] = {0, 0, 0, 0};
boolean _bstate[4] = {1, 1, 1, 1};
boolean changed = false; // used to check if toggles have changed 

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
   
  // hardware setup
  for (int i = 0; i < 4; i++){
    pinMode(inputs[i], INPUT_PULLUP); // button setup
    pinMode(leds[i], OUTPUT); // led setup 
    digitalWrite(leds[i], LOW); // turn all leds off
  }
}

void loop() {
  for (int i = 0; i < 4; i++){
    bstate[i] = digitalRead(inputs[i]);
    if( bstate[i] < 1 && _bstate[i] > 0 ){
      toggle[i] = !toggle[i];
      changed = true; 
    }
    _bstate[i] = bstate[i];
    digitalWrite(leds[i], toggle[i]);
  }
  
  if(changed){
    Wire.beginTransmission(BRAIN);
    Wire.write(toggle, NUMBYTES);
    Wire.endTransmission();  
  }

  changed = false; 
}

