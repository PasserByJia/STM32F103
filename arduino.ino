#include<SoftwareSerial.h>
#include<HX711.h>
#include<dht11.h>
#define DHT11PIN 2
SoftwareSerial serial2(6,7);
Hx711 scale(A1, A0);
dht11 DHT11;
int Sensor= 3; //data针接口为任意I/O口即可
String s1 = "";
void HX711Init(void)
{
  Serial.println("System Init,Please Wait...");
  
  long offset= scale.getAverageValue(30);//计算偏移量(此时称必须保持水平且称上不能有东西！！！)
  scale.setOffset(offset);//设置偏移
  scale.setScale(405);//设置比例(此值需要根据不同的重量传感器自己设置！)
}
void setup() {
  Serial.begin(9600);
  serial2.begin(38400);
  pinMode(DHT11PIN,OUTPUT);
  pinMode(Sensor, INPUT);
  HX711Init();
}

void loop() {
  s1+="?id=2&";
  s1+="w=";
  s1+=(int)scale.getWeight(10)>0?(int)scale.getWeight(10):-(int)scale.getWeight(10);
  s1+="&";
  int chk = DHT11.read(DHT11PIN);
  int SensorState = digitalRead(Sensor);
  s1+="t=";
  s1+=((int)((float)DHT11.temperature)*100)/100.0;
  s1+="&";
  s1+="h=";
  s1+=((int)((float)DHT11.humidity)*100)/100.0;
  s1+="&";
  s1+="i=";
  s1+=SensorState;
  Serial.println(s1);
  serial2.println(s1);
  delay(1000);
  s1="";

}
