/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/* 
 *	Version: 0.1.0 (protobrain)
 *	Created: 12-11-2020
 *  Author: Tiago Ângelo (aka p1nh0)
*/

/* 
 *  M-Brain (Slave Receiver) using Arduino Mega
 *  prototype version with four buttons (Note Map, CC Map, Load, Save)
 *  7 leds to display values from 0 to 127 in binary format
 *  rotary is connected to pins 2 and 3 
 *  rotary button is connected to pin 33 (with INPUT_PULLUP)
 *  buttons are connected to input pins 37, 36, 35 and 34 (with INPUT_PULLUP)
 *  buttons are connected to PORTC
 *  leds are connected to analog inputs A0 to A6 (PORTF)
*/

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

// Libraries
#include <Wire.h>
#include <EEPROM.h>
#include <MIDI.h>
#include <Rotary.h>
#include <TimerOne.h>

// My headers and classes 
#include "GLOBALS.h"

//Beginning of Auto generated function prototypes by Atmel Studio
void receiveI2C(int howmany);
void resetMsg(); // reset I2C message
void rotate();
void timerISR();
void michaelKnight(uint16_t t, boolean d);
//End of Auto generated function prototypes by Atmel Studio

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

Rotary rotary = Rotary(PIN1, PIN2);

volatile byte counter = 0; // Counter that will be incremented or decremented by rotation.
volatile boolean received = false; 
byte message[NUMBYTES]; // used to read I2C message
byte maddr, mval; // easy access of I2C messages

// event mapping arrays (stored and recalled from EEPROM) 
uint8_t chmap[128];
int8_t notemap[128];
int8_t velmap[128];
int8_t ccmap[128]; 
uint8_t globalch = 1; // set global channel 
uint8_t preset = 0; // current preset

boolean debug = true;

void setup() {
  Wire.begin(ADDR); 
  Wire.onReceive(receiveI2C);
  
  // Rotary interrupts
  attachInterrupt(digitalPinToInterrupt(PIN1), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN2), rotate, CHANGE);
  if(debug) Serial.print("interrupt pin1: ");
  if(debug) Serial.println(digitalPinToInterrupt(PIN1));
  if(debug) Serial.print("interrupt pin2: ");
  if(debug) Serial.println(digitalPinToInterrupt(PIN2));
  
  // Pin Setup
  DDRF = 0b11111111; // analog A0 to A6 as outputs (leds)
  DDRC = 0b11100000; // set pins 37 to 33 as inputs (buttons)
  PORTC = 0b00011111; // enable input pullup on pins 37 to 33
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Debug
  if(PINC == ENTER){
	Serial.begin(BDRATE);
	debug = true;
  }
  else if(debug) { Serial.begin(BDRATE); Serial.println("DEBUG MODE"); }
  
  // Midi  
  MIDI.begin(globalch);
  
  // RESET PRESET MEMORY (see GLOBALS)
  if(PINC == RESET){
	for(int i = 0; i < 128; i++){
		// reset channel map
		chmap[i] = 0;
		EEPROM.write(CHOFFSET + i, 0); 
		// reset notemap
		notemap[i] = -1;
		EEPROM.write(NOTEOFFSET + i, -1); 
		// reset velmap
		velmap[i] = 127;
		EEPROM.write(VELOFFSET + i, 127);
		// reset ccmap
		ccmap[i] = -1; 
		EEPROM.write(CCOFFSET + i, -1); 
	}
	if(debug) Serial.println("RESET preset 0");
	michaelKnight(100, 1);
  }
  else{
	  // LOAD machine previous state (aka Preset 0)
	  for(int i = 0; i < 128; i++){
		  chmap[i] = EEPROM.read(CHOFFSET + i);
		  notemap[i] = EEPROM.read(NOTEOFFSET + i);
		  velmap[i] = EEPROM.read(VELOFFSET + i);
		  ccmap[i] = EEPROM.read(CCOFFSET +	i);
	  }
	  michaelKnight(100, 0);
	  if(debug) Serial.println("LOADED preset 0");
  }
  
}

