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


void Drive::Driving(unsigned int driveDistance, int direction){
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
    DEBUG_PRINT("sizeof(sin3):");
    DEBUG_PRINT(sizeof(sin3));

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

  if(neededSteps < 2*sizeof(sin3)){
    DEBUG_PRINT("Die ausgewählte Distanz ist zu klein!");
    return;
  }
  else {

    neededSteps = neededSteps - 2*sizeof(sin3);

    Acceleration();

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

   SlowDown();

   if(direction == 1){
      actualHorizontalPosition = actualHorizontalPosition + driveDistance;
   }
   else if(direction == 0){
     actualHorizontalPosition = actualHorizontalPosition - driveDistance;
   }

   return;

  }


}

void Drive::Acceleration(){
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
  DEBUG_PRINTLN("==Anfahren Start==");

  unsigned int delay;

   for(unsigned int i = 0; i < sizeof(sin3); i++) {
    delay = neededDelay+accelorationFaktor/(neededDelay/2)*(1-sin3[i]);
    DEBUG_PRINT("Delay = ");
    DEBUG_PRINTLN(delay);
    for (size_t n = 0; n < 23; n++) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delayMicroseconds(delay);
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delayMicroseconds(delay);
    }
 }

  DEBUG_PRINTLN("==Anfahren Ende==");
}


void Drive::SlowDown(){
  DEBUG_PRINTLN("==Drive::SlowDown()");
  // delay(CalculationDelay+gewichtung/CalculationDelay*(1-sin3[i]))
  DEBUG_PRINTLN("==================Abbremsen Start===========================");

  unsigned int delay;

   for(unsigned int i = sizeof(sin3)-1; i >= 0; i--) {
    delay = neededDelay+accelorationFaktor/(neededDelay/2)*(1-sin3[i]);
    DEBUG_PRINT("Delay = ");
    DEBUG_PRINTLN(delay);
    for (size_t n = 0; n < 23; n++) {
      digitalWrite(DRIVER_1_STEP, HIGH);
      digitalWrite(DRIVER_2_STEP, HIGH);
      delayMicroseconds(delay);
      digitalWrite(DRIVER_1_STEP, LOW);
      digitalWrite(DRIVER_2_STEP, LOW);
      delayMicroseconds(delay);
    }
 }

  DEBUG_PRINTLN("==================Abbremsen Ende===========================");
}

long Drive::CalculationDistanceToSteps(unsigned int distance){
  DEBUG_PRINTLN("==Drive::CalculationDistanceToSteps(distance)");
  DEBUG_PRINTLN("===============Start Berechung Steps===============");
  unsigned long steps = distance/wegProMotorumdrehung*stepsPerRevolution;
  return steps;
  DEBUG_PRINTLN("===============Start Berechung Steps===============");
}
