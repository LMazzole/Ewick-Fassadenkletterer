#include "pneumatic.h"

Pneumatic::Pneumatic(){

}

void Pneumatic::cylinderout(){
  DEBUG_PRINTLN("Cylinder out");
  if (!status_cylinder_in) { // Check if Cylinder is already out
    DEBUG_PRINTLN("Cylinder is already out!");
    return;
  }

  vacuumcup(false);
  DEBUG_PRINTLN("       PNEUMATIC_VALVE_OUT, HIGH");
  digitalWrite(PNEUMATIC_VALVE_OUT, HIGH);
  delay(time_cylinder_offout); //Start Vaccum after delay
  vacuumcup(true);
  // while (!vacuumstatus()) {
  //   delay(100); //Pollingrate
  // }
    delay(time_cylinder_in);
  DEBUG_PRINTLN("       PNEUMATIC_VALVE_OUT, LOW");
  digitalWrite(PNEUMATIC_VALVE_OUT, LOW);
  DEBUG_PRINTLN("Cylinder out: Stopped");
  status_cylinder_in=false;
}

void Pneumatic::cylinderin(){
  DEBUG_PRINTLN("Cylinder in");
  if (status_cylinder_in) { // Check if Cylinder is already in
    DEBUG_PRINTLN("Cylinder is already in!");
    return;
  }

  vacuumcup(false);
  DEBUG_PRINTLN("       PNEUMATIC_VALVE_IN, HIGH");
  digitalWrite(PNEUMATIC_VALVE_IN, HIGH);
  delay(time_cylinder_in);
    DEBUG_PRINTLN("       PNEUMATIC_VALVE_IN, LOW");
  digitalWrite(PNEUMATIC_VALVE_IN, LOW);
  status_cylinder_in=true;
}

void Pneumatic::vacuumcup(boolean status_cup){
  DEBUG_PRINT("Vacuumcup: ");
  if(status_cup){
    DEBUG_PRINTLN("ACTIV");
    digitalWrite(VACUUM_VALVE, HIGH);
  }
  else{
    DEBUG_PRINTLN("INACTIV");
    digitalWrite(VACUUM_VALVE, LOW);
  }
  delay(500); //Give vacuum time to activate/deactivate
}

boolean Pneumatic::vacuumstatus(){
  DEBUG_PRINT("Vacuumstatus: ");
  vacuumsensor= analogRead(PNEUMATIC_SENSOR);
  if (vacuumsensor > vacuumsensor_upper){
    DEBUG_PRINTLN("TRUE " + String(vacuumsensor));
    return(true);
  }
  else{
    DEBUG_PRINTLN("FALSE " + String(vacuumsensor));
    return(false);
  }
}

void Pneumatic::test(){
  DEBUG_PRINTLN(" ");
  DEBUG_PRINTLN("===Start Pneumatic Test===");
  DEBUG_PRINTLN(" ");
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
