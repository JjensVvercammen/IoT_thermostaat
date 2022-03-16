#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char auth[] = "XZ05pFj_TkweR-C2r7Eaq4Vajxgye3rs";
char ssid[] = "telenet-0BB62";
char pass[] = "F8vPuVsXH4P3";

#define DHTPIN 19
#define DHTTYPE DHT11

#define temperatuur V0
#define wanted_temp V1
#define ledje V2

#define led_rood 4

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temp = 0;
float v = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

   Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);

  dht.begin();
  pinMode(led_rood, OUTPUT);
}

void loop() {
  Blynk.run();

  Blynk.virtualWrite(temperatuur, temp);
  Blynk.virtualWrite(wanted_temp, v);
  Blynk.virtualWrite(ledje, led_rood);
  
  delay(100);

  float val = map(analogRead(34), 0, 1023, 100, 300);
  float getal = val / 10;

  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if (t != temp)
  temp = t;
  {    
    delay(100);
    
    Serial.print(F("  Temperature: "));
    Serial.print(t);
    Serial.println("°C");
  
    Serial.print(F("  wanted: "));
    Serial.print(getal);
    Serial.println("");
    

  }

    if(getal > temp -1)
    {
      digitalWrite(led_rood, HIGH);
    }else
    {
      digitalWrite(led_rood, LOW);
    }
   
}
