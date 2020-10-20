


int r = 14;
int y =12;
int g =13;
void setup() {          //初始化函数，这个函数内的代码只在启动时运行一次
pinMode(r,OUTPUT);  //设置GPIO口D4状态为输出模式
pinMode(y,OUTPUT);  //设置GPIO口D4状态为输出模式
pinMode(g,OUTPUT);  //设置GPIO口D4状态为输出模式
}

void loop() {             //循环函数，这个函数内的代码会一直循环运行
digitalWrite(r,HIGH);  //设置GPIO口D4输出高电平，HIGH可以用1代替
delay(1000);            //延时1000毫秒
digitalWrite(r,LOW);   //设置GPIO口D4输出低电平，LOW可以用0代替
delay(1000);         

digitalWrite(y,HIGH);  //设置GPIO口D4输出高电平，HIGH可以用1代替
delay(1000);            //延时1000毫秒
digitalWrite(y,LOW);   //设置GPIO口D4输出低电平，LOW可以用0代替
delay(1000);    

digitalWrite(g,HIGH);  //设置GPIO口D4输出高电平，HIGH可以用1代替
delay(1000);            //延时1000毫秒
digitalWrite(g,LOW);   //设置GPIO口D4输出低电平，LOW可以用0代替
delay(1000);    
}
