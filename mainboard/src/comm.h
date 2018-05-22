#ifndef COMM_H_
#define COMM_H_


#include "global.h"
#include "Arduino.h"
#include "VirtuinoBluetooth.h"
#include "debug.h"

class Communicate : public VirtuinoBluetooth
{
  private:

    HardwareSerial &uart = Serial1;
  public:
    // Communicate();
    Communicate(HardwareSerial &uart);
    Communicate(HardwareSerial &uart, uint32_t baud);
    void test();

};



#endif /* DRIVE_H_ */
