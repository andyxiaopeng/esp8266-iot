#include <ESP8266WiFi.h>

static WiFiClient espClient;
#include <ArduinoJson.h>

#include <AliyunIoTSDK.h>
AliyunIoTSDK iot;

#define PRODUCT_KEY "a10R0jb1HhA"
#define DEVICE_NAME "WZd5lOvQpTRKxuL1YhPM"
#define DEVICE_SECRET "8a30a05929b214e7e051b0ad5c1703f2"
#define REGION_ID "cn-shanghai"

#define WIFI_SSID "604"
#define WIFI_PASSWD "604406##"


#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11

// 初始化 DHT 传感器
DHT dht(DHTPIN, DHTTYPE, 15);
float RH,T;

int HumidityCtrl,TemperatureCtrl;

int LED_R = 14;
int LED_Y = 12;
int LED_G = 13;

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

    // 绑定湿度属性回调
    AliyunIoTSDK::send("HumidityCtrl", HumidityCtrl);
    AliyunIoTSDK::bindData("HumidityCtrl", HumidityCallback);

    // 绑定温度属性回调
    AliyunIoTSDK::send("TemperatureCtrl", TemperatureCtrl);
    AliyunIoTSDK::bindData("TemperatureCtrl", TemperatureCallback);

    // 绑定红灯属性回调
    pinMode(LED_R,OUTPUT);  //设置GPIO口IO14状态为输出模式
    AliyunIoTSDK::send("LEDSwitchR", digitalRead(LED_R));
    AliyunIoTSDK::bindData("LEDSwitchR", LEDRCallback);

    // 绑定黄灯属性回调
    pinMode(LED_Y,OUTPUT);  //设置GPIO口IO12状态为输出模式
    AliyunIoTSDK::send("LEDSwitchY", digitalRead(LED_Y));
    AliyunIoTSDK::bindData("LEDSwitchY", LEDYCallback);

    // 绑定绿灯属性回调
    pinMode(LED_G,OUTPUT);  //设置GPIO口IO13状态为输出模式
    AliyunIoTSDK::send("LEDSwitchG", digitalRead(LED_G));
    AliyunIoTSDK::bindData("LEDSwitchG", LEDGCallback);

    // 初始化 DHT11
    dht.begin();
}

unsigned long lastMsMain = 0;
void loop()
{
    AliyunIoTSDK::loop();
    if (millis() - lastMsMain >= 3000)
    {

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


      
        lastMsMain = millis();
        // 发送事件到阿里云平台
        //AliyunIoTSDK::sendEvent("xxx"); 
        // 发送模型属性到阿里云平台
        //AliyunIoTSDK::send("CurrentTemperature", 30);

        // 发送三种灯的当前状态
        //AliyunIoTSDK::send("LEDSwitchR", digitalRead(LED_R));
        //AliyunIoTSDK::send("LEDSwitchY", digitalRead(LED_Y));
        //AliyunIoTSDK::send("LEDSwitchG", digitalRead(LED_G));

        if(HumidityCtrl == 1){
          Serial.printf("湿度开关为：");Serial.println(HumidityCtrl);
          AliyunIoTSDK::send("Humidity", RH);
          //Serial.println("发送成功！");
        }
        
        if(TemperatureCtrl == 1){
          Serial.printf("温度开关为：");Serial.println(TemperatureCtrl);
          AliyunIoTSDK::send("Temperature", T);
          //Serial.println("发送成功！");
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
    AliyunIoTSDK::send("HumidityCtrl", HumidityCtrl);
}

void TemperatureCallback(JsonVariant p)
{
    int flag = p["TemperatureCtrl"];
    if (flag == 1)
    {
        //
        TemperatureCtrl = 1;
    }
    else
    {
        //
        TemperatureCtrl = 0;
    }
    Serial.printf("收到的温度开关为：");Serial.println(flag);
    AliyunIoTSDK::send("TemperatureCtrl", TemperatureCtrl);
}


void LEDRCallback(JsonVariant p)
{
    int flag = p["LEDSwitchR"];
    if (flag == 1)
    {
        //
        digitalWrite(LED_R,HIGH);
    }
    else
    {
        //
        digitalWrite(LED_R,LOW);
    }
    Serial.printf("收到的红灯开关为：");Serial.println(flag);
    AliyunIoTSDK::send("LEDSwitchR", digitalRead(LED_R));
     
}
void LEDYCallback(JsonVariant p)
{
    int flag = p["LEDSwitchY"];
    if (flag == 1)
    {
        //
        digitalWrite(LED_Y,HIGH);
    }
    else
    {
        //
        digitalWrite(LED_Y,LOW);
    }
    Serial.printf("收到的黄灯开关为：");Serial.println(flag);
    AliyunIoTSDK::send("LEDSwitchY", digitalRead(LED_Y));
}
void LEDGCallback(JsonVariant p)
{
    int flag = p["LEDSwitchG"];
    if (flag == 1)
    {
        //
        digitalWrite(LED_G,HIGH);
    }
    else
    {
        //
        digitalWrite(LED_G,LOW);
    }
    Serial.printf("收到的绿灯开关为：");Serial.println(flag);
    AliyunIoTSDK::send("LEDSwitchG", digitalRead(LED_G));
}
