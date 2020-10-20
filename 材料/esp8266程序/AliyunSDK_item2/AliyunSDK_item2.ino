#include <ESP8266WiFi.h>

static WiFiClient espClient;
#include <ArduinoJson.h>

#include <AliyunIoTSDK.h>
AliyunIoTSDK iot;

#define PRODUCT_KEY "a10R0jb1HhA"
#define DEVICE_NAME "WZd5lOvQpTRKxuL1YhPM"
#define DEVICE_SECRET "8a30a05929b214e7e051b0ad5c1703f2"
#define REGION_ID "cn-shanghai"

#define WIFI_SSID "LYW"
#define WIFI_PASSWD "29303270"


#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11

// 初始化 DHT 传感器
DHT dht(DHTPIN, DHTTYPE, 15);
float RH,T;

int HumidityCtrl;

void wifiInit(const char *ssid, const char *passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    WiFi.setAutoConnect (true);
    WiFi.setAutoReconnect (true);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
}

void setup()
{
    Serial.begin(115200);

    wifiInit(WIFI_SSID, WIFI_PASSWD);

    AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);

    // 绑定属性回调
    AliyunIoTSDK::send("HumidityCtrl", HumidityCtrl);
    AliyunIoTSDK::bindData("HumidityCtrl", HumidityCallback);

    // 初始化 DHT11
    dht.begin();
}

unsigned long lastMsMain = 0;
void loop()
{
    delay(4000);                  //延时4000毫秒
  
    // 获取湿度和温度
    RH = dht.readHumidity();
    T  = dht.readTemperature();
    /*
    Serial.print("Humidity:");  //向串口打印 Humidity:
    Serial.print(RH);           //向串口打印湿度数据
    Serial.print("%");
    Serial.print("  Temperature:");
    Serial.print(T);            //向串口打印温度数据
    Serial.println("C"); 
*/


  
    AliyunIoTSDK::loop();
    if (millis() - lastMsMain >= 5000)
    {
        lastMsMain = millis();
        // 发送事件到阿里云平台
        //AliyunIoTSDK::sendEvent("xxx"); 
        // 发送模型属性到阿里云平台
        //AliyunIoTSDK::send("CurrentTemperature", 30);

        if(HumidityCtrl == 1){
          Serial.printf("湿度开关为：");Serial.println(HumidityCtrl);
          AliyunIoTSDK::send("Humidity", RH);
          Serial.println("发送成功！");
        }
    }
}


void HumidityCallback(JsonVariant p)
{
    int flag = p["HumidityCtrl"];
    if (flag == 1)
    {
        //
        HumidityCtrl = 1;
    }
    else
    {
        //
        HumidityCtrl = 0;
    }
    Serial.printf("收到的湿度开关为：");Serial.println(flag);
}
