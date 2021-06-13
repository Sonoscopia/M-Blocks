// Print all EEPROM data contents

#include <EEPROM.h>

int addr = 0; 
byte value; 

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  Serial.print("EEPROM LENGTH = ");
  Serial.println(EEPROM.length());
  Serial.println("BEGIN");
}

void loop() {
  value = EEPROM.read(addr);
  Serial.print(addr);
  Serial.print(" ");
  Serial.println(value);
  
  addr++;
  delay(10);
  if(addr == EEPROM.length()){
    Serial.println("STOP");
    delay(50);
    exit(0);
  }
}
