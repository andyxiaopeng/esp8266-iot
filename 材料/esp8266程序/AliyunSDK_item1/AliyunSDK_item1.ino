// 引入 wifi 模块，并实例化，不同的芯片这里的依赖可能不同
#include <ESP8266WiFi.h>
static WiFiClient espClient;
 
// 引入阿里云 IoT SDK
#include <AliyunIoTSDK.h>
 
// 设置产品和设备的信息，从阿里云设备信息里查看
#define PRODUCT_KEY "a10R0jb1HhA"
#define DEVICE_NAME "WZd5lOvQpTRKxuL1YhPM"
#define DEVICE_SECRET "8a30a05929b214e7e051b0ad5c1703f2"
#define REGION_ID "cn-shanghai"
 
// 设置 wifi 信息
#define WIFI_SSID "LYW"
#define WIFI_PASSWD "29303270"

// 设置温控设备 DHT11 信息
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
// 初始化 DHT 传感器
DHT dht(DHTPIN, DHTTYPE, 15);
float RH,T;

int y = 12;
int ledstate = 0;
 
void setup()
{
    Serial.begin(115200);
    
    pinMode(y,OUTPUT);  //设置GPIO口D4状态为输出模式
    ledstate = digitalRead(y);
    
    // 初始化 wifi
    wifiInit(WIFI_SSID, WIFI_PASSWD);
    
    // 初始化 iot，需传入 wifi 的 client，和设备产品信息
    AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);
    
    // 绑定一个设备属性回调，当远程修改此属性，会触发 powerCallback
    // PowerSwitch 是在设备产品中定义的物联网模型的 id
    AliyunIoTSDK::bindData("LEDSwitchY", powerCallback);
    
    // 发送一个数据到云平台，CurrentTemperature 是在设备产品中定义的物联网模型的 id
    AliyunIoTSDK::send("LEDSwitchY", ledstate);




    // 启动 DHT
    dht.begin();
}
 
void loop()
{
    RH = dht.readHumidity();
    T  = dht.readTemperature();
    // 发送一个数据到云平台，CurrentTemperature 是在设备产品中定义的物联网模型的 id
    AliyunIoTSDK::send("LEDSwitchY", ledstate);
    // 发送一个数据到云平台，CurrentTemperature 是在设备产品中定义的物联网模型的 id
    AliyunIoTSDK::send("LEDSwitchY", ledstate);
    
    

    AliyunIoTSDK::loop();
}
 
// 初始化 wifi 连接
void wifiInit(const char *ssid, const char *passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
}
 
// 电源属性修改的回调函数
void powerCallback(JsonVariant p)
{

/* 
    int PowerSwitch = p["PowerSwitch"];
      // PowerSwitch 是设备功能的标识符
    if (PowerSwitch == 1)
    {
        // 启动设备
    } 
*/
 

  
  ledstate = digitalRead(y);
    
    if (ledstate == HIGH)
    {
       digitalWrite(y,LOW);
    }else{
      digitalWrite(y,HIGH);
    }
}
