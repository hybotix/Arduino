/*
  Read an 8x8 array of distances from the VL53L5CX
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 26, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to read all 64 distance readings at once.

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/18642

*/

#include <Wire.h>

#include <SparkFun_VL53L5CX_Library.h> //http://librarymanager/All#SparkFun_VL53L5CX

SparkFun_VL53L5CX myImager;
VL53L5CX_ResultsData measurementData; // Result data class structure, 1356 byes of RAM

int imageResolution = 0; //Used to pretty print output
int imageWidth = 0; //Used to pretty print output

uint32_t looper = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("SparkFun VL53L5CX Imager Example");

  Wire.begin(); //This resets to 100kHz I2C
  Wire.setClock(400000); //Sensor has max I2C freq of 400kHz 
  myImager.setWireMaxPacketSize(128);  // ← Add this
 
  if (myImager.begin()) {
    Serial.println("Found the VL53L5CX sensor!");
  } else {
    Serial.println(F("The VL53L5CX was not found - Check your wiring. Freezing"));
    while (1) ;
  }
  
  Serial.println("Initializing sensor board. This can take up to 10s. Please wait.");

  myImager.setResolution(8*8); //Enable all 64 pads
  
  imageResolution = myImager.getResolution(); //Query sensor for current resolution - either 4x4 or 8x8
  imageWidth = sqrt(imageResolution); //Calculate printing width

  myImager.startRanging();

  Serial.println("Exiting the setup()");
}

void loop() {
  looper += 1;

  //Serial.print("Loop #");
  //Serial.print(looper);
  //Serial.println();

  //Poll sensor for new data
  if (myImager.isDataReady() == true) {
    if (myImager.getRangingData(&measurementData)) { //Read distance data into array
  
      //The ST library returns the data transposed from zone mapping shown in datasheet
      //Pretty-print data with increasing y, decreasing x to reflect reality
      for (int y = 0 ; y <= imageWidth * (imageWidth - 1) ; y += imageWidth) {
        for (int x = imageWidth - 1 ; x >= 0 ; x--) {
          Serial.print("\t");
          Serial.print(measurementData.distance_mm[x + y]);
        }

        Serial.println();
      }
      
      Serial.println();
    }
  }

  delay(5); //Small delay between polling
}
