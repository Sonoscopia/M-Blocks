/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/* M-Encoder (Master Sender) using Arduino Pro Mini
*  version 0.1.1
*
*  Created: 15-06-2021
*  Author: Tiago Ângelo (aka p1nh0)
* 
* It is the same code for M-Enc-C (continuous encoders) and M-Enc-D (detent encoders) 
*/

#include <Wire.h>
#include <EEPROM.h>
#include <Rotary.h>
#include "GLOBALS.h"

//Beginning of Auto generated function prototypes by Atmel Studio
void sendMessage(byte addr, byte value, int ctrl_id); // I2C message output
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

volatile byte counter[4] = {0, 0, 0, 0}; // encoders' values
byte buttons[4] = {0, 0, 0, 0}; // encoders' button press
byte _buttons[4] = {0, 0, 0, 0};
byte toggles[4] = {0, 0, 0, 0}; // exclusive to MODE3 (toggles value between 0 and 127)


byte mode;
byte message[2] = {MADDR, counter[0]};

void setup() {
	Wire.begin();// join i2c bus (address optional for master)
	if(DEBUG) Serial.begin(9600);
  
	// button setup
	for(int i = 0; i < 4; i++){
		pinMode(inputs[i], INPUT_PULLUP);
	}
  
	// set mode (encoder+button behaviour)
	byte p = PINC << 4; // read A0 to A3 and bitshift to ignore A4 to A7 
	switch(p){
		case MODE1:
			mode = MODE1;
			EEPROM.update(MLOC, mode);
			if(DEBUG){ Serial.print("mode = "); Serial.println(mode, HEX);}
		break;
	  
		case MODE2:
			mode = MODE2;
			EEPROM.update(MLOC, mode);
			if(DEBUG){ Serial.print("mode = "); Serial.println(mode, HEX);}
		break;
	  
		case MODE3:
			mode = MODE3;
			EEPROM.update(MLOC, mode);
			if(DEBUG){ Serial.print("mode = "); Serial.println(mode, HEX);}
		break;
	  
		case MODE4:
			mode = MODE4;
			EEPROM.update(MLOC, mode);
			if(DEBUG){ Serial.print("mode = "); Serial.println(mode, HEX);}
		break;
	  
		default:
			mode = EEPROM.read(MLOC);
			if(DEBUG){ Serial.print("mode = "); Serial.println(mode, HEX);}
		break;
	}	    
}

void loop(){
	switch(mode){
		case(MODE4): // pressing the encoder button sends values as another address (MADDR_N instead of MADDR) just like a MIDI keyboard press
		for(int i = 0; i < 4; i++){
			// READ ENCODER BUTTONS
			buttons[i] = 1 - (analogRead(inputs[i])>>9); //read current button state
			if(buttons[i] != _buttons[i]){
				_buttons[i] = buttons[i];
				if(DEBUG) printButton(i, buttons[i]*127);
				sendMessage(MADDR_N, buttons[i]*127, i);						// SEND I2C MESSAGE
			}
			// READ ENCODERS
			volatile unsigned char result = encoder[i].process();
			if (result == DIR_CW && counter[i] < 127) {
				counter[i]++;
				if(DEBUG) printEncoder(i, counter[i]);
				sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				} else if (result == DIR_CCW && counter[i] >0) {
				counter[i]--;
				printEncoder(i, counter[i]);
				sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
			}
		}
		break;
		
		case(MODE3): // pressing the encoder button toggles the value from 0 to 127
			for(int i = 0; i < 4; i++){
				// READ ENCODER BUTTONS
				buttons[i] = 1 - (analogRead(inputs[i])>>9); //read current button state
				if(buttons[i] != _buttons[i]){
					_buttons[i] = buttons[i];
					if(buttons[i]>0){
						toggles[i] = !toggles[i];
						counter[i] = toggles[i] * 127;
						if(DEBUG) printEncoder(i, counter[i]);
						sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
					} 
				}
				// READ ENCODERS
				volatile unsigned char result = encoder[i].process();
				if (result == DIR_CW && counter[i] < 127) {
					counter[i]++;
					if(DEBUG) printEncoder(i, counter[i]);
					sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				} else if (result == DIR_CCW && counter[i] >0) {
					counter[i]--;
					printEncoder(i, counter[i]);
					sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				}
			}
		break;
		
		case(MODE2): // the only difference from MODE1 is the increment value (M2_INC instead of M1_INC)
			for(int i = 0; i < 4; i++){
				// READ ENCODER BUTTONS
				buttons[i] = 1 - (analogRead(inputs[i])>>9); //read current button state
				if(buttons[i] != _buttons[i]){
					_buttons[i] = buttons[i];
					if(DEBUG) printButton(i, buttons[i]);
				}
			
				// READ ENCODERS (short ifelse  (condition) ? true : false)
				volatile unsigned char result = encoder[i].process();
				if (result == DIR_CW && counter[i] < 127) {					// CLOCKWISE
					(buttons[i]) ? counter[i]+=M2_INC : counter[i]++;		// increment
					if(counter[i] > 127) counter[i] = 127;					// prevent out of bounds
					if(DEBUG) printEncoder(i, counter[i]);					// debug
					sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				
				} else if (result == DIR_CCW && counter[i] >0) {		// COUNTER CLOCKWISE
					(buttons[i]) ? counter[i]-=M2_INC : counter[i]--;		//decrement
					if(counter[i] > 127) counter[i] = 0;					// prevent out of bounds
					if(DEBUG) printEncoder(i, counter[i]);					// debug
					sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				}
			}
		break;
		
		default: // MODE1 (in default in case something wrong happens with the mode variable
			for(int i = 0; i < 4; i++){
				// READ ENCODER BUTTONS
				buttons[i] = 1 - (analogRead(inputs[i])>>9); //read current button state
				if(buttons[i] != _buttons[i]){
					_buttons[i] = buttons[i];
					if(DEBUG) printButton(i, buttons[i]);
				}
				
				// READ ENCODERS (short ifelse  (condition) ? true : false)
				volatile unsigned char result = encoder[i].process();
				if (result == DIR_CW && counter[i] < 127) {					// CLOCKWISE
					(buttons[i]) ? counter[i]+=M1_INC : counter[i]++;		//increment
					if(counter[i] > 127) counter[i] = 127;					// prevent out of bounds
					if(DEBUG) printEncoder(i, counter[i]);					// debug
					sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				
				} else if (result == DIR_CCW && counter[i] >0) {			// COUNTER CLOCKWISE
					(buttons[i]) ? counter[i]-=M1_INC : counter[i]--;		//decrement
					if(counter[i] > 127) counter[i] = 0;					// prevent out of bounds
					printEncoder(i, counter[i]);							// debug
					sendMessage(MADDR, counter[i], i);						// SEND I2C MESSAGE
				}
			}
		break; 
	}
}

// Send I2C message
void sendMessage(byte addr, byte value, int ctrl_id){
	// prepare message to send through I2C
	message[0] = addr + (ctrl_id << MADDRSIZE);
	message[1] = value;
	// send I2C message
	Wire.beginTransmission(BRAIN);
	Wire.write(message, NUMBYTES);
	Wire.endTransmission();
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
