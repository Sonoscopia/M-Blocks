# M-Blocks
Modular MIDI Controllers

## INFO
M-Blocks is a projected developed by Sonoscopia Associação Cultural (www.sonoscopia.pt). 
It consists of several MIDI controllers (M-Controllers) that can be patched to a receiving interface (M-Brain) in a modular fashion, that is, connecting an arbitrary number (32 max.) and type of controllers such as buttons, knobs, faders, encoders, etc. 
The M-Brain than receives data from all the controllers via and maps them to MIDI messages sent to the output, either through USB (future implementation) or MIDI DIN connections.
The communication between modules is made using I2C (Inter-Integrated Circuit) using the Arduino platform (www.arduino.cc).  

### Note to programmers
When programming an M-Brain for the first time do not forget to set the EEPROM memory using /utilities/EEPROM_Preset_Clear/


## CHANGELOG

### version 0.1.2 (phobosfeijoada)
Fully functional M-Brain prototype and M-Controllers.
Continuous controls (ex: knobs) can now output notes, [see commit](https://github.com/Sonoscopia/M-Blocks/commit/bef133f0ddcc1b52bf48fc73a7da5345fef3f352).
M-Toggle code was modified to (MToggleAsButton) acting as M-Button to work with Phobos.
There are still some bugs when programming M-Brain but it works as long as one follows the manual and pays attention to the LED's.

### version 0.1.1 (francesinha)
Fully functional M-Brain prototype and M-Controllers. Needs testing...

### version 0.1.0 (protobrain)
First working version for M-Brain protoype version (the version with LED's instead of a screen). 

### version 0.0.3 (gopro)
As the code for M-Brain is getting bigger I moved the code development to Atmel Studio. In the 'firmware' folder should be a version to compile in Arduino IDE for those of you who don't have Atmel Studio. 

### version 0.0.2 (whoisthemaster)
Inverted Master/Slave relationship. 
Now M-Brain is the slave and M-Controllers are masters.
This way the controllers send data whenever their hardware sensor data changes, while the slave (M-Brain) is requested to read this data. 

### version 0.0.1 (first prototype)
First working sketch containing two modules (MBrain and MToggle).
In this version the controller (MToggle) acts as a Slave device and MBrain acts as a Master device, where the slave is constantly sending data to the master with a flag to let the master know if data has changed or not. 





## CONTRIBUTORS 
Contributors: Gustavo Costa, Tiago Ângelo, Rui Dias, Ján Solčáni and PierrePierrePierre.

## DEPENDENCIES & ACKNOWLEDGEMENTS
- Wire library (https://www.arduino.cc/en/reference/wire) 
- EEPROM library (https://www.arduino.cc/en/Reference/EEPROM)
- Rotary library by Ben Buxton(https://github.com/brianlow/Rotary)
- MIDI Library by François Best (https://github.com/FortySevenEffects/arduino_midi_library)
- TimerOne Library (https://www.arduino.cc/reference/en/libraries/timerone/)

## LICENSE
[![CC BY-NC 4.0][cc-by-nc-shield]][cc-by-nc]

This work is licensed under a
[Creative Commons Attribution-NonCommercial 4.0 International License][cc-by-nc].

[![CC BY-NC 4.0][cc-by-nc-image]][cc-by-nc]

[cc-by-nc]: https://creativecommons.org/licenses/by-nc/4.0/
[cc-by-nc-image]: https://licensebuttons.net/l/by-nc/4.0/88x31.png
[cc-by-nc-shield]: https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg

