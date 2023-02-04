/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/* 
 *	Version: 0.1.1 (protobrain)
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
void blinkConfirm();
//End of Auto generated function prototypes by Atmel Studio

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

Rotary rotary = Rotary(PIN1, PIN2);

volatile byte counter = 0; // Counter that will be incremented or decremented by rotation.
volatile boolean received = false; 
volatile byte message[NUMBYTES]; // used to read I2C message

// event mapping arrays (stored and recalled from EEPROM) 
byte chmap[128];
byte notemap[128];
byte velmap[128];
byte ccmap[128]; 
byte globalch = 1; // set global channel 
byte preset = 0; // current preset
uint16_t loc = 0; // memory location
boolean first = true; 

void setup() {
  Wire.begin(ADDR); 
  Wire.onReceive(receiveI2C);
  
  // Rotary interrupts
  attachInterrupt(digitalPinToInterrupt(PIN1), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN2), rotate, CHANGE);
  
  // Pin Setup
  DDRF = 0b11111111; // analog A0 to A6 as outputs (leds)
  DDRC = 0b11100000; // set pins 37 to 33 as inputs (buttons)
  PORTC = 0b00011111; // enable input pullup on pins 37 to 33
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  	  
  // Midi  
  MIDI.begin(globalch);
  
  // RESET PRESET MEMORY (see GLOBALS)
  if(PINC == RESET){
	for(int i = 0; i < 128; i++){
		// reset channel map
		loc = CHOFFSET + i;
		EEPROM.update(loc, DEFAULTCH); 
		chmap[i] = EEPROM.read(loc);
		// reset notemap
		loc = NOTEOFFSET + i;
		EEPROM.update(loc, DEFAULTNOTE); 
		notemap[i] = EEPROM.read(loc);
		// reset velmap
		loc = VELOFFSET + i;
		EEPROM.update(loc, DEFAULTVEL);
		velmap[i] = EEPROM.read(loc);
		// reset ccmap
		loc = CCOFFSET + i; 
		EEPROM.update(loc, DEFAULTCC); 
		ccmap[i] = EEPROM.read(loc);
	}
	loc = 0; // reset memory location
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
  }
  
}

void loop(){	
	switch(PINC){
		//############### NOTE MAP ###############################################
		case NMAP:
			if(notemap[message[0]] < 128) counter = notemap[message[0]]; // set ENCODER value
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
					notemap[message[0]] = counter; // store value in memory (preset=0)
					EEPROM.update(NOTEOFFSET + message[0], counter);
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
			counter = velmap[message[0]]; // set ENCODER value
			
			if (!received)
			{
				Timer1.initialize(BLINK4X);
				Timer1.attachInterrupt( timerISR ); // blink LEDS 2x a second
			}
		
			while(received){
				Timer1.detachInterrupt();
				PORTF = counter; // display value
			
				if(PINC == ENTER) {
					velmap[message[0]] = counter; // store value in memory (preset=0)
					EEPROM.update(VELOFFSET + message[0], counter);
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
			if(ccmap[message[0]] < 128) counter = ccmap[message[0]]; // set ENCODER value
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
					ccmap[message[0]] = counter; // store value in memory (preset=0)
					EEPROM.update(CCOFFSET + message[0], counter);
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
			counter = chmap[message[0]]; // set ENCODER value
			
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
					chmap[message[0]] = counter; // store value in memory (preset=0)
					EEPROM.update(CHOFFSET + message[0], counter);
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
						resetMsg();
						//PORTF = 0x00; // turn all LEDS off
						//received = false;
					}
					else{
						if(PINC == LOADB) { // CANCEL
							resetMsg();
							//PORTF = 0x00; // turn all LEDS off
							//received = false;
						}
					}
				}
				break;
				//############### LOAD PRESET ####################################
				case  LOADB:
					// CANCEL (1st time press only!)
					if(first){
						Timer1.detachInterrupt(); // turn leds off if mapping mode is engaged but is the cancelled after pressing LOAD
						PORTF = 0x00; // turn all LEDS off
						preset = 0;
						counter = 0;
						first = false; 	
					} // CANCEL 
					else{ // SELECT PRESET TO LOAD
						if(counter > 7) counter = 0;
						preset = counter;
						PORTF = (BIT(preset) >> 1) ^ 0xFF; // unlit led represents selected preset, if all leds on preset=0 (0xFF = 0b11111111)	
					}
				break;
				
				case LOADYES:
					for(int i = 0; i < 128; i++){
						// load channel map
						loc = (preset << 9) + CHOFFSET + i;
						chmap[i] = EEPROM.read(loc);
						// load note map
						loc = (preset << 9) + NOTEOFFSET + i;
						notemap[i] = EEPROM.read(loc);
						// load velocity map
						loc = (preset << 9) + VELOFFSET + i;
						velmap[i] = EEPROM.read(loc);
						// load cc map
						loc = (preset << 9) + CCOFFSET + i;
						ccmap[i] = EEPROM.read(loc);
					}
					blinkConfirm();
				break;
				
				//############### SAVE PRESET ####################################
				case SAVEB: // SELECT PRESET TO SAVE
					if(counter > 7) counter = 0;
					preset = counter;
					PORTF = (BIT(preset) >> 1) ^ 0xFF; // unlit led represents selected preset, if all leds on preset=0 (0xFF = 0b11111111)	
				break;
				
				case SAVEYES: // save preset 0 to a selected preset slot
					for(int i = 0; i < 128; i++){  
						// save channel map
						loc = (preset << 9) + CHOFFSET + i;
						EEPROM.update(loc, chmap[i]);
						// save note map
						loc = (preset << 9) + NOTEOFFSET + i;
						EEPROM.update(loc, notemap[i]);
						// save velocity map
						loc = (preset << 9) + VELOFFSET + i;
						EEPROM.update(loc, velmap[i]);
						// save cc map
						loc = (preset << 9) + CCOFFSET + i;
						EEPROM.update(loc, ccmap[i]);
					}
					blinkConfirm();
				break;
				
		//############### PLAY MODE ##############################################
		default: // no buttons pressed
			// PLAY MODE EXECUTION runs inside the I2C ISR to avoid processing messages while others are arriving in a different routine
			first = true; // reset (used for LOAD/CANCEL behaviour)
			preset = 0; // reset preset to 0 if all buttons are released
			PORTF = 0x00; // turn all LED's off
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
	// PLAY MODE EXECUTION
	// message[0] -> MController address (0..127), message[1] -> MController value (0..127)
	if(PINC == PLAYMODE){
		byte ch; // channel variable visible to PLAY MODE only
			
		if (chmap[message[0]] > 0 ) ch = chmap[message[0]];	// use chmap if there is one
		else ch = globalch; // if channel is 0 then use global channel
			
		if (notemap[message[0]] < 128) // if there's a notemap stored
		{
			if(message[1] > 0){
				 if(message[1]<= velmap[message[0]]) MIDI.sendNoteOn(notemap[message[0]], message[1], ch); // if velocity is lower than set maximum velocity, send received velocity
				 else MIDI.sendNoteOn(notemap[message[0]], velmap[message[0]], ch); // else, send set maximum velocity (default = 127) 
			}
			else MIDI.sendNoteOff(notemap[message[0]], 0, ch);
		}
			
		if (ccmap[message[0]] < 128) // if there's a ccmap stored
		{
			MIDI.sendControlChange(ccmap[message[0]], message[1], ch);
		}
		
		received = false; // clear flag	
	} 
	
	received = true;
}


// reset I2C message
void resetMsg(){
	PORTF = 0x00; // turn all LEDS off
	received = false;
	//first = true; 
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

void blinkConfirm(){
	PORTF = 0x00;
	
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	PORTF ^= 0b01111111;
	delay(100);
	
	PORTF = 0x00;
}