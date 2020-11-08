/* 
 *  M-Button (Master Sender) using Arduino Pro Mini
 *  
 *  Created: 25-08-2019
 *  Author: Tiago Ângelo (aka p1nh0)
*/
 
#include <Wire.h>

#define NUMBYTES 4 // number of bytes using in communication from M-Controllers to M-Brain
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define DEBUG 1

char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte potstate[4] = {0, 0, 0, 0};
byte _potstate[4] = {0, 0, 0, 0};
boolean changed = false; // used to check if toggles have changed 

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
  if(DEBUG) Serial.begin(9600);

}

void loop() {
  for (int i = 0; i < 4; i++){
    potstate[i] = analogRead(inputs[i]) >> 3; // 0..127
    if( potstate[i] != _potstate[i] ){
      changed = true; 
    }
    _potstate[i] = potstate[i];
  }
  
  if(changed){
    Wire.beginTransmission(BRAIN);
    Wire.write(potstate, NUMBYTES);
    Wire.endTransmission();

    if(DEBUG){
      for(int i = 0; i < 4; i++){
        Serial.print((byte)potstate[i]);
        Serial.print(" ");
      }
      Serial.println();  
    }
  }
  
  changed = false; 

}
