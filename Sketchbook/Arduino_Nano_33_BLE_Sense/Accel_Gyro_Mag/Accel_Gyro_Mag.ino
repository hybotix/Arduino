/*
  Arduino BMI270 - Simple Accelerometer

  This example reads the acceleration values from the BMI270
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Nano 33 BLE Sense Rev2

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino.h>
#include "Arduino_BMI270_BMM150.h"
#include <math.h>

#define CONFIDENCE_PERCENT  (0.5)
#define SAMPLERATE_DELAY_MS (1000)

float accel_x_M, accel_y_M, accel_z_M = 0.0;

//  Accelerometer variables
float a_thetaM, a_phiM = 0.0;
float a_thetaF, a_thetaFold, a_thetaFnew = 0.0;
float a_phiF, a_phiFold, a_phiFnew = 0.0;

float a_rollM, a_rollF, a_rollFold, a_rollFnew = 0.0;
float a_pitchM, a_pitchF, a_pitchFold, a_pitchFnew = 0.0;
float a_rollMnew, a_rollMold, a_pitchMnew, a_pitchMold = 0.0;

//  Gyroscope variables
float gyro_x_M, gyro_y_M, gyro_z_M = 0.0;

float g_thetaM, g_phiM = 0.0;
float g_thetaF, g_thetaFold, g_thetaFnew = 0.0;
float g_phiF, g_phiFold, g_phiFnew = 0.0;

float g_rollM, g_rollF, g_rollFold, g_rollFnew = 0.0;
float g_pitchM, g_pitchF, g_pitchFold, g_pitchFnew = 0.0;
float g_rollMnew, g_rollMold, g_pitchMnew, g_pitchMold = 0.0;
float g_dt = 0.0;

//  Magnetometer variables
float mag_x_M, mag_y_M, mag_z_M = 0.0;

/******************************************************
  Functions
******************************************************/

float radians_to_degrees (float radians) {
  return radians / 2 / PI * 360;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize t IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println("Acceleration in G's");

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println("Gyroscope in degrees/second");

  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" Hz");
  Serial.println("Magnetic Field in uT");

  Serial.println();
  delay(5000);
}

void loop() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accel_x_M, accel_y_M, accel_z_M);

    accel_x_M /= 9.8;
    accel_y_M /= 9.8;
    accel_z_M /= 9.8;

    Serial.print("Accelerometer: x = ");
    Serial.print(accel_x_M);
    Serial.print(", y = ");
    Serial.print(accel_y_M);
    Serial.print(", z = ");
    Serial.println(accel_z_M);

    a_thetaM = atan2(accel_x_M, accel_z_M) / 2 / PI * 360;
    a_thetaFnew = (CONFIDENCE_PERCENT * a_thetaFold) + ((1 - CONFIDENCE_PERCENT) * a_thetaM);

    a_phiM = -atan2(accel_y_M, accel_z_M) / 2 / PI * 360;
    a_phiFnew = (CONFIDENCE_PERCENT * a_phiFold) + ((1 - CONFIDENCE_PERCENT) * a_phiM);

    a_rollMnew = -atan(accel_y_M / sqrt(pow(accel_x_M, 2) + pow(accel_z_M, 2))) * 180 / PI;
    a_pitchMnew = -atan(-1 - accel_x_M / sqrt(pow(accel_y_M, 2) + pow(accel_z_M, 2))) * 180 / PI;

    Serial.print("thetaM = ");
    Serial.print(a_thetaM);
    Serial.print("°, thetaFold = ");
    Serial.print(a_thetaFold);
    Serial.print("°, thetaFnew = ");
    Serial.print(a_thetaFnew);
    Serial.println("°");

    Serial.print("phiM = ");
    Serial.print(a_phiM);
    Serial.print("°, phiFnold = ");
    Serial.print(a_phiFold);
    Serial.print("°, phiFnew = ");
    Serial.print(a_phiFnew);
    Serial.println("°");

    Serial.print("rollMnew = ");
    Serial.print(a_rollMnew);
    Serial.print("°, rollFnew = ");
    Serial.print(a_rollFnew);
    Serial.println("°");

    Serial.print("pitchMnew = ");
    Serial.print(a_pitchMnew);
    Serial.print("°, pitchFnew = ");
    Serial.print(a_pitchFnew);
    Serial.println("°");
  
    /*
      Save current values for the next loop
    */ 
    a_phiFold = a_phiFnew;
    a_thetaFold = a_thetaFnew;
    a_rollFold = a_rollFnew;
    a_pitchFold = a_pitchFnew;
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyro_x_M, gyro_y_M, gyro_z_M);

    Serial.print("Gyroscope: x = ");
    Serial.print(gyro_x_M);
    Serial.print(", y =");
    Serial.print(gyro_y_M);
    Serial.print(", z = ");
    Serial.println(gyro_z_M);


  }

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(mag_x_M, mag_y_M, mag_z_M);

    Serial.print("Magnetometer: x = ");
    Serial.print(mag_x_M);
    Serial.print(", ");
    Serial.print(mag_y_M);
    Serial.print(", ");
    Serial.println(mag_z_M);
  }

  Serial.println();
  
  delay(SAMPLERATE_DELAY_MS); 
}