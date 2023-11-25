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
#define SDA_Write(x,y) digitalWrite(SDAPin,(((x)>>(y))&1))
#define SCL_Write(x) digitalWrite(SCLPin,(x))
#define WriteData() digitalWrite(DCPin,1)
#define WriteComm() digitalWrite(DCPin,0)
#define RESSet(x) digitalWrite(RESPin,(x))

int *TFT_Data = NULL;

hw_timer_t *TFT_timer = NULL;

void TFTInit();
void TFT_WRByte(uint8_t *Data);
void TFT_Test(int data);
void TFT_DisplayBlue();

#endif