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
  bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,winch.max_distanz_Winch/10);
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

//int postionTablet = winch.max_distanz_Winch-winch.position
// Automatisches Fahren
if (bluetooth.vDigitalMemoryRead(AUTOMATIC_DRIVING) == 1){
  // Zuerst auf Position 0 zurückfahren -> falls Manual fahren implementiert
  DEBUG_PRINTLN("ANFANGSPOSITION ANFAHREN");
      DEBUG_PRINT("Drive Up: ");
      DEBUG_PRINTLN(winch.position);
      winch.drive(winch.position,UP);
      DEBUG_PRINT("Drive left: ");
      DEBUG_PRINTLN(drive.actualHorizontalPosition);
      drive.Driving(drive.actualHorizontalPosition, LEFT);

// Position am Marktplatz ANFAHREN
    DEBUG_PRINTLN("Drive RIGHT 500");
    drive.Driving(550, RIGHT);
    DEBUG_PRINTLN("Drive DOWN 500");
    winch.drive(400, DOWN);


// Position an der Wand anfahren
  // DEBUG_PRINTLN("POSITION 1 ANFAHREN");
  //     DEBUG_PRINTLN("Drive RIGHT 500");
  //     drive.Driving(550, RIGHT);
  //     DEBUG_PRINTLN("Drive DOWN 500");
  //     winch.drive(600, DOWN);
  //     DEBUG_PRINTLN("Cylinder ausfahren");
  //     pneumatic.cylinderout();
  //     winch.drive(100,DOWN);
  //     bluetooth.vDelay(10000);
  //     DEBUG_PRINTLN("Cylinder einfahren");
  //     winch.drive(100,UP);
  //     pneumatic.cylinderin();
  //
  // DEBUG_PRINTLN("POSITION 2 ANFAHREN");
  //     DEBUG_PRINTLN("Drive DOWN 500");
  //     winch.drive(1900, DOWN);
  //     DEBUG_PRINTLN("Drive RIGHT 500");
  //     drive.Driving(1400, RIGHT);
  //     DEBUG_PRINTLN("Cylinder ausfahren");
  //     pneumatic.cylinderout();
  //     winch.drive(100,DOWN);
  //     bluetooth.vDelay(10000);
  //     DEBUG_PRINTLN("Cylinder einfahren");
  //     winch.drive(100,UP);
  //     pneumatic.cylinderin();

  DEBUG_PRINTLN("ANFANGSPOSITION ANFAHREN");
          DEBUG_PRINT("Drive Up: ");
          DEBUG_PRINTLN(winch.position);
          winch.drive(winch.position,UP);
          DEBUG_PRINT("Drive left: ");
          DEBUG_PRINTLN(drive.actualHorizontalPosition);
          drive.Driving(drive.actualHorizontalPosition, LEFT);



  bluetooth.vDigitalMemoryWrite(AUTOMATIC_DRIVING, 0);
  bluetooth.vDigitalMemoryWrite(POSITION_HORIZONTAL, drive.actualHorizontalPosition/10);
  bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,(winch.max_distanz_Winch-winch.position)/10);
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

   DEBUG_PRINT("Aktuelle vertikale Position unten: ");
   DEBUG_PRINTLN(winch.max_distanz_Winch-winch.position);

   DEBUG_PRINT("Vertikal Value von unten: ");
   DEBUG_PRINTLN(bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10);

   if( (winch.max_distanz_Winch-winch.position) > (bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10) ){
     DEBUG_PRINTLN("Driving DOWN");
     DEBUG_PRINTLN(winch.max_distanz_Winch-winch.position-bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10);
     winch.drive(winch.max_distanz_Winch-winch.position-bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10,DOWN);
   } else {
     DEBUG_PRINTLN("Driving UP");
     DEBUG_PRINTLN(bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10-(winch.max_distanz_Winch-winch.position));
     winch.drive(bluetooth.vDigitalMemoryRead(VALUE_VERTIKAL)*10-(winch.max_distanz_Winch-winch.position),UP);
   }

   bluetooth.vDigitalMemoryWrite(DRIVE_MANUAL, 0);
   bluetooth.vDigitalMemoryWrite(POSITION_HORIZONTAL, drive.actualHorizontalPosition/10);
   bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,(winch.max_distanz_Winch-winch.position)/10);
   bluetooth.vDelay(500);
 }

if (bluetooth.vDigitalMemoryRead(ZYLINDER_MANUAL_IN) == 1){
  winch.drive(100,UP);
  pneumatic.cylinderin();
  bluetooth.vDigitalMemoryWrite(ZYLINDER_MANUAL_IN, 0);
  bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,(winch.max_distanz_Winch-winch.position)/10);
}

if (bluetooth.vDigitalMemoryRead(ZYLINDER_MANUAL_OUT) == 1){
  pneumatic.cylinderout();
  winch.drive(60,DOWN);
  bluetooth.vDigitalMemoryWrite(ZYLINDER_MANUAL_OUT, 0);
  bluetooth.vDigitalMemoryWrite(POSITION_VERTIKAL,(winch.max_distanz_Winch-winch.position)/10);
}

// Serial Eingabe
if(Serial.available()){                        //Send commands over serial to play
  switch(Serial.read()){
    case '0':
      DEBUG_PRINTLN("Case '0' Info");
      DEBUG_PRINTLN("Case '1' Drive LEFT 500mm");
      DEBUG_PRINTLN("Case '2' Drive RIGHT 500mm");
      DEBUG_PRINTLN("Case '3' Drive DOWN 500mm");
      DEBUG_PRINTLN("Case '4' Drive UP 500mm");
      DEBUG_PRINTLN("Case '5' Cylinder Out");
      DEBUG_PRINTLN("Case '6' Cylinder In");
      DEBUG_PRINTLN("Case '7' Vaccum Status");
      break;
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
    DEBUG_PRINTLN("Case '7' Vacuumstatus");
    for (size_t i = 0; i < 50; i++) {
      DEBUG_PRINT("Vacuumstatus: ");
      DEBUG_PRINTLN(analogRead(PNEUMATIC_SENSOR));
      delay(300);
    }
      DEBUG_PRINTLN("Case 7: finished");
      DEBUG_PRINTLN("");
    break;

    case'8':
    DEBUG_PRINTLN("Case '8' ");
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
