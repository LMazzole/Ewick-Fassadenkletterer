//http://www.kramann.info/96_Arduino/24_OOP/index.php
//https://github.com/HSR-Stud/Willkommen

/* Includes */
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

#include "global.h"
#include "drive.h"



// erstelle object antrieb
Drive drive;


//=============================================================================================================
void setup()
{
  Serial.begin(115200);

  pinMode(ledOpen, OUTPUT);
  pinMode(ledClose, OUTPUT);
  pinMode(doorPin, INPUT);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  pinMode(button8, INPUT);
  pinMode(button9, INPUT);
  pinMode(buttonStar, INPUT);
  pinMode(buttonHash, INPUT);
  digitalWrite(ledOpen, LOW);
  digitalWrite(ledClose, LOW);
  analogWrite(doorPin, 0);
  digitalWrite(button0, HIGH);
  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);
  digitalWrite(button4, HIGH);
  digitalWrite(button5, HIGH);
  digitalWrite(button6, HIGH);
  digitalWrite(button7, HIGH);
  digitalWrite(button8, HIGH);
  digitalWrite(button9, HIGH);
  digitalWrite(buttonStar, HIGH);
  digitalWrite(buttonHash, HIGH);

}

//=========================================================================================
void loop()
{

drive.move(links,100, 30);

  
}
  
