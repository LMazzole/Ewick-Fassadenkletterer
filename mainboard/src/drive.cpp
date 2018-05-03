// #include <Stepper.h>
#include "drive.h"
#include <math.h>

// Stepper Steppermotor_UPSTAIRS(TREIBER_1_PIN_1,TREIBER_1_PIN_2,TREIBER_1_PIN_3,TREIBER_1_PIN_4);

// Stepper Steppermotor_DONWSTAIRS(TREIBER_2_PIN_1,TREIBER_2_PIN_2,TREIBER_2_PIN_3,TREIBER_2_PIN_4);

Drive::Drive(){

}

void Drive::DriveFlo(double driveDistance, int direction){

  Serial.println("===============Start Drive===============");
  Serial.println("Durchmesser Zahnrad An:" + char(durchmesserZahnradAn));
  Serial.println("Durchmesser Zahnrad Ab:" + char(durchmesserZahnradAb));
  Serial.println("Durchmesser Reibrad:" + char(durchmesserReibrad));
  Serial.println("Durchmesser Zahnrad An:" + char(durchmesserZahnradAn));
  Serial.println("Reisegeschwindigkeit:" + char(maxSpeed));
  Serial.println("Zurückgelegter Weg pro Motorumdrehung:" + char(wegProMotorumdrehung));
  Serial.println("Delay in Milliseconds:" + char(neededDelay));

  delay(20000);

  digitalWrite(DRIVER_1_DIR, direction); //Geht das? Direction ist boolean und somit entweder 0 oder 1
  digitalWrite(DRIVER_2_DIR, direction); //Geht das? Direction ist boolean und somit entweder 0 oder 1

  int neededSteps = CalculationDistanceToSteps(driveDistance)-(2*157);

  AccelorationFlo();

  for(int i=0; i <= neededSteps;  i++ ){
    digitalWrite(DRIVER_1_STEP, HIGH);
    digitalWrite(DRIVER_2_STEP, HIGH);
    delay(neededDelay);
    digitalWrite(DRIVER_1_STEP, LOW);
    digitalWrite(DRIVER_2_STEP, LOW);
    delay(neededDelay);
  }

  SlowDownFlo();

}


void Drive::AccelorationFlo(){
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
    for(int i = 0; i == 156; i++) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
    }
}


void Drive::SlowDownFlo(){
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
    for(int i = 156; i == 0; i--) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delay(neededDelay+accelorationFaktor/neededDelay*(1-sin3[i]));
    }
}

int Drive::CalculationDistanceToSteps(double distance){
  Serial.println("===============Start CalculationDistancetoSteps===============");
  int steps = distance/wegProMotorumdrehung*stepsPerRevolution;
  Serial.println("Anzahl ausgerechnete Steps:" + char(steps));
  return steps;
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
