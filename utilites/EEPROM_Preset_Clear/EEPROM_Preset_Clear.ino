// Clear all presets and set EEPROM to default blank state
#include <EEPROM.h>

// EEPROM MEMORY READ/WRITE OFFSETS
#define CHOFFSET 0 
#define NOTEOFFSET 128
#define VELOFFSET 256
#define CCOFFSET 384
#define POFFSET 512 // preset offset
// DEFAULT VALUES
#define DEFAULTCH 0 // global channel 
#define DEFAULTNOTE 255 // no note mapping
#define DEFAULTVEL 127 // maximum velocity
#define DEFAULTCC 255 // no CC mapping
 
int loc = 0; 
int preset = 0; 

void setup() {
  for(int j = 0; j < 8; j++){
    preset = j * POFFSET; // preset starting address  
    for(int i = 0; i < 128; i++){
      // reset channel map
      loc = preset + CHOFFSET + i;
      EEPROM.update( loc, DEFAULTCH); 
      // reset notemap
      loc = preset + NOTEOFFSET + i;
      EEPROM.update( loc, DEFAULTNOTE); 
      // reset velmap
      loc = preset + VELOFFSET + i;
      EEPROM.update( loc, DEFAULTVEL);
      // reset ccmap
      loc = preset + CCOFFSET + i;
      EEPROM.update( loc, DEFAULTCC); 
    }
  }
  delay(1000);
}

void loop() {
  delay(1000);
  exit(0);
}
