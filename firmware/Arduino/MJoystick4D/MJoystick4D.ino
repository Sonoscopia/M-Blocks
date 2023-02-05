/* 
 *  M-Joystick (Master Sender) using Arduino Pro Mini
 *  version 0.1.0
 *  
 *  Created: 12-11-2020
 *  Author: Tiago Ângelo (aka p1nh0)
*/
 
#include <Wire.h>

#define NUMBYTES 2 // number of bytes using in communication from M-Controllers to M-Brain
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define MADDR 4 // M-Controller address
#define MADDRSIZE 5 // addres size in bits (5-bits: 0 to 31)
#define DEBUG 0
#define W 0.5f //exponential smoothing weight - 0 = slow, very smoothed; 1 = fast, no smooth 
// implemented to filter some noise on the analogRead
// probably caused by crappy potentiometers on the joystick?! 
// => try replacing the potentiometers...


char inputs[2] = {A1, A0}; // BUTTON PINS (X, Y)
int X, Y; 
                  // {X+, X-, Y+, Y-}
float XY4D[4] =        {0,  0 , 0 , 0 }; // 'real-time' analog pots reading                   
float potstate[4]  = {0 , 0 , 0 , 0 }; // current smoothed value; using floats because of the exponential filter
float _potstate[4] = {0 , 0 , 0 , 0 }; // last smoothed value; using floats because of the exponential filter
boolean changed = false; // used to check if toggles have changed 
byte addr = MADDR;
byte message[2] = {addr, potstate[0]};

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
  if(DEBUG) Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // use built-in led to check for ADC flickers
  digitalWrite(LED_BUILTIN, LOW); 
  
  // update values upon startup
  X = setX(analogRead(inputs[0]));
  Y = setY(analogRead(inputs[1])); 
  XYto4D(X, Y, XY4D);
  XYto4D(X, Y, potstate); 
  _potstateUpdate();
}

void loop() {
  X = setX(analogRead(inputs[0]));
  Y = setY(analogRead(inputs[1])); 
  XYto4D(X, Y, XY4D);
  
  for (int i = 0; i < 4; i++){
    potstate[i] = expFilter(XY4D[i], _potstate[i], W);
    potstate[i] = round(potstate[i]);
    
    if( potstate[i] != _potstate[i] ){
      digitalWrite(LED_BUILTIN, HIGH); 
       // prepare message to send through I2C
      message[0] = MADDR + (i << MADDRSIZE);
      message[1] = (byte)(round(potstate[i])); // 0..127
      // send I2C message      
      Wire.beginTransmission(BRAIN);
      Wire.write(message, NUMBYTES);
      Wire.endTransmission();
      
      // DEBUG I2C MESSAGES
      if(DEBUG){
        changed = true; 
        Serial.print("I2C message to M-Brain on addr=");
        Serial.print(BRAIN);
        Serial.println(" :");
        Serial.print("ctrl_addres: ");
        Serial.print(message[0], BIN);
        Serial.print(" | ctrl_value: ");
        Serial.println(message[1]); 
      }
    }
    _potstate[i] = potstate[i];
  }
  
  // DEBUG HARDWARE CONTROLLERS
  if(changed && DEBUG ){
    for(int i=0; i < 4; i++){
      Serial.print(potstate[i]);
      Serial.print(" ");
    }
    Serial.println();
    changed = false;
  }
  
  digitalWrite(LED_BUILTIN, LOW);
}

// exponential smoothing formula: Yn = (w * Xn) + ((1-w) * Yn-1); 0 >= w <= 1; Xn = new value; Yn-1 = last smoothed value; 
float expFilter(float Xn, float Yn1, float w){
  return (w * Xn) + ((1.f-w) * Yn1); 
}

// set pot X value (-127 to 128)
int setX(int ar){
  int _x = 128 - (ar>>2);
  return _x; 
}
// set pot Y value (-127 to 128)
int setY(int ar){
  int _y = -127 + (ar>>2);
  return _y;
}

// convert X and Y to 4dimensions (X+, X-, Y+, Y-)
void XYto4D(int x, int y, float *d){
  if(x > 0){
      d[0] = x - 1;
      d[1] = 0; 
  }
  else {
    d[0]= 0;
    d[1] = abs(x);
  }

  if(Y > 0){
      d[2] = y - 1;
      d[3] = 0; 
  }
  else {
    d[2] = 0;
    d[3] = abs(y);
  }
}

void _potstateUpdate(){
  for(int i = 0; i < 4; i++){
    _potstate[i] = potstate[i];
  }
}
