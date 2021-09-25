#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 11
#define DHTTYPE    DHT11 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2);
#define moisture_pin A0
int sensorValue;  
int limit = 300; 
DHT dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
void setup() {
 Serial.begin(9600);
 lcd.init();                      
 lcd.begin(16, 2);
 lcd.backlight();
 pinMode(moisture_pin, INPUT);
 dht.begin();
 lcd.setCursor(1,0);
 lcd.print("Plant Monitor");
 delay(5000);
}

void loop() {

 int sensorValue = map(analogRead(moisture_pin), 0, 1023, 100, 0); //read sensor and scale the reading 100% to 0%
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Moisture:");
  lcd.setCursor(10,0);
  lcd.print(sensorValue);
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.setCursor(2,1);
  lcd.print(t);
  lcd.setCursor(9,1);
  lcd.print("H:");
  lcd.setCursor(11,1);
  lcd.print(h);
 delay(5000); 
}
