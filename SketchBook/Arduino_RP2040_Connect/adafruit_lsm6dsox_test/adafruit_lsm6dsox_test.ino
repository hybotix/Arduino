/*
  Basic demo for accelerometer & gyro readings from Adafruit
  LSM6DSOX sensor
*/

#include <Adafruit_LSM6DSOX.h>

Adafruit_LSM6DSOX sox;

/**********************
  Utility routines
**********************/

/*
  Blink the onboard RGB LED with the selected color

  Parameters:
    color:          a ColorRGB structure that defines the desired color
    blink_rate_ms:  The blink rate in ms
    nr_cycles:      The number of times to blink the LED

  Returns:          void
*/
void blink_rgb (ColorRGB color, uint8_t blink_rate_ms=DEFAULT_BLINK_RATE_MS, uint8_t nr_cycles=DEFAULT_NR_CYCLES) {
  uint8_t count;

  for (count=0; count<nr_cycles; count++) {
    digitalWrite(LEDR, color.redB);
    digitalWrite(LEDG, color.greenB);
    digitalWrite(LEDB, color.blueB);

    delay(blink_rate_ms);

    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    delay(blink_rate_ms);
  }
}

/*
  Blink a standard LED on the selected pin.
  Pins are active LOW

  Parameters:
    pin:            The pin the LED is connected to
    blink_rate_ms:  The blink rate in ms
    nr_cycles:      The number of times to blink the LED

  Returns:          void
*/
void blink_led_c33 (uint8_t pin, uint8_t blink_rate_ms=DEFAULT_BLINK_RATE_MS, uint8_t nr_cycles=DEFAULT_NR_CYCLES) {
  uint8_t index;

  for (index=0; index < nr_cycles; index++) {
    //  Turn the LED ON
    digitalWrite(pin, LOW);
    delay(blink_rate_ms);
      
    //  Turn the LED OFF
    digitalWrite(pin, HIGH);
    delay(blink_rate_ms);
  }
}

/*
  Blink a standard LED on the selected Raspberry Pi pin.
  Pins are active HIGH

  Parameters:
    pin:            The pin the LED is connected to
    blink_rate_ms:  The blink rate in ms
    nr_cycles:      The number of times to blink the LED

  Returns:          void
*/
void blink_led_raspi (uint8_t pin, uint8_t blink_rate_ms=DEFAULT_BLINK_RATE_MS, uint8_t nr_cycles=DEFAULT_NR_CYCLES) {
  uint8_t index;

  for (index=0; index < nr_cycles; index++) {
    //  Turn the LED ON
    digitalWrite(pin, HIGH);
    delay(blink_rate_ms);
      
    //  Turn the LED OFF
    digitalWrite(pin, LOW);
    delay(blink_rate_ms);
  }
}

/*
  Halt everything - used for unrecoverable errors

  Parameters:
    message:    The message to disaplay on the serial console
    wifi_halt:  If this is a WiFi connection halt, true
    wifi_ssid:  If wifi_halt is true, this should be the SSID of the WiFi network

  Returns:      void
*/
void halt (String message, bool wifi_halt=false, char *wifi_ssid=ssid) {
  Serial.println();
  Serial.println(message);

  if (wifi_halt) {
    Serial.print(" ");
    Serial.print(wifi_ssid);
  }

  //  Turn off all other status LEDs
  digitalWrite(LED_RASPI_WIFI_PIN, LOW);
  digitalWrite(LED_RASPI_CONNECT_PIN, LOW);

  //  Infinite loop
  while (true) {
    blink_led_raspi(LED_RASPI_HALT_PIN);
    delay(100);
  }
}

/*
  Convert the Celsius temperature to Fahrenheit

  Returns: (float) temperature in fahrenheit
*/
float to_fahrenheit (float celsius) {
  return celsius * 1.8 + 32;
}

