#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht11.h>
//pins
#define HUM_PIN 4
#define GPU_ADRR 0x27
#define t 1500
#define GAS A0

//appr 30ppm == 0.3 F

//globals
LiquidCrystal_I2C lcd(GPU_ADRR, 16, 2);
char HUMID_VALS;
short temps;



//MQ135 sens = MQ135(GAS);
dht11 hum;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Syncing...");
  delay(5);
  lcd.clear();
  lcd.home();
  
}

void loop()
{
  hum.read(HUM_PIN);
  lcd.home();
  lcd.print("Humidity:       ");
  lcd.setCursor(0, 1);
  lcd.print((byte) hum.humidity);
  lcd.print("%         ");
  
  delay(t);

  lcd.home();
  lcd.print("Temprature:     ");
  lcd.setCursor(0, 1);
  lcd.print((float)hum.temperature);
  lcd.print(" C    ");

  delay(t);

  lcd.home();
  lcd.print("Air quality:    ");
  lcd.setCursor(0, 1);
  lcd.print(getVals());
  lcd.print(" PPM    ");

  delay(t);
}

float getVals(){
  return (analogRead(GAS) * 0.004882814) * 1000;   //math stuf xd4
}