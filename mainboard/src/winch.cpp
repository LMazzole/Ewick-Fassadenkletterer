
#include "winch.h"

Winch::Winch(){

}

void Winch::drive(int distanz, int direction){
    Serial.println("Startposition in mm: " + String(position));
    distanz=checkPosition(distanz,direction);
    drivetime = convertDistanzTime(distanz);
  if (direction == DOWN){
      Serial.println("Direction: DOWN");
      digitalWrite(WINCH_RELAIS_DOWN, HIGH);
      delay(drivetime);
      digitalWrite(WINCH_RELAIS_DOWN, LOW);
  }
  else{
      Serial.println("Direction: UP");
      digitalWrite(WINCH_RELAIS_UP, HIGH);
      delay(drivetime);
      digitalWrite(WINCH_RELAIS_UP, LOW);
  }

  Serial.println("Endposition in mm: " + String(position));
  Serial.println("");
}

double Winch::convertDistanzTime(int distanz){
  double dTime=0.0;
  // Serial.println("DB-distanz: " + String(distanz));
  // Serial.println("DB-winchspeed: " + String(winchspeed));
  dTime=(abs(distanz)/ winchspeed)*1000; //dTime in ms
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



void Winch::test(){
  Winch winch;
  int delaytime = 200;
  Serial.println("");
  Serial.println("===Winch Test===");
  Serial.println("");
  winch.drive(1000,DOWN);
  delay(delaytime);
  winch.drive(500,DOWN);
  delay(delaytime);
  winch.drive(1000,DOWN);
  delay(delaytime);
  winch.drive(500,DOWN);
  delay(delaytime);
  winch.drive(500,DOWN);
  Serial.println("----------");
  winch.drive(1000,UP);
  delay(delaytime);
  winch.drive(500,UP);
  delay(delaytime);
  winch.drive(1000,UP);
  delay(delaytime);
  winch.drive(500,UP);
  delay(delaytime);
  winch.drive(500,UP);
  delay(delaytime);
}
