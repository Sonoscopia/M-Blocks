/*
 * Sample Average Technique to smooth analogRead from potentiometers
 * 
 * this technique only outputs values when X samples are read
 * 
 */

#define SAMPLES 8

uint16_t pot[SAMPLES];
uint16_t val; 
byte _val =0;
byte counter = 0;
 
void setup() {
  Serial.begin(9600);
}

void loop() {
  pot[counter] = analogRead(A0) >> 3; 
  
  counter++;
  if(counter >= SAMPLES){
    counter = 0;
    val = 0; 
    for(int i = 0; i < SAMPLES; i++){
      val += pot[i];
    }
    val = val >> 3; 
    if(val != _val){
      _val = val;
      Serial.println(val);
    }
  }
}
