//http://www.kramann.info/96_Arduino/24_OOP/index.php
//https://github.com/HSR-Stud/Willkommen

#define MYDEBUG


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
#include "debug.h"
#include "VirtuinoBluetooth.h"

// Bluetooth Modul --> Hardware Serial einstellen
//
//#include <SoftwareSerial.h>                         //  Disable this line if you want to use hardware serial
//SoftwareSerial bluetoothSerial = SoftwareSerial(2,3);   // arduino TX pin=2  arduino RX pin=3    connect the arduino RX pin to bluetooth module TX pin   -  connect the arduino TX pin to bluetooth module RX pin.  Disable this line if you want to use hardware serial
//VirtuinoBluetooth virtuino(bluetoothSerial, 9600);       // Set SoftwareSerial baud rate.  -  Disable this line if you want to use hardware serial

Drive drive;
Communicate bluetooth(Serial3,9600);
//VirtuinoBluetooth virtuino(9600);
Winch winch;
Pneumatic pneumatic;

//=============================================================================================================
void setup(){

  // Overview over the PIN-defines are in global.h

  Serial.begin(9600);                // Set serial monitor baud rate
  //bluetoothSerial.begin(9600);
  bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,300);
  Serial.println("Initialise Arduino");


  //bluetooth.DEBUG=false;               // set this value TRUE to enable the serial monitor status


  // Use virtuino.vPinMode instead default pinMode method for digital input or digital output pins.
   //pinMode(pinalias, OUTPUT);
   //pinMode(LED_BUILTIN, OUTPUT);
   //bluetooth.vPinMode(testLED,OUTPUT);

   //== PIN STEPPER====
   //==UPSTAIRS
   pinMode(DRIVER_1_DIR, OUTPUT);
   pinMode(DRIVER_1_STEP, OUTPUT);
   pinMode(DRIVER_2_DIR, OUTPUT);
   pinMode(DRIVER_2_STEP, OUTPUT);

   //== PIN WINCH====
   //==UP
   pinMode(WINCH_RELAIS_ON_POS, OUTPUT);
   pinMode(WINCH_RELAIS_ON_NEG, OUTPUT);
   pinMode(WINCH_RELAIS_DIR_POS, OUTPUT);
   pinMode(WINCH_RELAIS_DIR_NEG, OUTPUT);


   //==PIN PNEUMATIC ===
   pinMode(VACUUM_VALVE, OUTPUT);
   pinMode(PNEUMATIC_VALVE_OUT, OUTPUT);
   pinMode(PNEUMATIC_VALVE_IN, OUTPUT);
   pinMode(PNEUMATIC_SENSOR, INPUT);

   winch.initialise();

   DEBUG_PRINTLN("Case '1' Drive LEFT 500mm");
   DEBUG_PRINTLN("Case '2' Drive RIGHT 500mm");
   DEBUG_PRINTLN("Case '3' Drive DOWN 500mm");
   DEBUG_PRINTLN("Case '4' Drive UP 500mm");
   DEBUG_PRINTLN("Case '5' Cylinder Out");
   DEBUG_PRINTLN("Case '6' Cylinder In");
   DEBUG_PRINTLN("Case '7' Vaccum Status");
   DEBUG_PRINTLN("=========================");
}

