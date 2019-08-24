/* 
 *  M-Brain (Slave Receiver) using Arduino Mega
 *  
 *  Created: 24-08-2019
 *  Author: Tiago Ângelo (aka p1nh0)
*/

#define ADDR 8 // this device address
#define NUMBYTES 4 // number of bytes using in communication from M-Controllers to M-Brain

#include <Wire.h>

void setup() {
  Wire.begin(ADDR); 
  Wire.onReceive(receiveI2C);
  Serial.begin(9600);
}

void loop() {

}

void receiveI2C(int howmany){
  while(Wire.available()){
    byte v = Wire.read();
    Serial.print(v);
    Serial.print(" "); 
  }
  if(!Wire.available()) Serial.println(); // print line when no more bytes are available
  
}
