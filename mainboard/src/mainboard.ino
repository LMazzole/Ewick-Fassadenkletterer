//http://www.kramann.info/96_Arduino/24_OOP/index.php
//https://github.com/HSR-Stud/Willkommen

/* Includes */
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <stdio.h>

#include "global.h"
#include "comm.h"
#include "drive.h"
#include "pneumatic.h"
#include "winch.h"
#include "VirtuinoBluetooth.h"


Drive drive;
Communicate bluetooth(Serial1,9600);
Winch winch;

//=============================================================================================================
void setup(){

  // Overview over the PIN-defines are in global.h

  Serial.begin(9600);                // Set serial monitor baud rate
  Serial.println("Initialise Arduino");

  bluetooth.DEBUG=false;               // set this value TRUE to enable the serial monitor status


  // Use virtuino.vPinMode instead default pinMode method for digital input or digital output pins.
   //pinMode(pinalias, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
   bluetooth.vPinMode(testLED,OUTPUT);

   //== PIN STEPPER====
   //==LEFT

   //==RIGTH


   //== PIN WINCH====
   //==UP
   pinMode(WINCH_RELAIS_UP, OUTPUT);
   //==DOWN
   pinMode(WINCH_RELAIS_DOWN, OUTPUT);

   //== PIN PNEUMATIC ===


}

//=========================================================================================
void loop(){
Serial.println("===============Enter Loop===============");
delay(500);
// bluetooth.run();
// drive.test();

winch.test();

delay(5000);
}
