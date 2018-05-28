/*
 * drive.h
 *
 *  Created on: 08.03.2018
 *      Author: Luca
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#define MYDEBUG

#include "global.h"
#include "Arduino.h"
#include <math.h>
#include "debug.h"

class Drive
{

  public:
    Drive();
    // void Step(int steps, int direction, int motorspeed);
    long CalculationDistanceToSteps(unsigned int distance); // distance in mm
    void Driving(unsigned int distance, int direction); //distance in mm
    void Acceleration();
    void SlowDown();
    void printDouble(double val, unsigned int precision);
    int actualHorizontalPosition = 0;

  private:
    //int stepCountTop = 0;
    //int speedTop=0;
    //int stepCountBottom = 0;
    //int speedBottom = 0;
    const int stepsPerRevolution = 200*4;
    const double durchmesserZahnradAn = 24.0;
    const double durchmesserZahnradAb = 77.0;
    const double durchmesserReibrad = 90.0;
    const double maxSpeed = 0.05; // speed [m/s]
    const double wegProMotorumdrehung = M_PI*durchmesserReibrad*(durchmesserZahnradAn/durchmesserZahnradAb);
    const unsigned int neededDelay = M_PI*durchmesserReibrad*durchmesserZahnradAn/(400*maxSpeed*durchmesserZahnradAb)*1000/16;
    const int accelorationFaktor = 300000;
    const float sin3[162]={ 0.000,
                            0.000,
                            0.000,
                            0.000,
                            0.000,
                            0.000,
                            0.000,
                            0.001,
                            0.001,
                            0.001,
                            0.001,
                            0.002,
                            0.002,
                            0.003,
                            0.003,
                            0.004,
                            0.005,
                            0.006,
                            0.007,
                            0.008,
                            0.009,
                            0.010,
                            0.012,
                            0.013,
                            0.015,
                            0.017,
                            0.019,
                            0.021,
                            0.023,
                            0.026,
                            0.028,
                            0.031,
                            0.034,
                            0.037,
                            0.040,
                            0.044,
                            0.047,
                            0.051,
                            0.055,
                            0.059,
                            0.063,
                            0.068,
                            0.072,
                            0.077,
                            0.082,
                            0.087,
                            0.093,
                            0.098,
                            0.104,
                            0.110,
                            0.116,
                            0.123,
                            0.129,
                            0.136,
                            0.143,
                            0.150,
                            0.157,
                            0.165,
                            0.172,
                            0.180,
                            0.188,
                            0.196,
                            0.204,
                            0.213,
                            0.222,
                            0.230,
                            0.239,
                            0.249,
                            0.258,
                            0.267,
                            0.277,
                            0.287,
                            0.297,
                            0.307,
                            0.317,
                            0.327,
                            0.337,
                            0.348,
                            0.358,
                            0.369,
                            0.380,
                            0.391,
                            0.402,
                            0.413,
                            0.424,
                            0.435,
                            0.447,
                            0.458,
                            0.469,
                            0.481,
                            0.492,
                            0.504,
                            0.515,
                            0.527,
                            0.538,
                            0.550,
                            0.561,
                            0.573,
                            0.584,
                            0.596,
                            0.607,
                            0.619,
                            0.630,
                            0.641,
                            0.653,
                            0.664,
                            0.675,
                            0.686,
                            0.697,
                            0.708,
                            0.719,
                            0.729,
                            0.740,
                            0.750,
                            0.760,
                            0.771,
                            0.781,
                            0.790,
                            0.800,
                            0.810,
                            0.819,
                            0.828,
                            0.837,
                            0.846,
                            0.855,
                            0.863,
                            0.871,
                            0.879,
                            0.887,
                            0.895,
                            0.902,
                            0.909,
                            0.916,
                            0.923,
                            0.929,
                            0.935,
                            0.941,
                            0.947,
                            0.952,
                            0.957,
                            0.962,
                            0.966,
                            0.971,
                            0.975,
                            0.978,
                            0.982,
                            0.985,
                            0.988,
                            0.990,
                            0.993,
                            0.994,
                            0.996,
                            0.998,
                            0.999,
                            0.999,
                            1.000,
                            1.000,
                            1.000,
                            1.000,
                            1.000,
                            1.000,
                            1.000};
};



#endif /* DRIVE_H_ */
