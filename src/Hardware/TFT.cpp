/*
 * @Author: qwqb233 3087820261@qq.com
 * @Date: 2023-10-15 10:46:20
 * @LastEditors: qwqb233 3087820261@qq.com
 * @LastEditTime: 2023-11-13 17:31:20
 * @FilePath: \esp32c:\Users\qwqb233\Documents\PlatformIO\Projects\test_WiFi\src\Hardware\TFT.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "TFT.h"



void TFTInit()
{
    pinMode(CSPin, OUTPUT);
    pinMode(SCLPin,OUTPUT);
    pinMode(SDAPin,OUTPUT);
    CS_Default();
    RESSet(1);
}

void TFT_SendBit(uint8_t data)
{
    SDA_Write(data);
    ets_delay_us(1);
    SCL_Write(1);
    ets_delay_us(100);
    SCL_Write(0);
    ets_delay_us(1);
    SDA_Write(0);
}

void TFT_WRComm(uint8_t *Data)
{
    CS_Enable();
    delay(1);
    WriteComm();
    for(int i = 0;i < 8;i++)
    {
        TFT_SendBit(Data[i]);
        ets_delay_us(1);
    }
    delay(1);
    CS_Default();
}

void TFT_WRByte(uint8_t *Data)
{
    CS_Enable();
    delay(1);
    WriteData();
    for(int i = 0;i < 8;i++)
    {
        TFT_SendBit(Data[i]);
        ets_delay_us(100);
    }
    delay(1);
    CS_Default();
}

void TFT_DisplayBlue()
{
    CS_Enable();
    delay(1);
    WriteData();
    for(int i = 0;i < (128*160);i++)
    {
        for (int i = 24-1;i >= 0;i--)
        {
            TFT_SendBit((0xff0000 >> i)&1);
            ets_delay_us(100);
        }
    }
    delay(1);
    CS_Default(); 
}

void TFT_Test(int data)
{
    CS_Enable();
    delay(1);
    WriteData();
    for(int i = 0;i < (128*160);i++)
    {
        for (int i = 7;i >= 0;i--)
        {
            TFT_SendBit((data >> i)&1);
            ets_delay_us(100);
        }
    }
    delay(1);
    CS_Default(); 
}

