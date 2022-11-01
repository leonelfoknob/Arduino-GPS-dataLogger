#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const int chipSelect = 4;

static const int RXPin = 2, TXPin = 3; //i change it myself and it is work
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

int vol_in = A0;
float voltmeter;

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);

}

void loop()
{
  while (ss.available() > 0)
    
    if (gps.encode(ss.read())){ // gps is avaible 
      Serial.print(F("Location: ")); //location data latitude and longitude avaible
  if (gps.location.isValid())
  {
    Serial.print("lat= ");Serial.print(gps.location.lat(), 6);
    Serial.print(F(" "));
    Serial.print("long= ");Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));//location data latitude and longitude not avaible
  }

  if (gps.speed.isValid()) //speed data avaible
  {
    Serial.print("  speed :");Serial.print(gps.speed.kmph());Serial.print(" km/h");}
  else
  {Serial.print("invalid speed");//speed data not avaible
  }
  
  Serial.print(F("  Date: "));//date and time data avaible
  if (gps.date.isValid())//date data avaible
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));//date data not avaible
  }
  Serial.print(F("  Time: "));
  if (gps.time.isValid())//time data avaible
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour()+3);
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
    
    lcd.setCursor(4, 0);
    lcd.print(gps.time.hour()+3);
    lcd.print(" ");
    lcd.setCursor(6, 0);
    lcd.print(":");
    lcd.setCursor(7, 0);
    lcd.print(gps.time.minute());
    lcd.print(" ");
    lcd.setCursor(9, 0);
    lcd.print(":");
    lcd.setCursor(10, 0);
    lcd.print(gps.time.second());
    lcd.print(" ");

    /*lcd.setCursor(3, 1);
    lcd.print("Leo Hours");*/
    
  }
  else
  {
    Serial.println(F("INVALID"));//time data not avaible
    lcd.setCursor(1, 0);
    lcd.print("00");
    lcd.setCursor(3, 0);
    lcd.print(":");
    lcd.setCursor(4, 0);
    lcd.print("00");
    lcd.setCursor(7, 0);
    lcd.print(":");
    lcd.setCursor(8, 0);
    lcd.print("00");
  }
  Serial.println();
    }
    // gps not avaible  
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  
  voltmeter = (analogRead(vol_in) * 5.0) / 1024.0; 
  lcd.setCursor(0, 1);
  lcd.print("Volts : ");
  lcd.setCursor(8, 1);
  lcd.print(voltmeter);
  lcd.print("  ");
}
