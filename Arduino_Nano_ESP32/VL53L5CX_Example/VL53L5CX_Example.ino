/*
 * VL53L5CX_Example.ino
 * Hybrid RobotiX — Arduino Nano ESP32
 * Dale Weber <hybotix@hybridrobotix.io>
 *
 * Read an 8x8 array of distances from the VL53L5CX using hybx_vl53l5cx_arduino_full.
 * Prints distance_mm as an 8x8 grid to Serial at 115200 baud.
 */

#include <Wire.h>
#include <hybx_vl53l5cx_arduino_full.h>

static hybx_vl53l5cx_arduino_full sensor;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("hybx_vl53l5cx_arduino_full — VL53L5CX Example");

    Wire.begin();
    Wire.setClock(400000);

    Serial.println("Initializing sensor — firmware upload up to 30s. Please wait.");

    if (!sensor.begin()) {
        Serial.print("ERROR: init failed — step ");
        Serial.print(hybx_last_error_step);
        Serial.print(" code ");
        Serial.println(hybx_last_error);
        while (1);
    }

    Serial.println("Sensor ready. Resolution: 8x8");
}

void loop() {
    sensor.poll();

    if (!hybx_sensor_ready) return;

    // Distance grid
    for (int row = 0; row < 8; row++) {
        for (int col = 7; col >= 0; col--) {
            Serial.print("\t");
            Serial.print(hybx_distance_mm[row][col]);
        }
        Serial.println();
    }

    // Motion indicator
    Serial.print("Motion: ");
    Serial.print(hybx_motion.global_indicator_1);
    Serial.print(" / ");
    Serial.println(hybx_motion.global_indicator_2);

    Serial.println();

    delay(5);
}
