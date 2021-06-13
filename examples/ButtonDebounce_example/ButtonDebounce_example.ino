int counter = 0;
byte state = 1, _state = 1; 
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(A0, INPUT_PULLUP);
}

void loop() {
  state = analogRead(A0)>>9; 
  if(state != _state){
    lastDebounceTime = millis();
    Serial.println("reset");
  }

  if((millis() - lastDebounceTime) > debounceDelay){
    _state = state; 
  }

  if(state != _state){
    counter++;
    Serial.println(counter);
    _state = state; 
  }
  
}