void loop(){
	if(received){
		maddr = message[0]; // memory address (from 0 to 127, representing each controller of each M-Controller)
		mval = message[1]; // controller value (ex: knob value, button, etc.)
		if(debug){ Serial.print( "M-Controller ID:" ); Serial.println( get_maddr(maddr) ); Serial.print( "Controller#" );
					Serial.print( get_ctrl(maddr) ); Serial.print( " = " ); Serial.println( mval );
		}	
	}
		
	switch(PINC){
		//############### NOTE MAP ###############################################
		case NMAP:
			if(debug) Serial.println("NOTE MAP MODE");
			if(notemap[maddr] > -1) counter = notemap[maddr]; // set ENCODER value
			else counter = 0; 
			
			if (!received)
			{
				Timer1.initialize(BLINK2X); 
				Timer1.attachInterrupt( timerISR ); // blink LEDS 2x a second
			}
			
			while(received){
				Timer1.detachInterrupt();
				PORTF = counter; // display value
				
				if(PINC == ENTER) { // STORE MAPPING
					notemap[maddr] = counter; // store value in volatile memory (preset=0)
					EEPROM.write(NOTEOFFSET + maddr, counter);
					resetMsg();
				}
				else{ 
					if(PINC == LOADB) { // CANCEL
						resetMsg();
					}
				}
			}
			break;
		
		//############### VELOCITY MAP ###########################################
		case VMAP:
			if(debug) Serial.println("VELOCITY MAP MODE");
			counter = velmap[maddr]; // set ENCODER value
			
			if (!received)
			{
				Timer1.initialize(BLINK4X);
				Timer1.attachInterrupt( timerISR ); // blink LEDS 2x a second
			}
		
			while(received){
				Timer1.detachInterrupt();
				PORTF = counter; // display value
			
				if(PINC == ENTER) {
					velmap[maddr] = counter; // store value in volatile memory (preset=0)
					EEPROM.write(VELOFFSET + maddr, counter);
					resetMsg();
				}
				else{
					if(PINC == LOADB) { // CANCEL
						resetMsg();
					}
				}
			}
			break;
		
		//############### CC MAP #################################################
		case CCMAP:
			if(debug) Serial.println("CC MAP MODE");
			if(ccmap[maddr] > -1) counter = ccmap[maddr]; // set ENCODER value
			else counter = 0; 
			
			if (!received)
			{
				Timer1.initialize(BLINK2X);
				Timer1.attachInterrupt( timerISR ); // blink LEDS 2x a second
			}
		
			while(received){
				Timer1.detachInterrupt();
				PORTF = counter; // display value
			
				if(PINC == ENTER) {
					ccmap[maddr] = counter; // store value in volatile memory (preset=0)
					EEPROM.write(CCOFFSET + maddr, counter);
					resetMsg();
				}
				else{
					if(PINC == LOADB) { // CANCEL
						resetMsg();
					}
				}
			}
			break;
		
		//############### CH MAP #################################################
		case CHMAP:
			if(debug) Serial.println("CHANNEL MAP MODE");
			counter = chmap[maddr]; // set ENCODER value
			
			if (!received)
			{
				Timer1.initialize(BLINK4X);
				Timer1.attachInterrupt( timerISR ); // blink LEDS 2x a second
			}
		
			while(received){
				Timer1.detachInterrupt();
				if(counter > 16) counter = 0;
				PORTF = counter; // display value
			
				if(PINC == ENTER) {
					chmap[maddr] = counter; // store value in volatile memory (preset=0)
					EEPROM.write(CHOFFSET + maddr, counter);
					resetMsg();
				}
				else{
					if(PINC == LOADB) { // CANCEL
						resetMsg();
					}
				}
			}
			break;
			
			//############### SET GLOBAL CHANNEL #################################
			case GCHSET:
				if(debug) Serial.println("SET GLOBAL CHANNEL");
				counter = globalch; // reset ENCODER value
				if (!received)
				{
					Timer1.initialize(BLINK2X);
					Timer1.attachInterrupt( timerISR ); // blink LEDS 2x a second
				}
			
				while(received){
					Timer1.detachInterrupt();
					if(counter > 16) counter = 1;
					if(counter < 1) counter = 16;
					PORTF = counter; // display value
				
					if(PINC == ENTER) {
						globalch = counter; // store value in volatile memory (preset=0)
						PORTF = 0x00; // turn all LEDS off
						received = false;
					}
					else{
						if(PINC == LOADB) { // CANCEL
							PORTF = 0x00; // turn all LEDS off
							received = false;
						}
					}
				}
				break;
				//############### LOAD PRESET ####################################
				case  LOADB:
					Timer1.detachInterrupt(); // turn leds off if mapping mode is engaged but is the cancelled after pressing LOAD
					PORTF = 0x00; // turn all LEDS off
				break;
				
		//############### PLAY MODE ##############################################
		default: // no buttons pressed
			if(received){ // if a message from a M-Controller is received
				if(debug){ Serial.print("PLAY: "); Serial.print(maddr, BIN); Serial.print(" | "); Serial.println(mval); }
		
				uint8_t ch; // channel variable visible to PLAY MODE only
				
				if (chmap[maddr] > 0 ) ch = chmap[maddr];	// use chmap if there is one
				else ch = globalch; // if channel is 0 then use global channel
				
				if (notemap[maddr] > -1 ) // if there's a notemap stored
				{
					if(mval > 0) MIDI.sendNoteOn(notemap[maddr], velmap[maddr], globalch);
					else MIDI.sendNoteOff(notemap[maddr], 0, globalch);
				}
				
				if (ccmap[maddr] > -1 ) // if there's a ccmap stored
				{
					MIDI.sendControlChange(ccmap[maddr], mval, globalch);
				}
				
				received = false; 
			}
		break;
	}
}

// called whenever an I2C message is received
void receiveI2C(int howmany){
	byte index = 0;
	while(Wire.available()){
		byte v = Wire.read();
		message[index] = v;
		index++;
	}
	received = true;
}

// reset I2C message
void resetMsg(){
	PORTF = 0x00; // turn all LEDS off
	received = false;
	maddr = -1;
	mval = -1;
	message[0] = -1;
	message[1] = -1; 
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  volatile unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
  // fold from 0 to 127
  if (counter > 127) counter = 0;
  } else if (result == DIR_CCW) {
    counter--;
  // fold from 0 to 127
  if (counter > 127) counter = 127;
  }
  
}

// timerISR uses TimerOne
void timerISR(){
	// toggle all 7-LED's 
	PORTF ^= 0b01111111; 
}

// Michael Knight LED movement
void michaelKnight(uint16_t t, boolean d){
	if(d<1){ // right-to-left direction
		for(int i=0; i < 7; i++){
			PORTF = 1 << i;
			delay(t);
		}
		for(int i=1; i < 8; i++){
			PORTF = 64 >> i;
			delay(t);
		}
	}
	else{ //left-to-right direction
		for(int i=0; i < 7; i++){
			PORTF = 64 >> i;
			delay(t);
		}
		for(int i=1; i < 8; i++){
			PORTF = 1 << i;
			delay(t);
		}
	}
	PORTF = 0x00; // safely set port to 0 (leds off)
}