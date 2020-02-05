#include "Adafruit_seesaw.h"
#include <SPI.h>
#include <SD.h>

File myFile;

Adafruit_seesaw ss;

const int chipSelect = 10;

void setup() {
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");

  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while (1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  myFile = SD.open("soil.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("success!");
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening soil.csv");
  }
}

void loop() {
  myFile = SD.open("soil.csv", FILE_WRITE);

  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);

  myFile.print(millis() / 1000);     //record how long the program is running divided by 1000 to make seconds
  myFile.print(",");                 //separate with a comma
  myFile.print(tempC);            //record the random number
  myFile.print(",");
  myFile.println(capread);
  myFile.close();         //close the data file

  delay(1000);
}
