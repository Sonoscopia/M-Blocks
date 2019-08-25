/* 
 *  M-Button (Master Sender) using Arduino Pro Mini
 *  
 *  Created: 25-08-2019
 *  Author: Tiago Ângelo (aka p1nh0)
*/

#include <Wire.h>
#define NUMBYTES 4 // number of bytes using in communication from M-Controllers to M-Brain
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define DEBUG 0

char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte bstate[4] = {0, 0, 0, 0};
byte _bstate[4] = {0, 0, 0, 0};
boolean changed = false; // used to check if toggles have changed 

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
  if(DEBUG) Serial.begin(9600);

  // hardware setup
  for(int i = 0; i < 4; i++){
    pinMode(inputs[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 4; i++){
    bstate[i] = !digitalRead(inputs[i]);
    if( bstate[i] != _bstate[i] ){
      changed = true; 
    }
    _bstate[i] = bstate[i];
  }
  
  if(changed){
    Wire.beginTransmission(BRAIN);
    Wire.write(bstate, NUMBYTES);
    Wire.endTransmission();

    if(DEBUG && changed){
      for(int i = 0; i < 4; i++){
        Serial.print(bstate[i]);
        Serial.print(" ");
      }
      Serial.println();  
    }
  }
  
  changed = false; 

}
