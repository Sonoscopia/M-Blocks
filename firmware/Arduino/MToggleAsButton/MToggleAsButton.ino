/* 
 *  M-Toggle (Master Sender) using Arduino Pro Mini
 *  version 0.1.0
 *  
 *  this is a special code made specifically to control PHOBOS
 *  it basically acts like M-Button but it still lights up the LEDS, so...no toggle functionality
 *  
 *  Created: 12-11-2020
 *  Author: Tiago Ângelo (aka p1nh0)
*/

#include <Wire.h>

#define MADDR 0 // M-Controller address
#define MADDRSIZE 5 // addres size in bits (5-bits: 0 to 31)
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define NUMBYTES 2 // number of bytes using in communication from M-Controllers to M-Brain
#define DEBUG 0

char inputs[4] = {A0, A1, A2, A3}; // BUTTON PINS 
byte leds[4] = {2, 3, 4, 7}; // LED PINS 
byte buttons[4] = {0, 0, 0, 0};
byte _buttons[4] = {0, 0, 0, 0};
long lastDebounceTime[4] = {0, 0, 0, 0};  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers
boolean changed = false; // used to check if toggles have changed 
byte addr = MADDR;
byte message[2] = {addr, buttons[0]};

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
  if(DEBUG) Serial.begin(115200);
  
  // hardware setup
  for(int i = 0; i < 4; i++){
    pinMode(inputs[i], INPUT_PULLUP);
    pinMode(leds[i], OUTPUT); // led setup 
    digitalWrite(leds[i], LOW); // turn all leds off
  }
}

void loop() {
  for (int i = 0; i < 4; i++){
    buttons[i] = 1 - (analogRead(inputs[i])>>9); //read current button state
    if (buttons[i]) digitalWrite(leds[i], HIGH);
    else digitalWrite(leds[i], LOW);
    
    if(buttons[i] != _buttons[i]){
      lastDebounceTime[i] = millis();    
    }

    if((millis() - lastDebounceTime[i]) > debounceDelay){
      _buttons[i] = buttons[i];
    }

    if(buttons[i] != _buttons[i]){
      _buttons[i] = buttons[i];
      // prepare message to send through I2C
      message[0] = MADDR + (i << MADDRSIZE);
      message[1] = buttons[i] * 127;
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
  }
  // DEBUG HARDWARE CONTROLLERS
  if(changed && DEBUG ){
    for(int i=0; i < 4; i++){
      Serial.print(buttons[i]);
      Serial.print(" ");
    }
    Serial.println();
    changed = false;
  }
}

