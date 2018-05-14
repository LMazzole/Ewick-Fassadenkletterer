
#include "winch.h"

Winch::Winch(){
}

void Winch::drive(int distanz, int direction){
    DEBUG_PRINTLN("Startposition in mm: " + String(position));
    distanz=checkPosition(distanz,direction);
    drivetime = convertDistanzTime(distanz);
  if (direction == DOWN && drivetime != 0){
      DEBUG_PRINTLN("Direction: DOWN");
      driveDown(true);
      delay(drivetime);
      driveDown(false);
  }
  else if (direction == UP && drivetime != 0){
      DEBUG_PRINTLN("Direction: UP");
      driveUp(true);
      delay(drivetime);
      driveUp(false);
  }
  DEBUG_PRINTLN("Endposition in mm: " + String(position));
  DEBUG_PRINTLN("");
}

double Winch::convertDistanzTime(int distanz){
  double dTime=0.0;
  dTime=round((abs(distanz)/ winchspeed)*1000); //dTime in ms
  DEBUG_PRINTLN("Drivetime in ms: " + String(dTime));
  return(dTime);
}

double Winch::checkPosition(int distanz, int direction){
  if ((position+distanz) > max_distanz_Winch && direction == DOWN){
      distanz = max_distanz_Winch-position;
    DEBUG_PRINTLN("Max. Distanz reached: " + String(max_distanz_Winch));
  }
  else if ((position-distanz) < min_distanz_Winch && direction== UP){
    distanz = position-min_distanz_Winch;
    DEBUG_PRINTLN("Min. Distanz reached: " + String(min_distanz_Winch));
  }

    DEBUG_PRINTLN("Distanz: " + String(distanz));
    position=position+(distanz*direction);
    return distanz;
}

void Winch::driveDown(bool status){
  if (status) {
    DEBUG_PRINTLN("driveDown()");
    if (!directionDown) {
      changeDirStatus();
    }
    if (!statusDriving) {
      changeDriveStatus();
    }
  }
}
void Winch::driveUp(bool status){
  if (status) {
    DEBUG_PRINTLN("driveUp()");
    if (directionDown) {
      changeDirStatus();
    }
    if (!statusDriving) {
      changeDriveStatus();
    }
  }
}

void Winch::changeDriveStatus(){
  DEBUG_PRINTLN("changeDriveStatus()");
  if (!statusDriving)
  statusDriving=true;
  else
  statusDriving=false;

  digitalWrite(WINCH_RELAIS_ON,HIGH);
  delay(20);
  digitalWrite(WINCH_RELAIS_ON,LOW);
}

void Winch::changeDirStatus(){
  DEBUG_PRINTLN("changeDirStatus()");
  if (!directionDown)
  statusDriving=true;
  else
  statusDriving=false;

  digitalWrite(WINCH_RELAIS_DIR,HIGH);
  delay(20);
  digitalWrite(WINCH_RELAIS_DIR,LOW);
  delay(50);
}

void Winch::test(){
  //Serial.println("");
  //Serial.println("===Start Winch Test===");
  //Serial.println("");
  Winch winch;
  //int delaytime = 200;

winch.drive(100, DOWN);
delay(2000);
winch.drive(100, UP);
  //winch.drive(1000,DOWN);
  //delay(delaytime);
  //winch.drive(500,DOWN);
  //delay(delaytime);
  //winch.drive(1000,DOWN);
  //delay(delaytime);
  //winch.drive(450,DOWN);
  //delay(delaytime);
  //winch.drive(500,DOWN);
  //delay(delaytime);
  //winch.drive(500,DOWN);
  //Serial.println("----------");
  //winch.drive(1000,UP);
  //delay(delaytime);
  //winch.drive(500,UP);
  //delay(delaytime);
  //winch.drive(1000,UP);
  //delay(delaytime);
  //winch.drive(450,UP);
  //delay(delaytime);
  //winch.drive(500,UP);
  //delay(delaytime);
  //winch.drive(500,UP);
  //delay(delaytime);
}
