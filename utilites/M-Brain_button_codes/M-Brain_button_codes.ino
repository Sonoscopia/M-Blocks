/* 
 *  Prints M-Brain button codes
 *  
 *  Created: 12-11-2020
 *  Author: Tiago Ângelo (aka p1nh0)
*/
byte pc = 0;
byte format = HEX;

void setup() {
  Serial.begin(9600);
  PORTC = 0b00011111; // enable input pullup on pins 37 to 33
}

void loop() {
  if(PINC != pc){ 
    Serial.print("hexadecimal: ");
    Serial.println(PINC, format);
  }
  pc = PINC;
}
