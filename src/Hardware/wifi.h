#ifndef __WIFI__H
#define __WIFI__H

#include <Arduino.h>
#include "WiFi.h"
#include "WiFiClientSecure.h"

const char *ssid = "猫正日记";               //WIFI名称
const char *Password = "B23431123456";       //WIFI密码

enum WiFiStatusEnum{WiFi_Rest,WiFi_Connecting,WiFi_Connected,WiFi_ConnectError,WiFi_DisConnect};


static uint8_t WiFiStatus = WiFi_Rest;

/*
*初始化WiFi连接
*/
void WiFiInit()
{
    WiFiClientSecure httpsClient;
    httpsClient.setInsecure();
}

/*
*连接WiFi
*@param char* WiFi_ssid 需要连接WiFi的名称
*@param char* WiFi_password 需要连接的WiFi的密码
*@return 如果连接成功返回true，反之返回false
*/
void WiFiConnect(char *WiFi_ssid, char *WiFi_password)
{
  Serial.println("正在连接WiFi：");          
  Serial.println(WiFi_ssid);

  WiFi.begin(WiFi_ssid,WiFi_password);

  WiFiStatus = WiFi_Connecting;
}




#endif
