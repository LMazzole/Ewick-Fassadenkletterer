
#include "comm.h"
// Communicate::Communicate(){
// };
//
// Communicate::Communicate(HardwareSerial &uart): VirtuinoBluetooth(uart){
// }


Communicate::Communicate(HardwareSerial &uart, uint32_t baud) : VirtuinoBluetooth(uart,baud){

}

void Communicate::test(){

}
