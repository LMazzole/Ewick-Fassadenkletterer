#ifndef WINCH_H_
#define WINCH_H_


#include "global.h"
#include "Arduino.h"

class Winch
{
  private:

  public:
    // Communicate();
    Winch();
    void up(int distanz);
    void down(int distanz);
    void test();

};



#endif /* WINCH_H_ */
