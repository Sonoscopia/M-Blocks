#define TOGGLE1 8 // M-Blocks Toggle#1 Address
#define NUMBYTES 5 // Num of bytes used in M-Blocks I2C communication
#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(TOGGLE1, NUMBYTES);    // request 5 bytes from TOGGLE#1 slave device
  byte countbytes = 0;
  boolean r = false; // parse data only if incoming data has the leftmost byte > 0 
  
  while (Wire.available()) { // slave may send less than requested
    byte v = Wire.read(); // receive a byte as character

    if(r){
      Serial.print(v);
      Serial.print(" ");
    }
    
    if(countbytes == 0 && v > 0) r = true;
    //else r = false; 
    countbytes++; 
  }
  if(r) Serial.println();
  
  //delay(500);
}
