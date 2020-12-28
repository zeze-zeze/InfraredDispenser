#include "IRSendRev.h"
const int pinRecv = 2;              // ir receiver connect to D2

void setup()
{
    Serial.begin(115200);
    IR.Init(pinRecv);
    Serial.println("init over");
}

unsigned char dta[20];

void loop()
{
    if(IR.IsDta())                  // get IR data
    {
        IR.Recv(dta);               // receive data to dta
        if(dta[6] == 'A'){
          Serial.println("Mode A");
        }
        else if (dta[6] == 'B'){
          Serial.println("Mode B");
        }
        else{
          Serial.println("Recv Error. Do Nothing !");
        }
    }
}
