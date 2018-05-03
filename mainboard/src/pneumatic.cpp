#include "pneumatic.h"

Pneumatic::Pneumatic(){

}

void Pneumatic::cylinderout(){
  Serial.println("Cylinder out");
  if (!status_cylinder_in) { // Check if Cylinder is already out
    Serial.println("Cylinder is already out!");
    return;
  }

  vacuumcup(false);
  Serial.println("       PNEUMATIC_VALVE_OUT, HIGH");
  digitalWrite(PNEUMATIC_VALVE_OUT, HIGH);
  delay(time_cylinder_offout); //Start Vaccum after delay
  vacuumcup(true);
  while (!vacuumstatus()) {
    vacuumsensor= vacuumsensor + 10; //just for testing
    delay(50); //Pollingrate
  }
  vacuumsensor=0; //just for testing
  Serial.println("       PNEUMATIC_VALVE_OUT, LOW");
  digitalWrite(PNEUMATIC_VALVE_OUT, LOW);
  Serial.println("Cylinder out: Stopped");
  status_cylinder_in=false;
}

void Pneumatic::cylinderin(){
  Serial.println("Cylinder in");
  if (status_cylinder_in) { // Check if Cylinder is already in
    Serial.println("Cylinder is already in!");
    return;
  }

  vacuumcup(false);
  Serial.println("       PNEUMATIC_VALVE_IN, HIGH");
  digitalWrite(PNEUMATIC_VALVE_IN, HIGH);
  delay(time_cylinder_in);
    Serial.println("       PNEUMATIC_VALVE_IN, LOW");
  digitalWrite(PNEUMATIC_VALVE_IN, LOW);
  status_cylinder_in=true;
}

void Pneumatic::vacuumcup(boolean status_cup){
  Serial.print("Vacuumcup: ");
  if(status_cup){
    Serial.println("ACTIV");
    digitalWrite(VACUUM_VALVE, HIGH);
  }
  else{
    Serial.println("INACTIV");
    digitalWrite(VACUUM_VALVE, LOW);
  }
  delay(500); //Give vacuum time to activate/deactivate
}

boolean Pneumatic::vacuumstatus(){
  Serial.print("Vacuumstatus: ");
  // vacuumsensor= digitalRead(PNEUMATIC_SENSOR);
  if (vacuumsensor > vacuumsensor_upper){
    Serial.println("TRUE " + String(vacuumsensor));
    return(true);
  }
  else{
    Serial.println("FALSE " + String(vacuumsensor));
    return(false);
  }
}

void Pneumatic::test(){
  Serial.println(" ");
  Serial.println("===Start Pneumatic Test===");
  Serial.println(" ");
  Pneumatic pneumatic;
  int delaytime = 200;
  pneumatic.cylinderin();
  delay(delaytime);
  pneumatic.cylinderout();
  delay(delaytime);
  pneumatic.cylinderout();
  delay(delaytime);
  pneumatic.cylinderin();
  delay(delaytime);
  pneumatic.cylinderin();
  delay(delaytime);
  pneumatic.cylinderout();
  delay(delaytime);
  pneumatic.cylinderout();
  delay(delaytime);
  pneumatic.cylinderin();
  delay(delaytime);
  pneumatic.cylinderin();
  delay(delaytime);
}
