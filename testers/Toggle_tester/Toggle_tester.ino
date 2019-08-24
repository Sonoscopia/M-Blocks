char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte leds[4] = {2, 3, 4, 7}; // LED PINS 
boolean toggle[4] = {0, 0, 0, 0};
boolean bstate[4] = {0, 0, 0, 0};
boolean _bstate[4] = {1, 1, 1, 1};


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++){
    pinMode(inputs[i], INPUT_PULLUP);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < 4; i++){
    bstate[i] = digitalRead(inputs[i]);
    if( bstate[i] < 1 && _bstate[i] > 0 ){
      toggle[i] = !toggle[i];
    }
    _bstate[i] = bstate[i];
    digitalWrite(leds[i], toggle[i]);
    Serial.print(toggle[i]);
    Serial.print(" ");
  }
  Serial.println();
}
