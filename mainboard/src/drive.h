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

  public:
    Drive();
    // void Step(int steps, int direction, int motorspeed);
    void test();

  private:

    const int RIGHT = 1;
    const int LEFT = -1;
};



#endif /* DRIVE_H_ */
