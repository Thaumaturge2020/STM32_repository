#include <Arduino.h>
#include <DHT.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Wire.h>

#include <Chrono.h>

Chrono chronoA;
Chrono chronoB;

#define DHTPIN PB8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, OLED_RESET);

void display_number(int order,int number);
void words_display();
void read_data();

const int ledPin = PC13;

//b     a0 
//SEG3  a1 
//SEG2  a2 
//f     a3 
//a     b0 
//SEG1  b1 
//SEG4  a4 
//g     a5 
//c     a6 
//dp    a7 
//d     a9 
//e     a8 

int b     = PA0;
int SEG3  = PA1;
int SEG2  = PA2;
int f     = PA3;
int a     = PB0;
int SEG1  = PB1;
int SEG4  = PA4;
int g     = PA5;
int c     = PA6;
int dp    = PA7;
int d     = PA8;
int e     = PA9;

int scl   = SCL; //PB6
int sda   = SDA; //PB7

int humidity = 0;
int temperature = 0;

int seg_array[4] = {SEG4,SEG3,SEG2,SEG1};
int led_array[8] = {a,b,c,d,e,f,g,dp};


//B,?,C,SEG1,A,F,G,DP

int logic_array[10][8] = {
  //a,b,c,d,e,f,g,dp
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
};

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // dht.begin();

  for(int i=0;i<4;++i){
    pinMode(seg_array[i], OUTPUT);
  }
  
  digitalWrite(seg_array[0], LOW);
  digitalWrite(seg_array[1], LOW);
  digitalWrite(seg_array[2], LOW);
  digitalWrite(seg_array[3], LOW);

  for(int i=0;i<8;++i){
    pinMode(led_array[i], OUTPUT);
  }
  digitalWrite(led_array[0], HIGH);
  digitalWrite(led_array[1], HIGH);
  digitalWrite(led_array[2], HIGH);
  digitalWrite(led_array[3], HIGH);
  digitalWrite(led_array[4], HIGH);
  digitalWrite(led_array[5], HIGH);
  digitalWrite(led_array[6], HIGH);
  digitalWrite(led_array[7], HIGH);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  read_data();
}

void loop() {


    // float humidity = dht.readHumidity();
    // float temperature = dht.readTemperature();

    // if (isnan(humidity) || isnan(temperature)) {
    //     Serial.println("读取失败！");
    //     return;
    // }

    // Serial.print("湿度: ");
    // Serial.print(humidity);
    // Serial.print(" %\t");
    // Serial.print("温度: ");
    // Serial.print(temperature);
    // Serial.println(" *C");

    // delay(2000);  // 每2秒读取一次

  // put your main code here, to run repeatedly:

  // for(int i=1;i<=5;++i){
  //   digitalWrite(ledPin, HIGH);
  //   delay(60*i);
  //   digitalWrite(ledPin, LOW);
  //   delay(60*i);
  //   Serial.println("Done!");
  // }

  // digitalWrite(led_array[0], HIGH);
  // digitalWrite(led_array[1], HIGH);
  // digitalWrite(led_array[2], HIGH);
  // digitalWrite(led_array[3], HIGH);
  // digitalWrite(led_array[4], HIGH);
  // digitalWrite(led_array[5], HIGH);
  // digitalWrite(led_array[6], HIGH);
  // digitalWrite(led_array[7], HIGH);
  // for(int i=0;i<=7;++i){
  //   digitalWrite(led_array[i], LOW);
  //   delay(800);
  // }
  if(chronoA.hasPassed(1000)){
    chronoA.restart();
    words_display();
    display.display();
  }
  if(chronoB.hasPassed(2500)){
    chronoB.restart();
    read_data();
  }
  return;
}

void read_data(){
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if(h!=0) humidity = h / 2;
  if(t!=0) temperature = t + 10;
}

void  words_display(){
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  // 设置字体颜色,白色可见
  display.setTextColor(WHITE);
 
  //设置字体大小
  display.setTextSize(1.5);
 
  //设置光标位置
  display.setCursor(0, 0);
  display.print("TaichiMaker");
 
  display.setCursor(0, 10);
  display.print("time: ");
  //打印自开发板重置以来的秒数：
  display.print(millis() / 1000);
  display.print(" s");

  display.setCursor(0, 20);
  display.print("humidity: ");
  display.print(humidity);
  display.print("%RH");

  
  display.setCursor(0, 30);
  display.print("temperature: ");
  display.print(temperature);
  display.print(" °C");
 
  display.setCursor(0, 40);
  display.setTextColor(WHITE);
  display.print("Author: ");
  display.print("Dapenson");
}



void display_number(int order,int number){
  digitalWrite(seg_array[order],HIGH);  
  for(int i=0;i<8;++i){
    digitalWrite(led_array[i],logic_array[number][i]^1);
  }
  delay(2);
  digitalWrite(seg_array[order],LOW);
}