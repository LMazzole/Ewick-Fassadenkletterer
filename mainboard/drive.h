/*
 * motor.h
 *
 *  Created on: 08.03.2018
 *      Author: Luca
 */

#ifndef DRIVE_H_
#define DRIVE_H_


//#include "Arduino.h"
#include "global.h"

class Drive
{
  private:
    int dir = -1; 	// direction -1 = left 1 = right
    int pos = 0;	// Position

  public:
    Drive();
    void move(int direction, int distance,int velocity);

};



#endif /* DRIVE_H_ */
