/*******************************************************************
    DISPLAY: Begin Data Display and Debug Routines
      Displayed on the Serial Console
*******************************************************************/

#include  "Arduino.h"

#include  "RSHC_Print.h"
#include  "Robot_Definitions.h"

void Print::print_switch_states (uint8_t nr_of_switches=NUMBER_OF_SWITCHES) {
  uint8_t index;

  Serial.print("Switch states: ");

  for (index=0; index < nr_of_switches; index++) {
    Serial.print(SWITCH_NAMES[index]);
    Serial.print(" = ");

    if (SWITCH_READINGS[index]) {
      Serial.print("OFF");
    } else {
      Serial.print("ON");
    }

    if (index < nr_of_switches - 1) {
      Serial.print(", ");
    }
  }

  Serial.println();
}

void Print::print_uint_16_hex(uint16_t value) {
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void Print::print_sensor_stat (bool available, String name) {
  if (available) {
    Serial.println("The " + name + " is available");
  } else {
    Serial.println("The " + name + " is NOT available");
  }
}

void Print::print_full_sensor_status(System_Sensor_Status *sen_stat) {
  Serial.println();
  Serial.println("Sensor availability status:");
  Serial.println("-----------------------------------------------");

  print_sensor_stat(sen_stat->bno055, MUX_BNO055_NAME);
  print_sensor_stat(sen_stat->ens160, MUX_ENS160_NAME);
  print_sensor_stat(sen_stat->lis3mdl, MUX_LIS3MDL_NAME);
  print_sensor_stat(sen_stat->lsm6dsox_6dof, MUX_LSM6DSOX_6DOF_NAME);
  print_sensor_stat(sen_stat->lsm6dsox_9dof, MUX_LSM6DSOX_9DOF_NAME);
  print_sensor_stat(sen_stat->scd40, MUX_SCD40_NAME);
  print_sensor_stat(sen_stat->sht45, MUX_SHT45_NAME);
  print_sensor_stat(sen_stat->veml7700, MUX_VEML7700_NAME);
  Serial.println("-----------------------------------------------");
}

void Print::bno55_print_event (sensors_event_t* event) {
  //  Dumb values, easy to spot any problem
  double x = -1000000, y = -1000000 , z = -1000000;

  if (event->type == SENSOR_TYPE_ACCELEROMETER) {
    Serial.print("Accelerometer: ");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  } else if (event->type == SENSOR_TYPE_ORIENTATION) {
    Serial.print("Orientation: ");
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
  } else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
    Serial.print("Magnetometer: ");
    x = event->magnetic.x;
    y = event->magnetic.y;
    z = event->magnetic.z;
  } else if (event->type == SENSOR_TYPE_GYROSCOPE) {
    Serial.print("Gyroscope: ");
    x = event->gyro.x;
    y = event->gyro.y;
    z = event->gyro.z;
  } else if (event->type == SENSOR_TYPE_ROTATION_VECTOR) {
    Serial.print("Rotation: ");
    x = event->gyro.x;
    y = event->gyro.y;
    z = event->gyro.z;
  } else if (event->type == SENSOR_TYPE_LINEAR_ACCELERATION) {
    Serial.print("Linear: ");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  } else if (event->type == SENSOR_TYPE_GRAVITY) {
    Serial.print("Gravity: ");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  } else {
    Serial.print("Unknown: ");
  }

  Serial.print("x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.print(y);
  Serial.print(", z = ");
  Serial.println(z);
}

/*    
  Print out the connection status:
*/
void Print::print_wifi_status(void) {
  //  Print your board's IP address:
  Serial.print("Connected! IP Address is ");
  Serial.println(WiFi.localIP());

  //  Print the received signal strength:
  Serial.print("Signal strength (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

/*******************************************************************
    FORMATTING: Begin Data Formatting routines
********************************************************************/

/*
  Return the HTML for the switches and their states (ON or OFF)
*/
String Print::format_switch_html (uint8_t nr_of_switches=NUMBER_OF_SWITCHES) {
  uint8_t index;
  String html = "", state;

  for (index=0; index < nr_of_switches; index++) {
    if (SWITCH_READINGS[index]) {
      state ="<SPAN style=\"color: magenta\">OFF</SPAN>";
    } else {
      state = "<SPAN style=\"color: green\">ON</SPAN>";
    }

    html = html + "<SPAN style=\"color: yellow\">" + SWITCH_NAMES[index] + "</SPAN> = " + state;

    if (index < nr_of_switches - 1) {
      html = html + ", ";
    }
  }

  return html;
}

/*
  Format the X, Y, and Z readings for output
*/
String Print::format_imu_xyz_html (Three_Axis readings) {
  return "<SPAN STYLE=\"color: yellow\">x</SPAN> = <SPAN STYLE=\"color: green\">" + String(readings.x) + "</SPAN>, <SPAN STYLE=\"color: yellow\">y</SPAN> = <SPAN STYLE=\"color: green\">" + String(readings.y) + "</SPAN>, <SPAN STYLE=\"color: yellow\">z</SPAN> = <SPAN STYLE=\"color: green\">" + String(readings.z) + "</SPAN>";
}

/*******************************************************************
    FORMATTING: End of Data Formatting routines
********************************************************************/
