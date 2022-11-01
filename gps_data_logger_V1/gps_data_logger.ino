#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

static const int RXPin = 2, TXPin = 3; //i change it myself and it is work
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
//sd card initialization
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
}

void loop()
{
  while (ss.available() > 0)
    
    if (gps.encode(ss.read())){ // gps is avaible 
      File dataFile = SD.open("gps_data.txt", FILE_WRITE);
      Serial.print(F("Location: ")); //location data latitude and longitude avaible
      dataFile.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print("lat= ");Serial.print(gps.location.lat(), 6);
    Serial.print(F(" "));
    Serial.print("long= ");Serial.print(gps.location.lng(), 6);

    dataFile.print("lat= ");dataFile.print(gps.location.lat(), 6);
    dataFile.print(F(" "));
    dataFile.print("long= ");dataFile.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));//location data latitude and longitude not avaible
  }

  if (gps.speed.isValid()) //speed data avaible
  {
    Serial.print("  speed :");Serial.print(gps.speed.kmph());Serial.print(" km/h");
    dataFile.print("  speed :");dataFile.print(gps.speed.kmph());dataFile.print(" km/h");
  }
  else
  {Serial.print("invalid speed");//speed data not avaible
  }
  
  Serial.print(F("  Date: "));//date and time data avaible
  dataFile.print(F("  Date: "));
  if (gps.date.isValid())//date data avaible
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());

    dataFile.print(gps.date.month());
    dataFile.print(F("/"));
    dataFile.print(gps.date.day());
    dataFile.print(F("/"));
    dataFile.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));//date data not avaible
  }
  Serial.print(F("  Time: "));
  dataFile.print(F("  Time: "));
  if (gps.time.isValid())//time data avaible
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour()+3);
    Serial.print(F(":"));
    dataFile.print(gps.time.hour()+3);
    dataFile.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    dataFile.print(gps.time.minute());
    dataFile.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    dataFile.print(gps.time.second());
    dataFile.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
    dataFile.println(gps.time.centisecond());
  }
  else
  {
    Serial.println(F("INVALID"));//time data not avaible
  }
  Serial.println();
  dataFile.close();
    }
    // gps not avaible  
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
