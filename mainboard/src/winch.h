#ifndef WINCH_H_
#define WINCH_H_


#include "global.h"
#include "Arduino.h"


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
    const double winchspeed = 4.0*1000.0/60.0; //Winchspeed: 4m/min
    const int min_distanz_Winch = 0; //
    const int max_distanz_Winch = 3*1000; //High Wall 3m
    void startDriving(bool status);
    void directionDriving(int direction);
    double convertDistanzTime(int distanz);
    double checkPosition(int distanz, int direction);
};



#endif /* WINCH_H_ */
