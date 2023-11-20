#include "weather.h"

StaticJsonDocument<2048> doc;
HTTPClient http;

bool GetWeatherResultClass::getWeather(String WeatherUrl)
{
  http.begin(WeatherUrl);                         //指定要请求的URL
  Serial.println("尝试连接中");
  int httpCode = http.GET();                      //发送http请求
  delay(500);
  Serial.printf("http code: %d\n", httpCode);     //输出http码
  if (httpCode == 200)
  {
    WiFiClient *Stream = http.getStreamPtr();     //获取字符
    size_t size_avail = Stream->available();      //计算字符长度
    uint8_t responseData[1024];                   //缓冲区
    size_t size_in = Stream->readBytes(responseData, size_avail);    //计算返回长度，并写入responseData


    uint8_t *outbuf = (uint8_t *)malloc(sizeof(uint8_t)*1024*2);     //输出缓冲区
    uint32_t size_out = 0;                        //初始化输出字符长度变量

    if(ArduinoUZlib::decompress(responseData, size_in, outbuf, size_out))Serial.write(outbuf,size_out);      //gzip解包
    Serial.println(" ");
    deserializeJson(doc,outbuf,size_out);      //序列化输出缓冲区到doc
    free(outbuf);                              //释放输出缓冲区
  }
  else                                         //TODO 完善错误处理的逻辑链
  {
    Serial.println("Error");
    http.end();
    delay(1000);
    if (count++ <= 50)
    {
      Serial.printf("已尝试 %d 次",count);
      getWeather(WeatherUrl);
    }
    else {
      Serial.println("Link time out");
      return false;
    }
  }
  http.end();
  return true;
}

void GetWeatherResultClass::TFWeather_Json()
{
  if(getWeather(TFWeather))
  {
    JsonArray now = doc["hourly"];

    for (char i = 0; i < 3; i++)
    {

      TFTemp[i] =       now[i]["temp"].as<int>();
      TFPop[i] =        now[i]["pop"].as<int>();
      TFPrecip[i] =     now[i]["precip"].as<int>();
      TFHumidity[i] =   now[i]["humidity"].as<int>();
      TFText[i] =       now[i]["text"].as<String>();
      TFWindDir[i] =    now[i]["windDir"].as<String>();
    }
    isGetWeather = true;
  };
}

void GetWeatherResultClass::OnTimeWeather_Json()
{
  if(getWeather(OnTimeWeather))
  {
    JsonObject now = doc["now"];

    OnTimeTemp =        now["temp"].as<int>();
    OnTimeFeelsLike =   now["feelsLike"].as<int>();
    OnTimeHumidity =    now["humidity"].as<int>();
    OnTimePrecip =      now["precip"].as<int>();
    OnTimeText =        now["text"].as<String>();
    OnTimeWindDir =     now["windDir"].as<String>();

    isGetWeather = true;
  }
}

void GetWeatherResultClass::DayWeather_Json()
{
  if(getWeather(DayWeather))
  {
    JsonArray now = doc["daily"];

    for(char i = 0;i < 3;i++)
    {
      DayTempMax[i] =       now[i]["tempMax"].as<int>();
      DayTempMin[i] =       now[i]["tempMin"].as<int>();
      DayHumidity[i] =      now[i]["humidity"].as<int>();
      DayPrecip[i] =        now[i]["precip"].as<int>();
      DayTextDay[i] =       now[i]["textDay"].as<String>();
      DayTextNight[i] =     now[i]["textNight"].as<String>();
      DayWindDirDay[i] =    now[i]["windDirDay"].as<String>();
      DayWindDirNight[i] =  now[i]["windDirNight"].as<String>();
      DaySunrise[i] =       now[i]["sunrise"].as<String>();
      DaySunset[i] =        now[i]["sunset"].as<String>();
      DayMoonrise[i] =      now[i]["moonrise"].as<String>();
      DayMoonset[i] =       now[i]["moonset"].as<String>();
      DayMoonPhase[i] =     now[i]["moonPhase"].as<String>();
    }
    isGetWeather = true;
  }
}
