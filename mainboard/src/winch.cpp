
#include "winch.h"

Winch::Winch(){
}

void Winch::initialise(){
  DEBUG_PRINTLN("Winch::Initialise()");
  DEBUG_PRINTLN("WINCH OFF");
  DEBUG_PRINTLN("Direction DOWN");
  //Relais off
  digitalWrite(WINCH_RELAIS_ON_POS, LOW);
  digitalWrite(WINCH_RELAIS_ON_NEG, HIGH);
  delay(50);
  digitalWrite(WINCH_RELAIS_ON_NEG, LOW);
  //Direction Down
  digitalWrite(WINCH_RELAIS_DIR_POS, HIGH);
  digitalWrite(WINCH_RELAIS_DIR_NEG, LOW);
  delay(50);
  digitalWrite(WINCH_RELAIS_DIR_POS, LOW);
}

void Winch::drive(int distanz, int direction){
    DEBUG_PRINTLN("Startposition in mm: " + String(position));
    distanz=checkPosition(distanz,direction);
    drivetime = convertDistanzTime(distanz);
    DEBUG_PRINT("Direction 1=UP,0=Down : ");
    DEBUG_PRINTLN(direction);
  if (drivetime != 0){
      driveDirection(direction);
      delay(drivetime);
      drivePowerOn(false);
  }
  DEBUG_PRINT("Endposition in mm: ");
  DEBUG_PRINTLN(position);
}

double Winch::convertDistanzTime(int distanz){
  double dTime=0.0;
  dTime=round((abs(distanz)/ winchspeed)*1000); //dTime in ms
  DEBUG_PRINTLN("Drivetime in ms: " + String(dTime));
  return(dTime);
}

double Winch::checkPosition(int distanz, int direction){
  DEBUG_PRINTLN("Winch::checkPosition(distanz,direction)");
  if ((position+distanz) > max_distanz_Winch && direction == DOWN){
      distanz = max_distanz_Winch-position;
    DEBUG_PRINTLN("Max. Distanz reached: " + String(max_distanz_Winch));
  }
  else if ((position-distanz) < min_distanz_Winch && direction== UP){
    distanz = position-min_distanz_Winch;
    DEBUG_PRINTLN("Min. Distanz reached: " + String(min_distanz_Winch));
  }

    DEBUG_PRINTLN("Distanz: " + String(distanz));
    if (direction==DOWN) {
      position=position+distanz;
    } else {
      position=position-distanz;
    }
    // position=position+(distanz*direction);
    return distanz;
}

void Winch::drivePowerOn(bool status){
  if (status) {
    DEBUG_PRINT("drivePoweron(): ");
    DEBUG_PRINTLN(status);
    digitalWrite(WINCH_RELAIS_ON_POS, HIGH);
    digitalWrite(WINCH_RELAIS_ON_NEG, LOW);
    delay(50);
    digitalWrite(WINCH_RELAIS_ON_POS, LOW);
  }
  else{
    DEBUG_PRINT("drivePoweron(): ");
    DEBUG_PRINTLN(status);
    digitalWrite(WINCH_RELAIS_ON_POS, LOW);
    digitalWrite(WINCH_RELAIS_ON_NEG, HIGH);
    delay(50);
    digitalWrite(WINCH_RELAIS_ON_NEG, LOW);
  }
}

void Winch::driveDirection(int direction){
  DEBUG_PRINT("driveDirection(): ");
  DEBUG_PRINTLN(direction);
  drivePowerOn(false);
  delay(500);
  if (direction == DOWN) {
    digitalWrite(WINCH_RELAIS_DIR_POS, HIGH);
    digitalWrite(WINCH_RELAIS_DIR_NEG, LOW);
    delay(50);
    digitalWrite(WINCH_RELAIS_DIR_POS, LOW);
  } else if (direction == UP) {
    digitalWrite(WINCH_RELAIS_DIR_NEG, HIGH);
    digitalWrite(WINCH_RELAIS_DIR_POS, LOW);
    delay(50);
    digitalWrite(WINCH_RELAIS_DIR_NEG, LOW);
  }
  drivePowerOn(true);
}
