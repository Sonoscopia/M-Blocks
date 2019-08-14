/*
 * Example using the Rotary library, dumping integers to the serial
 * port. The integers increment or decrement depending on the direction
 * of rotation.
 *
 * This example uses interrupts rather than polling.
 */

#include <Rotary.h>
//#include <UTFT.h> 

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 2 and 3.
#define PIN1 6
#define PIN2 7
Rotary rotary = Rotary(PIN1, PIN2);

// Counter that will beincremented or decremented by rotation.
volatile int counter = 0;

//UTFT myGLCD(CTE32HR,38,39,40,41);

void setup() {
  Serial.begin(57600);
  attachInterrupt(digitalPinToInterrupt(PIN1), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN2), rotate, CHANGE);
  Serial.print("interrupt pin1: ");
  Serial.println(digitalPinToInterrupt(PIN1));
  Serial.print("interrupt pin2: ");
  Serial.println(digitalPinToInterrupt(PIN2));
  //myGLCD.InitLCD();
  //myGLCD.clrScr();
}

void loop() {
  //myGLCD.setColor(random(255), random(255), random(255));
  //myGLCD.fillRect(120, 120, 240, 240);
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  volatile unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
    Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
    Serial.println(counter);
  }
}

