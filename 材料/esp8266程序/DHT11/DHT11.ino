#include <Arduino.h>
#include <NTPClient.h>
#include <U8g2lib.h>
#include <DHT.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

DHT dht(D3,DHT11, 15);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ D1, /* data=*/ D2, /* reset=*/ U8X8_PIN_NONE);

void setup(){
u8g2.begin();
u8g2.enableUTF8Print();
dht.begin();
}

void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();
u8g2.clearBuffer();
u8g2.setFont(u8g2_font_unifont_t_chinese2);
u8g2.setFontDirection(0);
u8g2.setCursor(0, 15);
u8g2.print("Humidity:"); 
u8g2.setCursor(80, 15);
u8g2.print(h);    //https://blog.zeruns.tech
u8g2.setCursor(120, 15);
u8g2.print("%");
u8g2.setCursor(0, 40);
u8g2.print("Temperature:"); 
u8g2.setCursor(0, 55); 
u8g2.print(t);
u8g2.setCursor(40, 55);
u8g2.print("C");
u8g2.sendBuffer(); 
delay(1000);
}
