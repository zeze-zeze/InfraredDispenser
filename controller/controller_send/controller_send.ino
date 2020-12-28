#include "IRSendRev.h"

#define BIT_LEN         0
#define BIT_START_H     1
#define BIT_START_L     2
#define BIT_DATA_H      3
#define BIT_DATA_L      4
#define BIT_DATA_LEN    5
#define BIT_DATA        6

const int ir_freq = 38;                 // 38k

const int buttonPinModeA = 2;
const int buttonPinModeB = 4;

unsigned char dtaSend[20];
void dtaInit()
{
    dtaSend[BIT_LEN]        = 11;			// all data that needs to be sent
    dtaSend[BIT_START_H]    = 179;			// the logic high duration of "Start"
    dtaSend[BIT_START_L]    = 90;			// the logic low duration of "Start"
    dtaSend[BIT_DATA_H]     = 11;			// the logic "long" duration in the communication
    dtaSend[BIT_DATA_L]     = 33;			// the logic "short" duration in the communication
    
    dtaSend[BIT_DATA_LEN]   = 1;			// Number of data which will sent. If the number is other, you should increase or reduce dtaSend[BIT_DATA+x].
    
    dtaSend[BIT_DATA+0]     = 65;
}

void setup()
{
    pinMode(buttonPinModeA, INPUT);
    pinMode(buttonPinModeB, INPUT);
    dtaInit();
}

void changeMode(char mode){
  dtaSend[BIT_DATA+0] = mode;
}

void loop(){
    int readingA = digitalRead(buttonPinModeA), readingB = digitalRead(buttonPinModeB);
    delay(500);
    if(readingA == HIGH){
      changeMode('A');
      IR.Send(dtaSend, 38); 
    }
    else if(readingB == HIGH){
      changeMode('B');
      IR.Send(dtaSend, 38);
    }
    delay(1000);
}
