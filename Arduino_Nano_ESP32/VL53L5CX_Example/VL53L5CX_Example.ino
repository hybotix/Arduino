/*
 * VL53L5CX_Example.ino
 * Hybrid RobotiX — Arduino Nano ESP32
 * Dale Weber <hybotix@hybridrobotix.io>
 *
 * Read an 8x8 array of distances from the VL53L5CX using hybx_vl53l5cx_arduino.
 * Converted from SparkFun example by Nathan Seidle.
 *
 * Prints distance_mm as an 8x8 grid to Serial at 115200 baud.
 */

#include <Wire.h>
#include <hybx_vl53l5cx_arduino.h>

static hybx_vl53l5cx_arduino sensor;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("hybx_vl53l5cx_arduino — VL53L5CX Example");

    Wire.begin();
    Wire.setClock(400000);  // Sensor max I2C: 400kHz

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

    // Print 8x8 distance grid — Y-axis flipped to match physical orientation
    for (int row = 0; row < 8; row++) {
        for (int col = 7; col >= 0; col--) {
            Serial.print("\t");
            Serial.print(hybx_distance_mm[row][col]);
        }
        Serial.println();
    }
    Serial.println();

    delay(5);
}
