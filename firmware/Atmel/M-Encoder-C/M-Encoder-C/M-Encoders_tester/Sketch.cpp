/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/* Tester for M-Enc-C and M-Enc-D
 * this test uses the 'poll' method
 * it also tests the encoder buttons
 */

#include <Rotary.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void printEncoder(int j, byte c);
void printButton(int j, byte c);
//End of Auto generated function prototypes by Atmel Studio



// rotary encoder pins
byte encA[4] = {3, 7, 11, 13};
byte encB[4] = {2, 4, 8, 12};
// rotary button pins
char inputs[4] = {A0, A1, A2, A3};

// Rotary objects
Rotary encoder[4] = {
  Rotary(encA[0], encB[0]),
  Rotary(encA[1], encB[1]),
  Rotary(encA[2], encB[2]),
  Rotary(encA[3], encB[3]),
  };

volatile byte counter[4] = {0, 0, 0, 0}; 
byte buttons[4] = {0, 0, 0, 0};
byte _buttons[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  // button setup
  for(int i = 0; i < 4; i++){
    pinMode(inputs[i], INPUT_PULLUP);
  }  
}

void loop() {
  for(int i = 0; i < 4; i++){
    // read rotary encoders
    volatile unsigned char result = encoder[i].process();
    if (result == DIR_CW && counter[i] < 127) {
      counter[i]++;
      printEncoder(i, counter[i]);
    } else if (result == DIR_CCW && counter[i] >0) {
      counter[i]--;
      printEncoder(i, counter[i]);
    }
    // read rotary buttons
    buttons[i] = 1 - (analogRead(inputs[i])>>9); //read current button state
    if(buttons[i] != _buttons[i]){
      _buttons[i] = buttons[i];
      printButton(i, buttons[i]);
    }
  }
}

void printEncoder(int j, byte c){
  Serial.print("enc"); 
  Serial.print(j+1);
  Serial.print(": "); 
  Serial.println(c);
}
void printButton(int j, byte c){
  Serial.print("button"); 
  Serial.print(j+1);
  Serial.print(": "); 
  Serial.println(c);
}
