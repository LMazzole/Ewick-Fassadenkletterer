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
Pneumatic pneumatic;

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
   //==UPSTAIRS
   pinMode(DRIVER_1_DIR, OUTPUT);
   pinMode(DRIVER_1_STEP, OUTPUT);
   pinMode(DRIVER_2_DIR, OUTPUT);
   pinMode(DRIVER_2_STEP, OUTPUT);
   // pinMode(DRIVER_1_DIR, OUTPUT);
   //pinMode(TREIBER_1_PIN_2);
   //pinMode(TREIBER_1_PIN_3);
   //pinMode(TREIBER_1_PIN_4);
   //==DOWNSTAIRS
   //pinMode(TREIBER_2_PIN_1);
   //pinMode(TREIBER_2_PIN_2);
   //pinMode(TREIBER_2_PIN_3);
   //pinMode(TREIBER_2_PIN_4);

   //== PIN WINCH====
   //==UP
   pinMode(WINCH_RELAIS_UP_1, OUTPUT);
   pinMode(WINCH_RELAIS_UP_2, OUTPUT);
   //==DOWN
   pinMode(WINCH_RELAIS_DOWN_1, OUTPUT);
   pinMode(WINCH_RELAIS_DOWN_2, OUTPUT);


   //== PIN PNEUMATIC ===
   pinMode(VACUUM_VALVE, OUTPUT);
   pinMode(PNEUMATIC_VALVE_OUT, OUTPUT);
   pinMode(PNEUMATIC_VALVE_IN, OUTPUT);
   pinMode(PNEUMATIC_SENSOR, INPUT);

}

//=========================================================================================
void loop(){
delay(500);
Serial.println("===============Enter Loop===============");
// delay(5000);
// bluetooth.run();
//drive.test();
Serial.println("===============Start===============");
drive.DriveFlo(100, RIGHT);
// pneumatic.test();
// winch.test();
delay(5000);
}
