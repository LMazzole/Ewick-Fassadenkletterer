// #include <Stepper.h>
#include "drive.h"
#include <math.h>

// Stepper Steppermotor_UPSTAIRS(TREIBER_1_PIN_1,TREIBER_1_PIN_2,TREIBER_1_PIN_3,TREIBER_1_PIN_4);

// Stepper Steppermotor_DONWSTAIRS(TREIBER_2_PIN_1,TREIBER_2_PIN_2,TREIBER_2_PIN_3,TREIBER_2_PIN_4);

Drive::Drive(){

}

void Drive::DriveFlo(double driveDistance, int direction){
  Serial.println("===============Start Drive===============");
  if (direction == 1){
    digitalWrite(DRIVER_1_DIR, HIGH);
    digitalWrite(DRIVER_2_DIR, HIGH);
  }
  else {
    digitalWrite(DRIVER_1_DIR, LOW);
    digitalWrite(DRIVER_2_DIR, LOW);
  }

  for(int i=0; i <= CalculationDistanceToSteps(driveDistance); i++ ){

    digitalWrite(DRIVER_1_STEP, HIGH);
    digitalWrite(DRIVER_2_STEP, HIGH);
    delay(10);
    digitalWrite(DRIVER_1_STEP, LOW);
    digitalWrite(DRIVER_2_STEP, LOW);
    delay(10);
  }


}

void Drive::AccelorationFlo(){
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
    for(int i = 157; sin3[i] >= CalculationDelay(); i--) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delay(sin3[i]*100000);
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delay(sin3[i]*100000);
    }

}

int Drive::CalculationDistanceToSteps(double distance){
  Serial.println("===============Start CalculationDistancetoSteps===============");
  int steps;
  double verhaeltnisZahnrad = durchmesserZahnradAn/durchmesserZahnradAb;
  double umfangReibrad = 2*M_PI*durchmesserReibrad;
  double wegProMotorumdrehung = umfangReibrad*verhaeltnisZahnrad;

  steps = distance/wegProMotorumdrehung*stepsPerRevolution;

  return steps;
}

double Drive::CalculationDelay(){
  double neededDelay;
Serial.println("===============Start CalculationDelay===============");
  double verhaeltnisZahnrad = durchmesserZahnradAn/durchmesserZahnradAb;
  double umfangReibrad = 2*M_PI*durchmesserReibrad;
  double wegProMotorumdrehung = umfangReibrad*verhaeltnisZahnrad;
  double wegProMotorstep = wegProMotorumdrehung/stepsPerRevolution;

  double stepsPerSeconds = wegProMotorstep/(maxSpeed*1000);
  Serial.println("===============Start Variable stepsPerSeconds===============");
  Serial.println(stepsPerSeconds);
  neededDelay = 1/stepsPerSeconds/2;
  Serial.println("===============Start Variable neededDelay===============");
  Serial.println(neededDelay);

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
