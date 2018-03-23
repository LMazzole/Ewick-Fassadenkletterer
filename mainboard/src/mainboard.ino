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
#inlcude "pneumatic.h"
#include "winch.h"
#include "VirtuinoBluetooth.h"


Drive drive;
Communicate bluetooth(Serial1,9600);

//=============================================================================================================
void setup(){
  // Overview over the PIN-defines are in global.h

  Serial.begin(9600);                // Set serial monitor baud rate

  bluetooth.DEBUG=true;               // set this value TRUE to enable the serial monitor status


  // Use virtuino.vPinMode instead default pinMode method for digital input or digital output pins.
   //pinMode(pinalias, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
   bluetooth.vPinMode(testLED,OUTPUT);

   //== PIN MOTOR====
   //==UP



   //==DOWN


   //== PIN WINCH====


   //== PIN PNEUMATIC


}

//=========================================================================================
void loop(){

bluetooth.run();
// drive.test();


}
