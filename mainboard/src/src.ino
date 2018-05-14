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
#include "debug.h"

#define MYDEBUG

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
   pinMode(WINCH_RELAIS_ON, OUTPUT);
   pinMode(WINCH_RELAIS_DIR, OUTPUT);


   //==PIN PNEUMATIC ===
   pinMode(VACUUM_VALVE, OUTPUT);
   pinMode(PNEUMATIC_VALVE_OUT, OUTPUT);
   pinMode(PNEUMATIC_VALVE_IN, OUTPUT);
   pinMode(PNEUMATIC_SENSOR, INPUT);
}

//=========================================================================================
void loop(){
// delay(500);
// Serial.println("===============Enter Loop===============");

// delay(5000);
// bluetooth.run();
//drive.test();
// Serial.println("===============Start===============");
// drive.DriveFlo(100, driveRight);
// pneumatic.test();
// winch.test();

int stepdelay= 1000/100;

if(Serial.available()){                        //Send commands over serial to play
  switch(Serial.read()){
    case '1':
    Serial.println("DOWN");
    digitalWrite(DRIVER_1_DIR, HIGH);
    digitalWrite(DRIVER_2_DIR, HIGH);
    for (size_t i = 0; i <800; i++) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delay(stepdelay);
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delay(stepdelay);
    }
    Serial.println("DOWN-Finished");
    break;
    case '2':
    Serial.println("UP");
    digitalWrite(DRIVER_1_DIR, LOW);
    digitalWrite(DRIVER_2_DIR, LOW);
    for (size_t i = 0; i <800; i++) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delay(stepdelay);
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delay(stepdelay);
    }
    Serial.println("UP-Finished");
    break;
  }
}

// int direction = UP;
// digitalWrite(DRIVER_1_DIR, HIGH);
// digitalWrite(DRIVER_2_DIR, HIGH);
// direction=DOWN;
// Serial.println("DOWN");
//
// int stepdelay= 1000/50;
// for (size_t i = 0; i <400; i++) {
//   // Serial.println("Step: "+i);
//   digitalWrite(DRIVER_1_STEP, HIGH);
//   digitalWrite(DRIVER_2_STEP, HIGH);
//   delay(stepdelay);
//   digitalWrite(DRIVER_1_STEP, LOW);
//   digitalWrite(DRIVER_2_STEP, LOW);
//   delay(stepdelay);
// }
// delay(1000);
// digitalWrite(DRIVER_1_DIR, LOW);
// digitalWrite(DRIVER_2_DIR, LOW);
// direction=UP;
// Serial.println("UP");
// for (size_t i = 0; i <400; i++) {
//   // Serial.println("Step: "+i);
//   digitalWrite(DRIVER_1_STEP, HIGH);
//   digitalWrite(DRIVER_2_STEP, HIGH);
//   delay(stepdelay);
//   digitalWrite(DRIVER_1_STEP, LOW);
//   digitalWrite(DRIVER_2_STEP, LOW);
//   delay(stepdelay);
// }
// delay(3000);
}
