//library
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "DHT.h"

//setting
#define DHTPIN 7     // DHT11이 연결된 핀
#define DHTTYPE DHT11   // DHT 11, DHT시리즈중 11을 선택합니다.
#define TX 8  //HM10 TX가 연결된 핀
#define RX 9  //HM10 RX가 연결된 핀
DHT dht(DHTPIN, DHTTYPE); // DTH객체를 생성합니다.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800); //네오픽셀 스트립 객체를 생성합니다.
SoftwareSerial BTSerial(TX,RX); // 시리얼 통신 객체를 생성합니다.

void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");
  BTSerial.begin(9600);ㄴ
  dht.begin();
  strip.begin();
  strip.show(); 
}

void loop() {
  float h = dht.readHumidity();// 습도를 측정합니다.
  delay(1000);
  Serial.print("Humidity:");
  Serial.println(h);
  if (BTSerial.available()) {
    BTSerial.write(h);
    int data = BTSerial.read();
    Serial.println(data);
    if(data == 49){
      delay(200);
    BTSerial.write("Light ON");
      if(h>55){
        for(uint16_t i=0; i <strip.numPixels(); i++){
          strip.setPixelColor(i, 255,255,255);   
        }
        strip.show();
        Serial.println("흰색");
        BTSerial.write("white");
      }else{
        for(uint16_t i=0; i <strip.numPixels(); i++){
          strip.setPixelColor(i, 0,33,3);   
        }
        strip.show();
        Serial.println("그린");
        BTSerial.write("green");
      }
    }else if(data == 50){
        BTSerial.write("Light OFF");
        strip.clear();
        strip.show();
    }
  }
}
