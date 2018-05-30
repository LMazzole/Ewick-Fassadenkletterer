#ifndef WINCH_H_
#define WINCH_H_

#define MYDEBUG

#include "global.h"
#include "Arduino.h"
#include "debug.h"

class Winch
{
  public:
    Winch();
    void initialise();
    void drive(int distanz, int direction);
    int position = 0;
    const int max_distanz_Winch = 2500; // height of the Wall in mm
    const int min_distanz_Winch = 0; //


  private:
    double drivetime =0.0;
    int distanz = 0.0;
    const double winchspeed = 4.0*1000.0/60.0; //Winchspeed: 4m/min
    void drivePowerOn(bool status);
    void driveDirection(int direction);
    double convertDistanzTime(int distanz);
    double checkPosition(int distanz, int direction);
};



#endif /* WINCH_H_ */
