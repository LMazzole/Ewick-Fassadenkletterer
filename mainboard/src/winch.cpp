
#include "winch.h"

Winch::Winch(){

}

void Winch::drive(int distanz, int direction){
    Serial.println("Startposition in mm: " + String(position));
    distanz=checkPosition(distanz,direction);
    drivetime = convertDistanzTime(distanz);
  if (direction == DOWN){
      Serial.println("Direction: DOWN");
      Winch::startDriving(true);
      Winch::directionDriving(DOWN);
      delay(drivetime);
      startDriving(false);
  }
  else{
      Serial.println("Direction: UP");
      Winch::startDriving(true);
      Winch::directionDriving(UP);
      delay(drivetime);
      startDriving(false);
  }

  Serial.println("Endposition in mm: " + String(position));
  Serial.println("");
}

double Winch::convertDistanzTime(int distanz){
  double dTime=0.0;
  // Serial.println("DB----distanz: " + String(distanz));
  // Serial.println("DB-winchspeed: " + String(winchspeed));
  dTime=round((abs(distanz)/ winchspeed)*1000); //dTime in ms
  Serial.println("Drivetime in ms: " + String(dTime));
  return(dTime);
}

double Winch::checkPosition(int distanz, int direction){
  if ((position+distanz) > max_distanz_Winch && direction == DOWN){
      distanz = max_distanz_Winch-position;
      Serial.println("Max. Distanz reached: " + String(max_distanz_Winch));
  }
  else if ((position-distanz) < min_distanz_Winch && direction== UP){
    distanz = position-min_distanz_Winch;
    Serial.println("Min. Distanz reached: " + String(min_distanz_Winch));
  }

    Serial.println("Distanz: " + String(distanz));
    position=position+(distanz*direction);
    return distanz;
}

void Winch::startDriving(bool status){
  if (status){
    digitalWrite(WINCH_RELAIS_DOWN_1, HIGH);
    // digitalWrite(WINCH_RELAIS_DOWN_2, HIGH);
  }
  else{
    digitalWrite(WINCH_RELAIS_DOWN_1, LOW);
    // digitalWrite(WINCH_RELAIS_DOWN_2, LOW);
  }
}
void Winch::directionDriving(int direction){
  if (direction){
    // digitalWrite(WINCH_RELAIS_DOWN_1, HIGH);
    digitalWrite(WINCH_RELAIS_DOWN_2, HIGH);
  }
  else{
    // digitalWrite(WINCH_RELAIS_DOWN_1, LOW);
    digitalWrite(WINCH_RELAIS_DOWN_2, LOW);
  }
}

void Winch::test(){
  //Serial.println("");
  //Serial.println("===Start Winch Test===");
  //Serial.println("");
  Winch winch;
  //int delaytime = 200;

winch.drive(100, DOWN);
delay(2000);
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
