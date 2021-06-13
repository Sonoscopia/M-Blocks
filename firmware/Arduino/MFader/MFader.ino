/* 
 *  M-Button (Master Sender) using Arduino Pro Mini
 *  version 0.1.0
 *  
 *  Created: 12-11-2020
 *  Author: Tiago Ângelo (aka p1nh0)
*/
 
#include <Wire.h>

#define NUMBYTES 2 // number of bytes using in communication from M-Controllers to M-Brain
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define MADDR 3 // M-Controller address
#define MADDRSIZE 5 // addres size in bytes (5-bytes: 0 to 31)
#define DEBUG 0

char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte potstate[4] = {0, 0, 0, 0};
byte _potstate[4] = {0, 0, 0, 0};
boolean changed = false; // used to check if toggles have changed 
byte addr = MADDR;
byte message[2] = {addr, potstate[0]};

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
  if(DEBUG) Serial.begin(115200);

}

void loop() {
  for (int i = 0; i < 4; i++){
    potstate[i] = analogRead(inputs[i]) >> 3; // 0..127
    if( potstate[i] != _potstate[i] ){
       // prepare message to send through I2C
      message[0] = MADDR + (i << MADDRSIZE);
      message[1] = potstate[i];
      // send I2C message      
      Wire.beginTransmission(BRAIN);
      Wire.write(message, NUMBYTES);
      Wire.endTransmission();
      
      // DEBUG I2C MESSAGES
      if(DEBUG){
        changed = true; 
        Serial.print("I2C message to M-Brain on addr=");
        Serial.print(BRAIN);
        Serial.println(" :");
        Serial.print("ctrl_addres: ");
        Serial.print(message[0], BIN);
        Serial.print(" | ctrl_value: ");
        Serial.println(message[1]); 
      }
    }
    _potstate[i] = potstate[i];
  }
  
  // DEBUG HARDWARE CONTROLLERS
  if(changed && DEBUG ){
    for(int i=0; i < 4; i++){
      Serial.print(potstate[i]);
      Serial.print(" ");
    }
    Serial.println();
    changed = false;
  }
}