//=========================================================================================
void loop(){
// Bluetooth Modul
bluetooth.run();

// Automatisches Fahren
if (bluetooth.vDigitalMemoryRead(AUTOMATIC_DRIVING) == 1){
  // Zuerst auf Position 0 zurückfahren -> falls Manual fahren implementiert
  DEBUG_PRINTLN("Anfangsposition fahren");
  DEBUG_PRINT("Drive Up: ");
  DEBUG_PRINTLN(winch.position);
  winch.drive(winch.position,UP);
  DEBUG_PRINT("Drive left: ");
  DEBUG_PRINTLN(drive.actualHorizontalPosition);
  drive.Driving(drive.actualHorizontalPosition, LEFT);

  DEBUG_PRINTLN("Drive RIGHT 500");
  drive.Driving(600, RIGHT);
  DEBUG_PRINTLN("Drive DOWN 500");
  winch.drive(600, DOWN);
  DEBUG_PRINTLN("Cylinder ausfahren");
  pneumatic.cylinderout();

  bluetooth.vDelay(5000);

  DEBUG_PRINTLN("Cylinder einfahren");
  pneumatic.cylinderin();
  DEBUG_PRINTLN("Drive UP 500");
  winch.drive(600, UP);
  DEBUG_PRINTLN("Drive LEFT 500");
  drive.Driving(600, LEFT);



  bluetooth.vDigitalMemoryWrite(AUTOMATIC_DRIVING, 0);
  bluetooth.vDigitalMemoryWrite(POSITION_HORIZONTAL, 0);
  bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL, 300);
  bluetooth.vDelay(5000);
}


 // Manuelle ansteuerung Motor
 if (bluetooth.vDigitalMemoryRead(DRIVE_MANUAL) == 1){
   DEBUG_PRINTLN("Akutelle horizontale Position ");
   DEBUG_PRINTLN(drive.actualHorizontalPosition);

   DEBUG_PRINTLN("Horizontal Value: ");
   DEBUG_PRINTLN(bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10);

   if(bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10 < drive.actualHorizontalPosition){
     DEBUG_PRINTLN("Driving LEFT");
     DEBUG_PRINTLN(drive.actualHorizontalPosition-bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10);
     drive.Driving(drive.actualHorizontalPosition-bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10, LEFT);
   } else if (bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10 > drive.actualHorizontalPosition)
   {
     DEBUG_PRINTLN("Driving RIGHT");
     DEBUG_PRINTLN(bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10-drive.actualHorizontalPosition);
     drive.Driving(bluetooth.vDigitalMemoryRead(VALUE_HORIZONTAL)*10-drive.actualHorizontalPosition, RIGHT);
   }

   Serial.print("Aktuelle vertikale Position unten: ");
   Serial.println(3000-winch.position);

   Serial.print("Vertikal Value von unten: ");
   Serial.println(bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10);

   if(3000-winch.position > bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10){
     DEBUG_PRINTLN("Driving DOWN");
     DEBUG_PRINTLN(3000-winch.position-bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10);
     winch.drive(3000-winch.position-bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10,DOWN);
   } else if (3000-winch.position < bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10){
     DEBUG_PRINTLN("Driving UP");
     DEBUG_PRINTLN(bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10-(3000-winch.position));
     winch.drive(bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10-(3000-winch.position),DOWN);
   }

   bluetooth.vDigitalMemoryWrite(DRIVE_MANUAL, 0);
   bluetooth.vDigitalMemoryWrite(POSITION_HORIZONTAL, drive.actualHorizontalPosition/10);
   bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,(3000-winch.position)/10);
   bluetooth.vDelay(500);
 }

if (bluetooth.vDigitalMemoryRead(ZYLINDER_MANUAL_IN) == 1){
  pneumatic.cylinderin();
  bluetooth.vDigitalMemoryWrite(ZYLINDER_MANUAL_IN, 0);
}

if (bluetooth.vDigitalMemoryRead(ZYLINDER_MANUAL_OUT) == 1){
  pneumatic.cylinderout();
  bluetooth.vDigitalMemoryWrite(ZYLINDER_MANUAL_OUT, 0);
}

// Serial Eingabe
if(Serial.available()){                        //Send commands over serial to play
  switch(Serial.read()){
    case '1':
    DEBUG_PRINTLN("Case '1' Drive LEFT 500");
    drive.Driving(400, LEFT);

      DEBUG_PRINTLN("Case 1: finished");
      DEBUG_PRINTLN("");
      break;
    case '2':
      DEBUG_PRINTLN("Case '2' Drive RIGHT 500");
      drive.Driving(500, RIGHT);
      DEBUG_PRINTLN("Case 2: finished");
      DEBUG_PRINTLN("");
      break;
    case '3':
      DEBUG_PRINTLN("Case '3' Drive DOWN 500");
      winch.drive(500,DOWN);
      DEBUG_PRINTLN("Case 3: finished");
      DEBUG_PRINTLN("");
    break;

    case'4':
      DEBUG_PRINTLN("Case '4' Drive UP 500");
      winch.drive(500,UP);
      DEBUG_PRINTLN("Case 4: finished");
      // DEBUG_PRINTLN("");
    break;

    case'5':
      DEBUG_PRINTLN("Case '5' Cylinder Out");
      pneumatic.cylinderout();
      DEBUG_PRINTLN("Case 5: finished");
      DEBUG_PRINTLN("");
    break;

    case'6':
      DEBUG_PRINTLN("Case '6'Cylinder In");
      pneumatic.cylinderin();
      DEBUG_PRINTLN("Case 6: finished");
      DEBUG_PRINTLN("");
    break;


    case'7':
    for (size_t i = 0; i < 50; i++) {
      DEBUG_PRINT("Vacuumstatus: ");
      DEBUG_PRINTLN(analogRead(PNEUMATIC_SENSOR));
      delay(300);
    }
      DEBUG_PRINTLN("Case 7: finished");
      DEBUG_PRINTLN("");
    break;

    case'8':
    int anzahl = 88/88*800;
    DEBUG_PRINTLN(anzahl);
    for (int i = 0; i <= anzahl; i++) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delayMicroseconds(275);
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delayMicroseconds(275);
    }
    break;
    DEBUG_PRINTLN("Case 8: finished");
    DEBUG_PRINTLN("");
  }
}





}
