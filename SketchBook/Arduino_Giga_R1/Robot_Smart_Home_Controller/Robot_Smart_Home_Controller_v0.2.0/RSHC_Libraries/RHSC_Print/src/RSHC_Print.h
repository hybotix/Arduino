#ifndef RSHC_PRINT_H
#define RSHC_PRINT_H

#include  <Arduino.h>

#include  "Robot_Definitions.h"

class print {

public:
  void print_sensor_stat (bool available, String name);
  void print_uint_16_hex(uint16_t value);
  void print_sensor_stat (bool available, String name);
  void print_full_sensor_status(System_Sensor_Status *sen_stat);
  void bno55_print_event (sensors_event_t* event);

  void print_wifi_status(void);
}

#endif