/*
 * GLOBALS.h
 *
 * Created: 15-06-2021 01:29:38
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#define MADDR 5 // M-Controller address (used for control change behaviour/modes1..3)
#define MADDR_N 6 // M-Controller address (used for note behaviour/mode4)
#define MADDRSIZE 5 // addres size in bits (5-bits: 0 to 31)
#define BRAIN 8 // Slave Receiver address (M-Brain)
#define NUMBYTES 2 // number of bytes using in communication from M-Controllers to M-Brain
#define DEBUG 1

// encoder+button behaviour, set at setup()
#define MODE1 0xe0 // button pressed + encoder = encoder value increment=M1_INC (default)
#define MODE2 0xd0 // button pressed + encoder = encoder value increment=M2_INC
#define MODE3 0xb0 // button pressed = encoder value min/max (set encoder value to either 0 or 127)
#define MODE4 0x70 // button pressed = "note out" to a separate M-Controller ID (=MADDR+1)
// to engage mode1 keep encoder button1 pressed and then power the unit
// press button2 for mode2, etc....
#define MLOC 0 // mode is stored on EEPROM address 0
// mode increments
#define M1_INC 8
#define M2_INC 4


#endif /* GLOBALS_H_ */