/*
 * VL53L5CX_Minimal.ino
 * Hybrid RobotiX — Arduino Portenta H7
 * Dale Weber <hybotix@hybridrobotix.io>
 *
 * Minimal VL53L5CX example using hybx_vl53l5cx_arduino.
 * Prints 8x8 distance grid to Serial at 115200 baud.
 */

#define HYBX_WIRE Wire1
#include <Wire.h>
#include <hybx_vl53l5cx_arduino.h>

hybx_vl53l5cx_arduino sensor;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("VL53L5CX Minimal Example");

    Wire.begin();
    Wire.setClock(400000);

    if (sensor.begin()) {
      Serial.println("The VL53L5CX Sensor is ready!");
    } else {
      Serial.print("The VL53L5CX Sensor was not found - ");
      Serial.print(" step ");
      Serial.print(hybx_last_error_step);
      Serial.print(" code ");
      Serial.print(hybx_last_error);

      Serial.println(" - Stopping...");
      while (1) {
        delay(10);
      };
    }

    Serial.println("Leaving setup...");
}

void loop() {
    sensor.poll();

    if (!hybx_sensor_ready) return;

    if (hybx_sensor_ready) {
      for (int row = 0; row < 8; row++) {
          for (int col = 7; col >= 0; col--) {
              Serial.print("\t");
              Serial.print(hybx_distance_mm[row][col]);
          }

          Serial.println();
      }
    }

    Serial.println();
    delay(100);
}
