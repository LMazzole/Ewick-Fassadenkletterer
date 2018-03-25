#ifndef PNEUMATIC_H_
#define PNEUMATIC_H_


#include "global.h"
#include "Arduino.h"

class Pneumatic
{
  public:
    Pneumatic();
    void cylinderout();
    void cylinderin();
    void vacuumcup(boolean status_cup);
    boolean vacuumstatus();
    void test();

  private:
    boolean status_cylinder_in= true; 
    int vacuumsensor = 0;
    const int vacuumsensor_upper = 500;
    const int vacuumsensor_lower = 50;
    const int time_cylinder_offout = 2*1000; //5sec to pull in
    const int time_cylinder_in = 5*1000; //5sec to pull in
};



#endif /* PNEUMATIC_H_ */
