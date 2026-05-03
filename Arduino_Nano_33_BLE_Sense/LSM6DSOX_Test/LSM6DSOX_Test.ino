/*
  Arduino LSM6DSOX - Simple Accelerometer

  This example reads the acceleration values from the LSM6DSOX
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Nano RP2040 Connect

  created 10 May 2021
  by Arturo Guadalupi

  This example code is in the public domain.
*/

#include <Arduino_LSM6DSOX.h>

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3MDL lis3mdl;

/*
  Convert the Celsius temperature to Fahrenheit

  Returns: (float) temperature in fahrenheit
*/
float to_fahrenheit (float celsius) {
  return celsius * 1.8 + 32;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Found an LSM6DSOX IMU");
  } else {
    Serial.println("Failed to initialize LSM6DSOX IMU!");

    while (true) {
      delay(10);
    };
  }

  if (lis3mdl.begin_I2C()) {
    Serial.println("Found an LIS3MDL Magnetometer");
  } else {
    Serial.println("Failed to find LIS3MDL Magnetometer!");

    while (true) { 
      delay(10);
    }
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in °/sec");

  delay(2000);
}

void loop() {
  sensors_event_t event; 
  float celsius, fahrenheit = 0.0;
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    Serial.print("Accelerometer: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.print(y);
    Serial.print(", z = ");
    Serial.print(z);
    Serial.println(" g");
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print("Gyroscope: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.print(y);
    Serial.print(", z = ");
    Serial.print(z);
    Serial.println(" °/sec");
  }

  if (IMU.temperatureAvailable()) {
    IMU.readTemperatureFloat(celsius);
    fahrenheit = to_fahrenheit(celsius);

    Serial.print("Temperature: ");
    Serial.print(fahrenheit);
    Serial.print(" °F (");
    Serial.print(celsius);
    Serial.println(" °C)");
  }

  lis3mdl.getEvent(&event);

  Serial.print("Magnetometer: x = ");
  Serial.print(event.magnetic.x);
  Serial.print(", y = ");
  Serial.print(event.magnetic.y);
  Serial.print(", z = ");
  Serial.print(event.magnetic.z);
  Serial.println(" uTesla ");

  delay(2000);
}
