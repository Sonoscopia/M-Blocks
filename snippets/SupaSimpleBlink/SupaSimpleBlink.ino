// supa simple blink 
#define bit_flip(p,m) ((p) ^= (m))


void setup() {
  DDRF = 0b11111111;
  PORTF = 0b00000000;
}

void loop() {
  PORTF ^= 0b01111111; 
  delay(500);
}
