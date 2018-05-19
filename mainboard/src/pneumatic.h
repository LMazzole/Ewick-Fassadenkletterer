#ifndef PNEUMATIC_H_
#define PNEUMATIC_H_

#define MYDEBUG

#include "global.h"
#include "Arduino.h"
#include "debug.h"

class Pneumatic
{
  public:
    Pneumatic();
    void cylinderout();
    void cylinderin();
    void test();

  private:
    boolean status_cylinder_in= true;
    int vacuumsensor = 0;
    const int vacuumsensor_upper = 755; // min Value for activ-status
    // const int vacuumsensor_lower = 750;  //max Value for inactov-status
    const int time_cylinder_offout = 100; //
    const int time_cylinder_in = 8*1000; //8sec to pull in
    void vacuumcup(boolean status_cup); //Start Vaccum
    boolean vacuumstatus();
};



#endif /* PNEUMATIC_H_ */
