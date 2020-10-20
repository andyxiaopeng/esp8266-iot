void setup() {    //初始化函数，这个函数内的代码只在启动时运行一次
Serial.begin(115200);    //设置串口波特率
}
/*
https://blog.zeruns.tech
*/
void loop() {     //循环函数，这个函数内的代码会一直循环运行
Serial.println("Hello World"); //向串口打印Hello World
}
