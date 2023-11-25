/*
 * @Author: qwqb233 3087820261@qq.com
 * @Date: 2023-09-23 10:45:53
 * @LastEditors: qwqb233 3087820261@qq.com
 * @LastEditTime: 2023-11-25 16:02:27
 * @FilePath: \esp32c:\Users\qwqb233\Documents\PlatformIO\Projects\test_WiFi\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include "./Hardware/Header.h"

void onTimer();
hw_timer_t *timer = NULL;

uint8_t WiFiConnectTimeCout = 0;

enum DisplayStatus{Dis_Opening,Dis_Working,Dis_Closing};
enum HttpStatus{Http_Getting,Http_Error,Http_Got};


void setup() {
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(23,OUTPUT);

  TFTInit();

  //Serial.begin(115200);                          //初始化串口，波特率为115200，如果中文乱码在串口监视器选择utf-8编码
  delay(50);
  //GetWeatherResultClass GetWeatherResult;

  timer = timerBegin(0,80,true);
  timerAttachInterrupt(timer,&onTimer,true);
  timerAlarmWrite(timer,200000,true);
  timerAlarmEnable(timer);
  
  ws2812::ws2812InitStruct ws2812BInitStruct;
  ws2812BInitStruct.GPIO = 23;
  ws2812BInitStruct.LED_Num = 10;
  ws2812::WS_Init(&ws2812BInitStruct);

  ws2812::ALL(0x00ffff);

  //WiFiConnect((char *)ssid, (char *)Password);      //连接到WiFi

}

void loop() {
  if(WiFiStatus == WiFi_Connected)Serial.println("connected");
  TFT_DisplayBlue();
  delay(1000);
}

void onTimer()
{
  if(WiFiStatus == WiFi_Connecting)
  {
    if(WiFi.status() == WL_CONNECTED)WiFiStatus = WiFi_Connected;
    else if (WiFiConnectTimeCout >= 50) WiFiStatus = WiFi_ConnectError;
    else WiFiConnectTimeCout++;
  }
  digitalWrite(2,!digitalRead(2));
/*   if(digitalRead(2)) digitalWrite(2,0);
  else digitalWrite(2,1); */
}

