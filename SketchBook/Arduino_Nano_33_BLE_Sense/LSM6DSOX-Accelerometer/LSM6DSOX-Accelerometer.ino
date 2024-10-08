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

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
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
  Serial.println("Gyroscope in degrees/second");

  delay(2000);
}

void loop() {
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

    delay(2000);
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print("Gyroscope: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.print(y);
    Serial.print(", z = ");
    Serial.print(z);
    Serial.println(" °/s");
  }
}
