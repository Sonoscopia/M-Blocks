/*
 * GLOBALS.h
 *
 * Created: 25-08-2019 01:03:30
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

// COMPILER (default="Os")
#define OPTIMIZATION "O2"
#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)
// MACROS
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
// DEFINITIONS
#define ADDR 8 // this device address
#define NUMBYTES 4 // number of bytes using in communication from M-Controllers to M-Brain
#define PIN1 2 // rotary pins
#define PIN2 3 // rotary pins
#define MIDICH 1 // MIDI channel

#define PLAYMODE 0x1F // 31: play mode
#define NMAP 0x1E // note map button code
#define VMAP 0x1D// velocity map button code
#define CCMAP 0x1C// cc map button code (= note+velocity buttons)
#define LOADB 0x1B// load button code
#define SAVEB 0x17 // save button code
#define ENTER 0x0F //15: encoder button code 

#define VELOFFSET 128
#define CCOFFSET 256

#define DEBUG 1 // Debug code (send data to Serial)
#define RESETMACHINEDATA 0



#endif /* GLOBALS_H_ */