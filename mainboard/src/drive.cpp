#include <Stepper.h>
#include "drive.h"

Stepper Steppermotor_UPSTAIRS(TREIBER_1_PIN_1,TREIBER_1_PIN_2,TREIBER_1_PIN_3,TREIBER_1_PIN_4);

Stepper Steppermotor_DONWSTAIRS(TREIBER_2_PIN_1,TREIBER_2_PIN_2,TREIBER_2_PIN_3,TREIBER_2_PIN_4);

Drive::Drive(){}

void Steppermotor_UPSTAIRS::Step(int steps, int direction,int motorspeed)
{
          if (direction == LEFT){
          motor.setSpeed(motorspeed);
          motor.step(steps);
          }
          else{
          motor.setSpeed(motorspeed);
          motor.step(-1*steps);
          }
}

void Steppermotor_DOWNSTAIRS::Step(int steps, int direction,int motorspeed)
{
          if (direction == LEFT){
          motor.setSpeed(motorspeed);
          motor.step(steps);
          }
          else{
          motor.setSpeed(motorspeed);
          motor.step(-1*steps);
          }
}

void Drive::test(){
Serial.println("");
  Serial.println("===Start Drive Test===");
  Serial.println("");
  
  void Steppermotor_UPSTAIRS.Step(20,1,20);
  delay(20000);
  void Steppermotor_DOWNSTAIRS.Step(20,1,20);
  delay(20000);
}
