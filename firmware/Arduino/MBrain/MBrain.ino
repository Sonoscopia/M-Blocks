/* 
 *  M-Brain (Slave Receiver) using Arduino Mega
 *  prototype version with four buttons (Note Map, CC Map, Load, Save
 *  7 leds to display values from 0 to 127 in binary format
 *  rotary is connected to pins 2 and 3 
 *  rotary button is connected to pin 33 (with INPUT_PULLUP)
 *  buttons are connected to input pins 37, 36, 35 and 34 (with INPUT_PULLUP)
 *  buttons are connected to PORTC
 *  leds are connected to analog inputs A0 to A6 (PORTF)
 *  Created: 24-08-2019
 *  Author: Tiago Ângelo (aka p1nh0)
*/

#include <Wire.h>
#include <MIDI.h>
#include <Rotary.h>

#define ADDR 8 // this device address
#define NUMBYTES 4 // number of bytes using in communication from M-Controllers to M-Brain
#define PIN1 2 // rotary pins
#define PIN2 3 // rotary pins
#define MIDICH 1 // MIDI channel 
#define DEBUG 1

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

Rotary rotary = Rotary(PIN1, PIN2);
// Counter that will beincremented or decremented by rotation.
volatile byte counter = 0;

byte toggle[4] = {0, 0, 0, 0}; // values received from M-Toggle
byte innertoggle[4] = {0, 0, 0, 0}; // values stored in M-Brain to check for changes
boolean received = false; 
byte notemap[4] = {0, 1, 2, 3}; // map toggle values to MIDI notes  
byte velmap[4] = {127, 127, 127, 127}; 

void setup() {
  Wire.begin(ADDR); 
  Wire.onReceive(receiveI2C);
  if(DEBUG) Serial.begin(9600);
  MIDI.begin(MIDICH);
  // Rotary interrupts
  attachInterrupt(digitalPinToInterrupt(PIN1), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN2), rotate, CHANGE);
  Serial.print("interrupt pin1: ");
  Serial.println(digitalPinToInterrupt(PIN1));
  Serial.print("interrupt pin2: ");
  Serial.println(digitalPinToInterrupt(PIN2));
  
  DDRF = 0b11111111; // analog A0 to A7 as outputs
  DDRC = 0b00000000; //
  PORTC = 0xFF; // enable input pullup on pins 37 to 30
}

void loop() {
  PORTF = counter; // light leds
  
  if(received){ // if I2C data is received
    
    if(PINC != 0){ // if no buttons are pressed
      for(int i = 0; i < 4; i++){
        if(innertoggle[i] != toggle[i]){
          innertoggle[i] = toggle[i];
          if(toggle[i]>0)   MIDI.sendNoteOn(notemap[i], velmap[i], MIDICH);
          else              MIDI.sendNoteOff(notemap[i], 0, MIDICH);
        }
      }
    }
    received = false; 
  }
  
}

void receiveI2C(int howmany){
  byte index = 0; 
  received = true; 
  while(Wire.available()){
    byte v = Wire.read();
    toggle[index] = v;
    index++;
    if(DEBUG) Serial.print(v);
    if(DEBUG) Serial.print(" "); 
  }
  if(!Wire.available()) Serial.println(); // print line when no more bytes are available
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  volatile unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
    if(DEBUG) Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
    if(DEBUG) Serial.println(counter);
  }
}
