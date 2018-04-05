/*
 * drive.h
 *
 *  Created on: 08.03.2018
 *      Author: Luca
 */

#ifndef DRIVE_H_
#define DRIVE_H_


#include "global.h"
#include "Arduino.h"

class Drive
{
  private:
    void Step(int steps, int direction, int motorspeed);
    void test();
    
  public:
    Drive();
    const int RIGHT = 1;
    const int LEFT = -1;
    
};



#endif /* DRIVE_H_ */
