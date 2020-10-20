#include<ESP8266WiFi.h>

const char* ssid = "LYW";          //wifi名
const char* passwd = "29303270";    //wifi密码

void setup() {
Serial.begin(115200);     //设置串口波特率
WiFi.begin(ssid,passwd);  //连接wifi
while (WiFi.status() != WL_CONNECTED) //判断wifi连接状态
{
delay(500);
Serial.print(".");      //串口打印 .
}
Serial.println("");       //换行
Serial.println("WiFi cnnected");
Serial.println(WiFi.localIP());   //打印获取到的IP地址
Serial.println("https://blog.zeruns.tech");
}

void loop() {

}
