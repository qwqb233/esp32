#ifndef __TFT__H
#define __TFT__H

#include "Arduino.h"

#define SCLPin 12
#define SDAPin 13
#define CSPin  14
#define DCPin  27
#define RESPin 26

#define CS_Enable() digitalWrite(CSPin,0)
#define CS_Default() digitalWrite(CSPin,1)
#define SDA_Write(x) digitalWrite(SDAPin,(x))
#define SCL_Write(x) digitalWrite(SCLPin,(x))
#define WriteData() digitalWrite(DCPin,1)
#define WriteComm() digitalWrite(DCPin,0)
#define RESSet(x) digitalWrite(RESPin,(x))

void TFTInit();
void TFT_WRByte(uint8_t *Data);
void TFT_Test(int data);
void TFT_DisplayBlue();

#endif