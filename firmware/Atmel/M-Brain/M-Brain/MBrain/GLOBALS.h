/*
 * GLOBALS.h
 *
 * Created: 25-08-2019 01:03:30
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

// COMPILER (default="Os", prefered="O2")
#define OPTIMIZATION "Os"
#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)
// MACROS
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))
#define get_maddr(m) ((0b00011111) & (m)) // get M-Controller address from I2C message
#define get_ctrl(m)((m) >> (6)) // get M-Controller control number from I2C message (ex: knob1, button3, etc.)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
// DEFINITIONS
#define ADDR 8 // this device address
#define NUMBYTES 2 // number of bytes using in communication from M-Controllers to M-Brain
#define PIN1 2 // rotary pins
#define PIN2 3 // rotary pins

#define PLAYMODE 0x17 // play mode
#define NMAP 0x16  // note map button code
#define VMAP 0x14  // velocity map combo button code (NOTE + CC)
#define CCMAP 0x15 // cc map button code 
#define CHMAP 0x12 // channel map combo button code (NOTE + LOAD)
#define GCHSET 0x10 // set global channel combo button code (NOTE + CC + LOAD)
#define LOADB 0x13// load button code
#define LOADYES 0x03 // confirm load button combo (LOAD + ENTER)
#define SAVEB 0x1F // save button code
#define SAVEYES 0x0F // confirm save button combo (SAVE + ENTER)
#define ENTER 0x07 //15: encoder button code 
#define RESET 0x1B // RESET preset#0 (init blank state) 

// EEPROM MEMORY READ/WRITE OFFSETS
#define CHOFFSET 0 
#define NOTEOFFSET 128
#define	VELOFFSET 256
#define CCOFFSET 384
#define POFFSET 512 // preset offset
// DEFAULT PRESET VALUES
#define DEFAULTCH 0 // global channel
#define DEFAULTNOTE 255 // no note mapping
#define DEFAULTVEL 127 // maximum velocity
#define DEFAULTCC 255 // no CC mapping
// OTHER 
#define LEDS 0b01111111
#define BLINK2X 250000
#define BLINK4X 125000
#define DELAYLED 1000

#endif /* GLOBALS_H_ */