/*
  IKTHOF Quick Draw Timer
  Mark Russell 15-Sep-19
  https://nootropicdesign.com/digit-shield/
  https://www.arduino.cc/en/tutorial/knock
*/

#include <DigitShield.h>

double time, start, stop = 0;                 // timer, counter start, counter stop
int sensitivity = 13;                     // adjust this to adjust sensitivity
const int thunkSensor = A0;               // the pin for the piezo 

void setup() {
  DigitShield.begin();                    // display activate
  DigitShield.setPrecision(3);            // thousandths of a second
  DigitShield.setBlank(true);             // display off
}

void loop() {
  // 3 second countdown timer, and then listen for a knock, or bail after 5 seconds, display the time for 10 seconds
  DigitShield.setLeadingZeros(true);        // start display with zero's
  DigitShield.setBlank(false);              // display on
  delay(3000);                              // 3 second boot

    for (int i=3; i>0; i--) {         // 3 second flashing countdown                
     delay(500);                      // pauses for 1/2 second for flashing
     DigitShield.setBlank(true);      // display off
     delay(500);                      // pauses for 1/2 second for flashing
     DigitShield.setValue(i);         // set value
     DigitShield.setBlank(false);     // display on
   }
  delay(500);                         // pauses for 1/2 second for flashing
  DigitShield.setBlank(true);         // display off
  delay(500);                         // pauses for 1/2 second for flashing
  //DigitShield.setValue(0);            // show 0
  DigitShield.setDigit(2, 6);         // G in .GO.
  DigitShield.setDigit(3, 0);         // O in .GO.
  DigitShield.setDecimalPoint(1, true);         // . in .GO.
  DigitShield.setDecimalPoint(3, true);         // . in .GO.
  DigitShield.setBlank(false);        // display on
  start = millis();                   // start timing at .GO.
  //time = 0;                           // initialize timer
  delay(500);                         // pauses for 1/2 second for flashing
  DigitShield.setBlank(true);         // display off
  
  // listen for a thunk for 5 seconds
  while (time < 5.555){               // if no thunk after 5 seconds, bail
    time = (millis()-start)/1000;     // start keeping time
    
    // listen for a thunk
    if (analogRead(thunkSensor) >= sensitivity)  // if sensor greater than sensitivity
    {
      break;                                     // leave the loop
    }   
  }
    stop = millis();                  // record when we left the loop
  
  // wait, showing the score
  while (true) {
    //DigitShield.setPrecision(3);              // thousandths of a second
    DigitShield.setValue((stop-start)/1000);  // calc + set the time
    DigitShield.setBlank(false);              // display on
    delay(10000);                             // hold to display score
  }
}
