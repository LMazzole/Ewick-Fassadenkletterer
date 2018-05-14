#ifndef WINCH_H_
#define WINCH_H_


#include "global.h"
#include "Arduino.h"
#include "debug.h"

class Winch
{
  public:
    Winch();
    void drive(int distanz, int direction);
    void test();


  private:
    double drivetime =0.0;
    int position = 0;
    int distanz = 0.0;
    bool directionDown = true; //true == down
    bool statusDriving = false; //true == driving
    const double winchspeed = 4.0*1000.0/60.0; //Winchspeed: 4m/min
    const int min_distanz_Winch = 0; //
    const int max_distanz_Winch = 3*1000; //height of the Wall 3m
    void driveDown(bool status);
    void driveUp(bool status);
    void changeDriveStatus(); //toggle status
    void changeDirStatus();
    double convertDistanzTime(int distanz);
    double checkPosition(int distanz, int direction);
};



#endif /* WINCH_H_ */
