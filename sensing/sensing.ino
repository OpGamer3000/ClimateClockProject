#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht11.h>
//pins
#define HUM_PIN 4
#define GPU_ADRR 0x27
#define t 1500
#define mqInput A1 //sensor input PIN

//appr 30ppm == 0.3 F

//globals
LiquidCrystal_I2C lcd(GPU_ADRR, 16, 2);
char HUMID_VALS;
short temps;


//pull-down resistor value
int mqR = 22000;
//rO sensor value
long rO = 41763;
//min value for Rs/Ro
float minRsRo = 0.358;
//max value for Rs/Ro
float maxRsRo = 2.428;
//sensor a coefficient value
float a = 116.6020682;
//sensor b coefficient value
float b = -2.769034857;


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
  pinMode(mqInput, INPUT);
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
  getVals();
  lcd.print(" PPM    ");

  delay(t);
}

void getVals() {
  int adcRaw = analogRead(mqInput);
  long rS = ((1024.0 * mqR) / adcRaw) - mqR;
  float rSrO = (float)rS / (float)rO;

  if(rSrO < maxRsRo && rSrO > minRsRo) {
    float ppm = a * pow((float)rS / (float)rO, b);
    Serial.print("ppm: ");
    Serial.println(ppm);
    lcd.print(ppm);
  } else {
    Serial.println("Out of range.");
  }  
  
  delay(1000);
}