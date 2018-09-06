//***************************************************************************//
#include <Wire.h>
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 (default)
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
// see here for info: https://www.youtube.com/watch?v=Wj_BBSsfNRg

/*===CO2===========================================*/
#include "MQ135.h"

#define CO2PIN_A0 1
#define CO2PIN_D0 4
MQ135 mq135(CO2PIN_A0); 

/*===Moisture,Temp,Humidity========================*/
#include "DHT.h"

//#define MOISTUREPIN A0
#define DHTPIN 7 
#define DHTTYPE DHT22   // DHT 11 or 22
DHT dht(DHTPIN, DHTTYPE);

/*===Relays=======================================*/
#define RELAY1  8      // Relay to start the first heater
#define RELAY2  9      // Relay to start the second heater
#define RELAY3  10     //Relay to start the humidifier
#define RELAY4  11     //Relay to start air pump


/*****************************/
/*set Triggers *************/
float h_trig = 90;
float t_trig  = 26; 
float C02_trig = 800; 
/*****************************/


//***************************************************************************//
void setup() {
//***************************************************************************//

  // initialize LCD library
  lcd.begin(16,2);

  // declare CO2 sensor 
  pinMode(CO2PIN_D0, INPUT);


  // start DHT22 
  Serial.begin(115200);  
  dht.begin();

  // declare pins as output
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

}

//***************************************************************************// 
void loop() {
//***************************************************************************//
   
  // read analog sensors:
  //  int m = analogRead(MOISTUREPIN);
  float co2 = mq135.getPPM();
  int co2_uncor = analogRead(CO2PIN_A0);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();

  // set relay based on readings
/*
    if (h < h_trig ) {
      digitalWrite(RELAY1, LOW); }
    if (h > h_trig ) {
      digitalWrite(RELAY1, HIGH);}
*/
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

    if (t > (t_trig + 2) ) { // 2 deg c buffer
      digitalWrite(RELAY2, LOW);
      }
    if (t < (t_trig - 2) ) { //2 deg c buffer
        digitalWrite(RELAY2, HIGH);
      }
/*
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
*/
  //corrected for t&h CO2 ppm:
  float co2_cor = mq135.getCorrectedPPM(t, h);

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

Serial.print(h);
Serial.print(" , ");
Serial.print(t);
Serial.print(" , ");
Serial.print(hic);
Serial.print(" , ");
//Serial.print(m);
//Serial.print(" , ");
//Serial.print(co2);
//Serial.print(" , ");
//Serial.print(co2_cor);
//Serial.print(" , ");
Serial.println(co2_uncor);

  lcd.setCursor(0,0);
  lcd.print("T=");
  lcd.print(t,1);
  lcd.print((char)223); //degree symbol
  lcd.print("C/H=");
  lcd.print(h,1);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("CO2= ");
  lcd.print(co2_uncor);
  lcd.print("PPM");

delay(2500); //Pause between readings.

}
