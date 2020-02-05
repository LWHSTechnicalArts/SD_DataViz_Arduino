/******************************************************************************
  Read basic CO2 and TVOCs

  Marshall Taylor @ SparkFun Electronics
  Nathan Seidle @ SparkFun Electronics
  SD features added by A. Kleindolph Sp2020

  April 4, 2017

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library

  Read the TVOC and CO2 values from the SparkFun CSS811 breakout board

  A new sensor requires at 48-burn in. Once burned in a sensor requires
  20 minutes of run in before readings are considered good.

  Hardware Connections (Breakoutboard to Arduino):
  3.3V to 3.3V pin
  GND to GND pin
  SDA to A4
  SCL to A5

******************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "SparkFunCCS811.h" //Click here to get the library: http://librarymanager/All#SparkFun_CCS811

#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 mySensor(CCS811_ADDR);

File myFile;
const int chipSelect = 10;

void setup()
{
  Serial.begin(115200);
  Serial.println("CCS811 Basic Example");

  Wire.begin(); //Inialize I2C Hardware

  if (mySensor.begin() == false)
  {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
    while (1);
  }

  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("co2.csv", FILE_WRITE);

  if (myFile) {
    Serial.println("success!");
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening co2.csv");
  }
}

void loop()
{
  myFile = SD.open("co2.csv", FILE_WRITE);
  
  //Check to see if data is ready with .dataAvailable()
  if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    mySensor.readAlgorithmResults();

    Serial.print("CO2[");
    //Returns calculated CO2 reading
    Serial.print(mySensor.getCO2());
    Serial.print("] tVOC[");
    //Returns calculated TVOC reading
    Serial.print(mySensor.getTVOC());
    Serial.print("] seconds[");
    //Display the time since program start
    Serial.print(millis()/1000);
    Serial.print("]");
    Serial.println();

    myFile.print(mySensor.getCO2());
    myFile.print(",");
    myFile.print(mySensor.getTVOC());
    myFile.print(",");
    myFile.println(millis()/1000);
  }

  delay(1000); //Don't spam the I2C bus
  myFile.close();         //close the data file
}
