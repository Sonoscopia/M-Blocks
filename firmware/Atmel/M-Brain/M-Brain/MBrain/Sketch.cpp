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
}

void loop() {
	  
  switch(PINC){
	  case NMAP: // NOTE MAP MODE
		counter = 0;
		while(received && PINC != ENTER){
			int8_t j = -1; 
			for (byte i = 0; i < 4; i++){ // check which button has changed
				if (mtoggle[i] != toggle[i]){
					j = i;
				}
			}
			if(j > -1){
				notemap[j] = counter;
				PORTF = counter; // light leds
				if(DEBUG){
					Serial.print("notemap[");
					Serial.print(j);
					Serial.print("] = ");
					Serial.println(counter);
				}	
			}
			
		}
		received = false;
		counter = 0;  
		PORTF = counter; // light leds
	  break;
	  
	  case VMAP: // NOTE MAP MODE
	  counter = 0;
	  while(received && PINC != ENTER){
		  int8_t j = -1;
		  for (byte i = 0; i < 4; i++){ // check which button has changed
			  if (mtoggle[i] != toggle[i]){
				  j = i;
			  }
		  }
		  if(j > -1){
			  velmap[j] = counter;
			  PORTF = counter; // light leds
			  if(DEBUG){
				  Serial.print("velmap[");
				  Serial.print(j);
				  Serial.print("] = ");
				  Serial.println(counter);
			  }
		  }
		  
	  }
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
  received = true; 
  byte index = 0; 
  while(Wire.available()){  
    toggle[index] = Wire.read();;
    index++;
    if(DEBUG) Serial.print(toggle[index]);
    if(DEBUG) Serial.print(" "); 
  }
  // print line when no more bytes are available
  if(DEBUG && !Wire.available()) Serial.println(); 
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
