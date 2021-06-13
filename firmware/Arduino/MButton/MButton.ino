/* 
 *  M-Button (Master Sender) using Arduino Pro Mini
 *  version 0.1.0
 *  
 *  Created: 16-12-2020
 *  Author: Tiago Ângelo (aka p1nh0)
*/

#include <Wire.h>

#define bit_get(p,m) ((p) & (m))
#define BIT(x)(0x01 << (x))

#define MADDR 2 // M-Controller address
#define MADDRSIZE 5 // addres size in bits (5-bits: 0 to 31)
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define NUMBYTES 2 // number of bytes using in communication from M-Controllers to M-Brain
#define DEBUG 0

uint8_t state = 0b00001111; // PINC state (ANALOG INPUTS || watch out for A4/A5 ->used in I2C) 
uint8_t prevState = state;
uint8_t buttons[4] = {0, 0, 0, 0};
uint8_t _buttons[4] = {0, 0, 0, 0}; 
byte reading;
byte addr = MADDR;
byte message[2] = {addr, buttons[0]};

// button debouncing variables (see: /Examples/Digital/Debounce
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers

void setup() {
  Wire.begin();// join i2c bus (address optional for master)
  if(DEBUG) Serial.begin(115200);
  
  // hardware setup
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  reading = PINC << 4;
  prevState = reading;
}

void loop() {
  reading = PINC << 4;
  
  if(reading != prevState){
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    state = reading >> 4;
    Serial.println("bang");
    for(int i = 0; i < 4; i++){
      buttons[i] = 1 - (bit_get(state, BIT(i)));
      if(buttons[i] != _buttons[i]){
        Serial.print(i); Serial.print(" ");
        Serial.println(buttons[i]);
        // prepare message to send through I2C
        message[0] = MADDR + (i << MADDRSIZE);
        message[1] = buttons[i] * 127;
        // send I2C message      
        Wire.beginTransmission(BRAIN);
        Wire.write(message, NUMBYTES);
        Wire.endTransmission();

        _buttons[i] = buttons[i];
        
        if(!DEBUG){
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
    
  }

  prevState = reading;
}
