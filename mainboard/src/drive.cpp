/*
 * drive.cpp
 *
 *  Created on: 08.03.2018
 *      Author: Luca
 */

#include "drive.h"
//#include <Serial.h>

Drive::Drive(){
}


void Drive::move(int direction, int distance, int velocity){
  //TODO Function implementieren
  //Serial.write(direction,2);
}

void Drive::test(){
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(50);                       // wait for a second
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     delay(50);
  }
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(2000);                       // wait for a second
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   delay(2000);

}
