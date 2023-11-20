#ifndef __WS2812B__H
#define __WS2812B__H

#include <Arduino.h>

#include "Wire.h"

namespace ws2812
{
    #define get(x,y) ((x)>>(y)&1)    //判断二进制数中1的对应位置，当为1时该位置在二进制数中有1，为0则相反

    //存储基本变量结构体
    typedef struct
    {
        int GPIO;            //ws2812b信号线对应的GPIO口
        int LED_Num;         //LED灯的数量
    }ws2812InitStruct;

    ws2812InitStruct *DATA_P;  //函数调用全局结构体

   /*
   *功能：全局结构体初始化
   *@param 输入设置结构体指针
   */
    void WS_Init(ws2812InitStruct *inData)
    {
        DATA_P = inData;
    }

    /*
    功能：模拟纳秒级延时（不精确）
    当a = 1时延时时常为450-500ns；
    无返回值
    */
    void delay_ns(float a)
    {
        for (int i = 0; i < a; i++) NOP();
    }

    /*
    功能：0码定义
    无输入
    无返回
    */
    void code0()
    {
        digitalWrite(DATA_P->GPIO, HIGH);
        delay_ns(1);
        digitalWrite(DATA_P->GPIO, LOW);
        delay_ns(6);
    }

    /*
    功能：1码定义
    无输入
    无返回值
    */
    void code1()
    {
        digitalWrite(DATA_P->GPIO, HIGH);
        delay_ns(6);
        digitalWrite(DATA_P->GPIO, LOW);
        delay_ns(1);
    }

    /*
    功能：将16进制数转换为2进制信号输出
    输入数据每两位对应BGR中一个颜色的颜色值
    无返回值
    */
    void wsbSendData(int32_t data)
    {
        for(int i = 1;i < 25;i++)
        {
            if(get(data,24-i))code1();
            else code0();
        }
    }

    /*
    功能：设置所有灯为一种颜色
    调用wsbSendData函数产生对应LED数量的24位信号
    无返回值
    */
    void ALL(int32_t data)
    {
        for(int i = 0;i < DATA_P->LED_Num;i++)
        {
            wsbSendData(data);
        }
    }

    /*
    功能：单独设置每个灯的数据
    输入数组指针
    无返回值
    */
    void ChangeData(int32_t *data)
    {
        for(int i = 0;i < DATA_P->LED_Num;i++)
        {
            wsbSendData(data[i]);
        }
    }

    /*
    功能：关闭灯光
    */
    void turnOff()
    {
        for(int i = 0;i < DATA_P->LED_Num;i++)wsbSendData(0x000000);
    }
}


#endif
