#ifndef __WEATHER__H
#define __WEATHER__H

#include <Arduino.h>
#include "HTTPClient.h"
#include "ArduinoJson.h"
#include "ArduinoUZlib.h"       //Gzip解包

const String TFWeather = "https://devapi.qweather.com/v7/weather/24h?location=101280101&key=8b42c4bd86c841538c80db5ab143b071";
const String OnTimeWeather = "https://devapi.qweather.com/v7/weather/now?location=101280101&key=8b42c4bd86c841538c80db5ab143b071";
const String DayWeather = "https://devapi.qweather.com/v7/weather/3d?location=101280101&key=8b42c4bd86c841538c80db5ab143b071";

static int count = 0;              //连接计次变量
static bool isGetWeather;

/*
*存储变量，解析JSON，解析函数基于getWeather函数
*/
class GetWeatherResultClass
{
public:
    /*
    *获取天气信息
    *（获取天气API的返回，进行Gzip解包后存储到doc类中）
    *@param String WeatherUrl 天气API的URL
    *@return 是否获取成功，成功返回true，反之返回false
    */
    bool getWeather(String WeatherUrl);
    /*
    *获取实时天气
    */
    void OnTimeWeather_Json();
    /*
    *获取逐小时天气
    */
    void TFWeather_Json();
    /*
    *获取每日天气
    */
    void DayWeather_Json();

    int TFTemp[3];                  //未来3小时的温度变化
    int TFHumidity[3];              //未来3小时的湿度变化
    int TFPrecip[3];                //未来3小时的降雨量
    int TFPop[3];                   //未来3小时的降雨概率
    String TFText[3];               //未来3小时的天气状况
    String TFWindDir[3];            //未来3小时的风向

    int OnTimeTemp;                 //实时温度
    int OnTimeFeelsLike;            //实时体感温度
    int OnTimeHumidity;             //实时湿度
    int OnTimePrecip;               //实时降雨量
    String OnTimeText;              //实时天气状况
    String OnTimeWindDir;           //实时风向

    int DayTempMax[3];              //每日最高温度
    int DayTempMin[3];              //每日最低温度
    int DayHumidity[3];             //每日湿度
    int DayPrecip[3];               //每日降雨量
    String DayTextDay[3];           //每日白日天气状况
    String DayTextNight[3];         //每日夜晚天气
    String DayWindDirDay[3];        //每日白日风向
    String DayWindDirNight[3];      //每日夜晚风向
    String DaySunrise[3];           //每日日出时间
    String DaySunset[3];            //每日日落时间
    String DayMoonrise[3];          //每日月亮升起时间
    String DayMoonset[3];           //每日月亮落下时间
    String DayMoonPhase[3];         //每日月相

};

#endif
