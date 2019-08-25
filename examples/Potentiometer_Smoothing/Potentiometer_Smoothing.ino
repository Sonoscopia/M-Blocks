/*
 * Moving Mean Technique to smooth analogRead from potentiometers
 * 
 * this technique only adds delay until the buffer (A0v array) is filled
 * after that it keeps replacing the last value by a new one
 */

#define SAMPLES 16 // must be a power of 2

byte A0v[SAMPLES] = {0, 0, 0, 0};
byte counter = 0; 
byte out = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(counter > SAMPLES-2){ // output after nth sample
    A0v[counter%SAMPLES] = analogRead(A0) >> 3;
    uint16_t val = 0;
    for(int i = 0; i < SAMPLES; i++){
      val += A0v[i];
    }
    val = val >> 3; // from 0..1024 to 0..127
    if(val != out){
      out = val; 
      Serial.println(out);
    }
  }
  else{ // stack
    A0v[counter%SAMPLES] = analogRead(A0) >> 3; // from 0..1024 to 0..127
  }
  counter++; 
}
