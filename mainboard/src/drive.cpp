// #include <Stepper.h>
#include "drive.h"

// Stepper Steppermotor_UPSTAIRS(TREIBER_1_PIN_1,TREIBER_1_PIN_2,TREIBER_1_PIN_3,TREIBER_1_PIN_4);

// Stepper Steppermotor_DONWSTAIRS(TREIBER_2_PIN_1,TREIBER_2_PIN_2,TREIBER_2_PIN_3,TREIBER_2_PIN_4);

Drive::Drive(){

}

void Drive::DriveFlo(double driveDistance){

  for(int i=0; i <= CalculationDistanceToSteps(driveDistance); i++ ){
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    delay(CalculationDelay());
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    delay(CalculationDelay());
  }

}

void Drive::AccelorationFlo(){
  
}

int Drive::CalculationDistanceToSteps(double distance){
  int steps;
  double verhaeltnisZahnrad = durchmesserZahnradAn/durchmesserZahnradAb;
  double umfangReibrad = 2*Pi()*durchmesserReibrad;
  double wegProMotorumdrehung = umfangReibrad*verhaeltnisZahnrad;

  steps = distance/wegProMotorumdrehung*stepsPerRevolution;

  return steps;
}

int Drive::CalculationDelay(){
  int neededDelay;

  double verhaeltnisZahnrad = durchmesserZahnradAn/durchmesserZahnradAb;
  double umfangReibrad = 2*Pi()*durchmesserReibrad;
  double wegProMotorumdrehung = umfangReibrad*verhaeltnisZahnrad;
  double wegProMotorstep = wegProMotorumdrehung/stepsPerRevolution;

  double stepsPerSeconds = wegProMotorstep/(speed*1000);
  neededDelay = 1000000/stepsPerSeconds/2;

  return neededDelay;
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
Serial.println("");
  Serial.println("===Start Drive Test===");

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
