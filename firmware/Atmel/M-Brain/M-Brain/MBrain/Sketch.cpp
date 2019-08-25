/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/* 
 *  M-Brain (Slave Receiver) using Arduino Mega
 *  prototype version with four buttons (Note Map, CC Map, Load, Save)
 *  7 leds to display values from 0 to 127 in binary format
 *  rotary is connected to pins 2 and 3 
 *  rotary button is connected to pin 33 (with INPUT_PULLUP)
 *  buttons are connected to input pins 37, 36, 35 and 34 (with INPUT_PULLUP)
 *  buttons are connected to PORTC
 *  leds are connected to analog inputs A0 to A6 (PORTF)
 *  Created: 24-08-2019
 *  Author: Tiago Ângelo (aka p1nh0)
*/

// Libraries
#include <Wire.h>
#include <EEPROM.h>
#include <MIDI.h>
#include <Rotary.h>
// My headers and classes 
#include "GLOBALS.h"

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

//Beginning of Auto generated function prototypes by Atmel Studio
void receiveI2C(int howmany);
void rotate();
//End of Auto generated function prototypes by Atmel Studio

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

Rotary rotary = Rotary(PIN1, PIN2);
// Counter that will beincremented or decremented by rotation.
volatile byte counter = 0;

byte toggle[4] = {0, 0, 0, 0}; // values received from M-Toggle
byte mtoggle[4] = {0, 0, 0, 0}; // values stored in M-Brain to check for changes
boolean received = false; 

// Arrays stored in EEPROM presets
byte notemap[128];
byte velmap[128];
byte ccmap[128]; 

int8_t veloffset, noteoffset;

byte mode = 0; 


void setup() {
  Wire.begin(ADDR); 
  Wire.onReceive(receiveI2C);
  
  if(DEBUG) Serial.begin(9600);
  
  MIDI.begin(MIDICH);
  
  // Rotary interrupts
  attachInterrupt(digitalPinToInterrupt(PIN1), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN2), rotate, CHANGE);
  if(DEBUG) Serial.print("interrupt pin1: ");
  if(DEBUG) Serial.println(digitalPinToInterrupt(PIN1));
  if(DEBUG) Serial.print("interrupt pin2: ");
  if(DEBUG) Serial.println(digitalPinToInterrupt(PIN2));
  
  DDRF = 0b01111111; // analog A0 to A6 as outputs (leds)
  DDRC = 0b11100000; // set pins 37 to 33 as inputs (buttons)
  PORTC = 0b00011111; // enable input pullup on pins 37 to 33
  
  // RESET PRESET MEMORY (see GLOBALS)
  if(RESETMACHINEDATA){
	for(int i = 0; i < 128; i++){
		EEPROM.write(i, 0); // reset notemap
		EEPROM.write(i+VELOFFSET, 127); // reset velmap
		EEPROM.write(i+CCOFFSET, 0); // reset ccmap
	}
	delay(1000);
  }
  
  // LOAD machine previous state (aka Preset 0)
  for(int i = 0; i < 128; i++){
    notemap[i] = EEPROM.read(i);
    velmap[i] = EEPROM.read(i+VELOFFSET);
    ccmap[i] = EEPROM.read(i+CCOFFSET);
  }
  delay(1000);
}


void loop() {
  if (DEBUG && mode != PINC){
    Serial.print("MODE: ");
    Serial.println(PINC, BIN);
    mode = PINC;    
  }
    
  switch(PINC){
    case NMAP: // NOTE MAP MODE
    counter = 0;
    while(received && PINC != ENTER){
      noteoffset = -1; 
      for (byte i = 0; i < 4; i++){ // check which button has changed
        if (mtoggle[i] != toggle[i]){
          noteoffset = i;
        }
      }
      if(noteoffset > -1){
        notemap[noteoffset] = counter;
        PORTF = counter; // light leds
        if(DEBUG){
          Serial.print("notemap[");
          Serial.print(noteoffset);
          Serial.print("] = ");
          Serial.println(counter);
        } 
      }
      
    }
    // write to memory (hold machine state prior to shutdown)
    if(noteoffset > -1){ // safeguard (avoid EEPROM writing errors)
      EEPROM.write(noteoffset, counter);  
    }
    // reset
    received = false;
    counter = 0;  
    PORTF = counter; // light leds
    break;
    
    case VMAP: // NOTE MAP MODE
    counter = 0;
    while(received && PINC != ENTER){
      veloffset = -1;
      for (byte i = 0; i < 4; i++){ // check which button has changed
        if (mtoggle[i] != toggle[i]){
          veloffset = i;
        }
      }
      if(veloffset > -1){
        velmap[veloffset] = counter;
        PORTF = counter; // light leds
        if(DEBUG){
          Serial.print("velmap[");
          Serial.print(veloffset);
          Serial.print("] = ");
          Serial.println(counter);
        }
      }
      
    }
    // write to memory (hold machine state prior to shutdown)
    if(veloffset > -1){ // safeguard (avoid EEPROM writing errors)
      EEPROM.write(veloffset+VELOFFSET, counter);
    }
    // reset
    received = false;
    counter = 0;
    PORTF = counter; // light leds
    break;
    
     
    default: // PLAY MODE
    for (byte i = 0; i < 4; i++){
      if(mtoggle[i] != toggle[i]){
        mtoggle[i] = toggle[i];
        if(toggle[i]>0)   MIDI.sendNoteOn(notemap[i], velmap[i], MIDICH);
        else              MIDI.sendNoteOff(notemap[i], 0, MIDICH);
      }
    }
    break;
  }
  
}

void receiveI2C(int howmany){
	byte index = 0;
	while(Wire.available()){
		byte v = Wire.read();
		toggle[index] = v;
		index++;
		if(DEBUG) Serial.print(v);
		if(DEBUG) Serial.print(" ");
	}
	received = true;
	// print line when no more bytes are available
	if(DEBUG && !Wire.available()){
		Serial.println();
		Serial.print("toggle: ");
		for(int i = 0; i < 4; i++){
			Serial.print(toggle[i]);
			Serial.print(" ");
		}
		Serial.println();
	}
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  volatile unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
  // fold from 0 to 127
  if (counter > 127) counter = 0;
    if(DEBUG) Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
  // fold from 0 to 127
  if (counter > 127) counter = 127;
    if(DEBUG) Serial.println(counter);
  }
  
}
