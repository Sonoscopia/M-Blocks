# TO DO 

- change all M-Encoders debug baud rate to 9600 (it's just more common!...)

- hardware fix on M-Brain: protect TRRS sockets from delivering 12V to the I2C SCL and SDA connections when connecting cables after the unit is already powered (can this be done only in the M-Brain instead of adding circuitry to all M-Controllers ???)

- make code for: M-Encoders and M-Trackpad

- M-Brain: check resetMsg() - does it need to be called so often ??? 

- M-Brain: resetMsg() function name is misleading!! Change name

- M-Brain: line:272 - does setting the global channel needs to have an I2C message received ?!?!?!

- make M-Brain code a bit more efficient (leave original code commented to facilitate understanding)

- implement USB MIDI 

- buy/apply rubber feet to the cases

- buy/apply velcro dust protection on the M-Fader faders


# NOTES

- the M-Encoder board (eagle file) is a bit messy: clean it up!