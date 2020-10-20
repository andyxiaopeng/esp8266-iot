void setup() {          //初始化函数，这个函数内的代码只在启动时运行一次
pinMode(D4,OUTPUT);  //设置GPIO口D4状态为输出模式
}

void loop() {             //循环函数，这个函数内的代码会一直循环运行
digitalWrite(D4,HIGH);  //设置GPIO口D4输出高电平，HIGH可以用1代替
delay(1000);            //延时1000毫秒
digitalWrite(D4,LOW);   //设置GPIO口D4输出低电平，LOW可以用0代替
delay(1000);            //https://blog.zeruns.tech
}
