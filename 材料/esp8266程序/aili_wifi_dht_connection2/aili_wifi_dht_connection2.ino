#include <ESP8266WiFi.h>
/* 依赖 PubSubClient 2.4.0 */
#include <PubSubClient.h>
/* 依赖 ArduinoJson 5.13.4 */
#include <ArduinoJson.h>

#define SENSOR_PIN    13
/*
设备三元组
productKey = a10R0jb1HhA
deviceName = WZd5lOvQpTRKxuL1YhPM
deviceSecret = 8a30a05929b214e7e051b0ad5c1703f2
建立MQTT连接时参数
clientId = SN2930327
timestamp = 1539421321846
signmethod = hmacsha1

#define CLIENT_ID         "SN2930327|securemode=3,signmethod=hmacsha1,timestamp=1539421321846|"    // id+"|securemode=3,signmethod=hmacsha1,timestamp="+timestamp+"|"
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY
#define MQTT_PASSWD       
mqttPassword = b2488041f64f425016b467ee1c94959ebd592ad1
clientIdSN2930327deviceNameWZd5lOvQpTRKxuL1YhPMproductKeya10R0jb1HhAtimestamp1539421321846
hax1:4603a8a5d0545e20c87ee86954f387c57dfb7421

建立MQTT连接时参数
clientId = SN1928339
timestamp = 1539421321846
signmethod = hmacsha1

生成password的contentStr
content=clientIdSN1928339deviceNamelight1983432productKeya14Xib5kdYdtimestamp1539421321846

生成连接参数
mqttClientId = SN1928339|securemode=3,signmethod=hmacsha1,timestamp=1539421321846|
mqttUsername = light1983432&a14Xib5kdYd
mqttPassword = b2488041f64f425016b467ee1c94959ebd592ad1

*/
/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID         "LYW"
#define WIFI_PASSWD       "29303270"


/* 设备的三元组信息*/
#define PRODUCT_KEY       "a10R0jb1HhA"
#define DEVICE_NAME       "WZd5lOvQpTRKxuL1YhPM"
#define DEVICE_SECRET     "8a30a05929b214e7e051b0ad5c1703f2"
#define REGION_ID         "cn-shanghai"

/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY


#define CLIENT_ID         "SN2930327|securemode=3,signmethod=hmacsha1,timestamp=1539421321846|"    // id+"|securemode=3,signmethod=hmacsha1,timestamp="+timestamp+"|"
// 算法工具: http://iot-face.oss-cn-shanghai.aliyuncs.com/tools.htm 进行加密生成password
// password教程 https://www.yuque.com/cloud-dev/iot-tech/mebm5g
#define MQTT_PASSWD       "4603a8a5d0545e20c87ee86954f387c57dfb7421"                                     //clientId${id}deviceName${deviceName}productKey${productKey}timestamp${timestamp}

#define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

unsigned long lastMs = 0;
WiFiClient espClient;
PubSubClient  client(espClient);


void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    payload[length] = '\0';
    Serial.println((char *)payload);

}


void wifiInit()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }

    Serial.println("Connected to AP");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    
Serial.print("espClient [");


    client.setServer(MQTT_SERVER, MQTT_PORT);   /* 连接WiFi之后，连接MQTT服务器 */
    client.setCallback(callback);
}


void mqttCheckConnect()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT Server ...");
        if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD))

        {

            Serial.println("MQTT Connected!");

        }
        else
        {
            Serial.print("MQTT Connect err:");
            Serial.println(client.state());
            delay(5000);
        }
    }
}


void mqttIntervalPost()
{
    char param[32];
    char jsonBuf[128];

    sprintf(param, "{\"idle\":%d}", digitalRead(13));
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    Serial.println(jsonBuf);
    boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
    Serial.print("publish: 0失败; 1成功");
    Serial.println(d);
}


void setup() 
{

    pinMode(SENSOR_PIN,  INPUT);
    /* initialize serial for debugging */
    Serial.begin(115200);
    Serial.println("Demo Start");

    wifiInit();
}


// the loop function runs over and over again forever
void loop()
{
    if (millis() - lastMs >= 5000)
    {
        lastMs = millis();
        mqttCheckConnect(); 

        /* 上报 */
        mqttIntervalPost();
    }

    client.loop();
    if (digitalRead(SENSOR_PIN) == HIGH){
    Serial.println("Motion detected!");
    delay(2000);
      }
    else {
    Serial.println("Motion absent!");
    delay(2000);
  }

}
