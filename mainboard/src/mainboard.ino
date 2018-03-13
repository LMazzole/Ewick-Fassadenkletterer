//http://www.kramann.info/96_Arduino/24_OOP/index.php
//https://github.com/HSR-Stud/Willkommen

/* Includes */
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

#include "global.h"
#include "comm.h"
#include "drive.h"
#include "VirtuinoBluetooth.h"

// erstelle object antrieb
Drive drive;
Communicate comm;
VirtuinoBluetooth virtuino(Serial1);

//=============================================================================================================
void setup()
{
  // Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);


  virtuino.DEBUG=true;               // set this value TRUE to enable the serial monitor status
  Serial.begin(9600);                // Set serial monitor baud rate

  Serial1.begin(9600);               // Enable this line if you want to use hardware serial (Mega, DUE etc.)

  // Use virtuino.vPinMode instead default pinMode method for digital input or digital output pins.
   // pinMode(13,OUTPUT);
   virtuino.vPinMode(22,OUTPUT);

}

//=========================================================================================
void loop()
{

//drive.move(links,100, 30);

virtuino.run();
// drive.test();
// comm.test();


}
