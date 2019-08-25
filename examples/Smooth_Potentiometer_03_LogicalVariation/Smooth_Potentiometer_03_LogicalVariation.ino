/*
 * Logical Variation Technique to smooth analogRead from potentiometers
 * 
 * this technique only outputs new values if current values are bigger/smaller than
 * current value by a given amount 
 * 
 */
#define diff 1

byte val, _val = 0; 

void setup() {
  Serial.begin(9600);
    
}

void loop() {
  val = analogRead(A1) >> 3; 
  if(val > _val + diff || val < _val - diff){
    _val = val; 
    Serial.println(val); 
  }
}
