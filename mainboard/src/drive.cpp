// #include <Stepper.h>
#include "drive.h"
#include <math.h>

// Stepper Steppermotor_UPSTAIRS(TREIBER_1_PIN_1,TREIBER_1_PIN_2,TREIBER_1_PIN_3,TREIBER_1_PIN_4);

// Stepper Steppermotor_DONWSTAIRS(TREIBER_2_PIN_1,TREIBER_2_PIN_2,TREIBER_2_PIN_3,TREIBER_2_PIN_4);

Drive::Drive(){

}

void Drive::printDouble(double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print(int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC);
}


void Drive::Driving(double driveDistance, int direction){
    DEBUG_PRINTLN("==Drive::Driving(driveDistance,direction)");
    DEBUG_PRINT("driveDistance: ");
    DEBUG_PRINTLN(driveDistance);
    DEBUG_PRINT("direction (0 LEFT, 1 RIGHT): ");
    DEBUG_PRINTLN(direction);
    DEBUG_PRINT("Durchmesser Zahnrad An: ");
    printDouble(durchmesserZahnradAn,10);
    DEBUG_PRINT("Durchmesser Zahnrad Ab: ");
    printDouble(durchmesserZahnradAb,10);
    DEBUG_PRINT("Durchmesser Reibrad: ");
    printDouble(durchmesserReibrad,10);
    DEBUG_PRINT("Reisegeschwindigkeit: ");
    printDouble(maxSpeed,10);
    DEBUG_PRINT("Zurückgelegter Weg pro Motorumdrehung: ");
    printDouble(wegProMotorumdrehung,10);
    DEBUG_PRINT("Delay in Microseconds:");
    printDouble(neededDelay,10);

  // delay(500);

  if (direction == 1){
    digitalWrite(DRIVER_1_DIR, HIGH);
    digitalWrite(DRIVER_2_DIR, HIGH);
  }
  else if (direction == 0){
    digitalWrite(DRIVER_1_DIR, LOW);
    digitalWrite(DRIVER_2_DIR, LOW);
  }
  unsigned long neededSteps = CalculationDistanceToSteps(driveDistance);
  DEBUG_PRINT("Benötigte Steps: ");
  printDouble(neededSteps,10);

  // Acceleration()

  DEBUG_PRINTLN("==Fahren Start==");
  printDouble(neededDelay,10);
  for(unsigned long i=0; i <= neededSteps;  i++){
    //Serial.println("Delay = ");
    //printDouble(neededDelay,10);
    digitalWrite(DRIVER_1_STEP, HIGH);
    digitalWrite(DRIVER_2_STEP, HIGH);
    delayMicroseconds(neededDelay);
    digitalWrite(DRIVER_1_STEP, LOW);
    digitalWrite(DRIVER_2_STEP, LOW);
    delayMicroseconds(neededDelay);
  }
  DEBUG_PRINTLN("==Fahren Ende==");

  //SlowDown();

}


void Drive::Acceleration(){
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
  DEBUG_PRINTLN("==Anfahren Start==");

   for(int i = 0; i <= 156; i++) {
     Serial.println("Delay = ");
     printDouble(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]),10);

     digitalWrite(DRIVER_1_STEP, HIGH);
     digitalWrite(DRIVER_2_STEP, HIGH);
     delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
     digitalWrite(DRIVER_1_STEP, LOW);
     digitalWrite(DRIVER_2_STEP, LOW);
     delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
    }

  DEBUG_PRINTLN("==Anfahren Ende==");
}


void Drive::SlowDown(){
  DEBUG_PRINTLN("==Drive::SlowDown()");
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
  DEBUG_PRINTLN("==================Abbremsen Start===========================");
    for(int i = 156; i >= 0; i--) {
      DEBUG_PRINT("Delay = ");
      printDouble(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]),10);

      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
    }
    DEBUG_PRINTLN("==================Abbremsen Ende===========================");
}

long Drive::CalculationDistanceToSteps(double distance){
  DEBUG_PRINTLN("==Drive::CalculationDistanceToSteps(distance)");
  DEBUG_PRINTLN("===============Start Berechung Steps===============");
  unsigned long steps = distance/wegProMotorumdrehung*stepsPerRevolution;
  return steps;
  DEBUG_PRINTLN("===============Start Berechung Steps===============");
}

// void Steppermotor_UPSTAIRS::Step(int steps, int direction,int motorspeed)
// {
//           if (direction == LEFT){
//           motor.setSpeed(motorspeed);
//           motor.step(steps);
//           }
//           else{
//           motor.setSpeed(motorspeed);
//           motor.step(-1*steps);
//           }
// }
//
// void Steppermotor_DOWNSTAIRS::Step(int steps, int direction,int motorspeed)
// {
//           if (direction == LEFT){
//           motor.setSpeed(motorspeed);
//           motor.step(steps);
//           }
//           else{
//           motor.setSpeed(motorspeed);
//           motor.step(-1*steps);
//           }
// }

void Drive::test(){
DEBUG_PRINTLN("");
  DEBUG_PRINTLN("===Start Drive Test===");

  while (digitalRead(50)==LOW) {
  }

digitalWrite(DRIVER_1_DIR,HIGH);
for (size_t i = 0; i < 10000; i=i+50) {
  Serial.println("PWM: " + String(10000-i));
   analogWrite(DRIVER_1_STEP,255);
   delayMicroseconds((10000.0-i));
   analogWrite(DRIVER_1_STEP,0);
   delayMicroseconds((10000.0-i));
}
analogWrite(DRIVER_1_STEP,126);
delay(10000);
analogWrite(DRIVER_1_STEP,0);
  // Serial.println(" Drive High, dir high");
  // digitalWrite(DRIVER_1_DIR,HIGH);
  // for (size_t i = 0; i < 256; i=i+10) {
  //   analogWrite(DRIVER_1_STEP,i);
  //   delay(200);
  //   Serial.println("PWM: " + String(i));
  // }
  // Serial.println("======");
  // delay(2000);
  // for (size_t i = 0; i <256; i=i+10) {
  //   analogWrite(DRIVER_1_STEP,(255-i));
  //   delay(200);
  //   Serial.println("PWM: " + String(255-i));
  // }
  // analogWrite(DRIVER_1_STEP,0);
  // Serial.println("Change Dir");
  // delay(2000);
  // Serial.println(" Drive High, dir low");
  // digitalWrite(DRIVER_1_DIR,LOW);
  // for (size_t i = 0; i < 256; i=i+10) {
  //   analogWrite(DRIVER_1_STEP,i);
  //   delay(200);
  //   Serial.println("PWM: " + String(i));
  // }
  // Serial.println("======");
  // delay(2000);
  // for (size_t i = 0; i <266; i=i+10) {
  //   analogWrite(DRIVER_1_STEP,(255-i));
  //   delay(200);
  //   Serial.println("PWM: " + String(255-i));
  // }
  // analogWrite(DRIVER_1_STEP,0);

  // void Steppermotor_UPSTAIRS.Step(20,1,20);
  // delay(20000);
  // void Steppermotor_DOWNSTAIRS.Step(20,1,20);
  // delay(20000);
}
