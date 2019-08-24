# M-Blocks
Modular MIDI Controllers

## INFO
M-Blocks is a projected developed by Sonoscopia Associação Cultural (www.sonoscopia.pt). 
It consists in a series of MIDI controllers (M-Controllers) that can be patched to a receiving interface (M-Brain) in a modular fashion, that is, connecting an arbitrary number and type of controllers such as buttons, knobs, faders, encoders, etc. 
The M-Brain than receives data from all the controllers and maps them to MIDI messages sent to the output, either through USB or MIDI DIN connections.
The communication between modules is made using I2C (Inter-Integrated Circuit) using the Arduino platform (www.arduino.cc).  

## CHANGELOG

### version 0.0.2 (whoisthemaster)
Inverted Master/Slave relationship. 
Now M-Brain is the slave and M-Controllers are masters.
This way the controllers send data whenever their hardware sensor data changes, while the slave (M-Brain) is requested to read this data. 

### version 0.0.1 (first prototype)
First working sketch containing two modules (MBrain and MToggle).
In this version the controller (MToggle) acts as a Slave device and MBrain acts as a Master device, where the slave is constantly sending data to the master with a flag to let the master know if data has changed or not. 


## CONTRIBUTORS 
Contributors: Gustavo Costa, Tiago Ângelo, Rui Dias, Ján Solčáni and PierrePierrePierre.