void setup (void) {
  Serial.begin(115200);

  while (!Serial) {
    //  will pause until the serial console opens
    delay(10);
  }

  Serial.println("Adafruit LSM6DSOX test!");
  Seial.println();

  if (sox.begin_I2C()) {
    Serial.println("The LSM6DSOX was Found!");

    sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);

    Serial.print("Accelerometer range set to: ");

    switch (sox.getAccelRange()) {
      case LSM6DS_ACCEL_RANGE_2_G:
        Serial.println("+-2G");
        break;
      case LSM6DS_ACCEL_RANGE_4_G:
        Serial.println("+-4G");
        break;
      case LSM6DS_ACCEL_RANGE_8_G:
        Serial.println("+-8G");
        break;
      case LSM6DS_ACCEL_RANGE_16_G:
        Serial.println("+-16G");
        break;
    }

    sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );

    Serial.print("Gyro range set to: ");

    switch (sox.getGyroRange()) {
      case LSM6DS_GYRO_RANGE_125_DPS:
        Serial.println("125 degrees/s");
        break;
      case LSM6DS_GYRO_RANGE_250_DPS:
        Serial.println("250 degrees/s");
        break;
      case LSM6DS_GYRO_RANGE_500_DPS:
        Serial.println("500 degrees/s");
        break;
      case LSM6DS_GYRO_RANGE_1000_DPS:
        Serial.println("1000 degrees/s");
        break;
      case LSM6DS_GYRO_RANGE_2000_DPS:
        Serial.println("2000 degrees/s");
        break;
      case ISM330DHCX_GYRO_RANGE_4000_DPS:
        break; // unsupported range for the DSOX
    }

    sox.setAccelDataRate(LSM6DS_RATE_12_5_HZ);

    Serial.print("Accelerometer data rate set to: ");

    switch (sox.getAccelDataRate()) {
      case LSM6DS_RATE_SHUTDOWN:
        Serial.println("0 Hz");
        break;
      case LSM6DS_RATE_12_5_HZ:
        Serial.println("12.5 Hz");
        break;
      case LSM6DS_RATE_26_HZ:
        Serial.println("26 Hz");
        break;
      case LSM6DS_RATE_52_HZ:
        Serial.println("52 Hz");
        break;
      case LSM6DS_RATE_104_HZ:
        Serial.println("104 Hz");
        break;
      case LSM6DS_RATE_208_HZ:
        Serial.println("208 Hz");
        break;
      case LSM6DS_RATE_416_HZ:
        Serial.println("416 Hz");
        break;
      case LSM6DS_RATE_833_HZ:
        Serial.println("833 Hz");
        break;
      case LSM6DS_RATE_1_66K_HZ:
        Serial.println("1.66 KHz");
        break;
      case LSM6DS_RATE_3_33K_HZ:
        Serial.println("3.33 KHz");
        break;
      case LSM6DS_RATE_6_66K_HZ:
        Serial.println("6.66 KHz");
        break;
    }

    sox.setGyroDataRate(LSM6DS_RATE_12_5_HZ);

    Serial.print("Gyro data rate set to: ");

    switch (sox.getGyroDataRate()) {
      case LSM6DS_RATE_SHUTDOWN:
        Serial.println("0 Hz");
        break;
      case LSM6DS_RATE_12_5_HZ:
        Serial.println("12.5 Hz");
        break;
      case LSM6DS_RATE_26_HZ:
        Serial.println("26 Hz");
        break;
      case LSM6DS_RATE_52_HZ:
        Serial.println("52 Hz");
        break;
      case LSM6DS_RATE_104_HZ:
        Serial.println("104 Hz");
        break;
      case LSM6DS_RATE_208_HZ:
        Serial.println("208 Hz");
        break;
      case LSM6DS_RATE_416_HZ:
        Serial.println("416 Hz");
        break;
      case LSM6DS_RATE_833_HZ:
        Serial.println("833 Hz");
        break;
      case LSM6DS_RATE_1_66K_HZ:
        Serial.println("1.66 KHz");
        break;
      case LSM6DS_RATE_3_33K_HZ:
        Serial.println("3.33 KHz");
        break;
      case LSM6DS_RATE_6_66K_HZ:
        Serial.println("6.66 KHz");
        break;
    }
  } else {
    Serial.println("Failed to find the LSM6DSOX IMU!");

    while (true) {
      delay(10);
    }
  }
}

void loop(void) {
  float celsius, fahrenheit;
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  /*
    Get a new normalized sensor event
  */
  sox.getEvent(&accel, &gyro, &temp);

  celsius = temp.temperature;
  fahrenheit = to_fahrenheit(celsius);

  Serial.print("Temperature = ");
  Serial.print(fahrenheit);
  Serial.println(" °F (");
  Serial.print(celsius);
  Serial.println(" °C)");

  /*
    Display the results (acceleration is measured in m/s^2)
  */
  Serial.print("Accelerometer X = ");
  Serial.print(accel.acceleration.x);
  Serial.print(", Y = ");
  Serial.print(accel.acceleration.y);
  Serial.print(", Z = ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");

  /*
    Display the results (rotation is measured in rad/s)
  */
  Serial.print("Gyroscope X = ");
  Serial.print(gyro.gyro.x);
  Serial.print(", Y = ");
  Serial.print(gyro.gyro.y);
  Serial.print(", Z = ");
  Serial.print(gyro.gyro.z);
  Serial.println(" radians/s ");
  Serial.println();

  delay(100);

  /*
    Serial plotter friendly format
  */

/*
  Serial.print(temp.temperature);
  Serial.print(",");

  Serial.print(accel.acceleration.x);
  Serial.print(",");
  Serial.print(accel.acceleration.y);
  Serial.print(",");
  Serial.print(accel.acceleration.z);
  Serial.print(",");

  Serial.print(gyro.gyro.x);
  Serial.print(",");
  Serial.print(gyro.gyro.y);
  Serial.print(",");
  Serial.print(gyro.gyro.z);
  Serial.println();
  delayMicroseconds(10000);
*/
}