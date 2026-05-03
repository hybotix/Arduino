#ifndef RSHC_PRINT_H
#define RSHC_PRINT_H

/*
*   Function Prototypes
*/
//#include    "Robot_Smart_Home_Controller.h"
#include    "Arduino.h"
#include    "Robot_Definitions.h"

void RSHC_Print(void);
void print_switch_states (uint8_t nr_of_switches=NUMBER_OF_SWITCHES);
void print_uint_16_hex(uint16_t value);
void print_sensor_stat (bool available, String name);
void print_full_sensor_status(System_Sensor_Status *sen_stat);
void bno55_print_event (sensors_event_t* event);
void print_wifi_status(void);

class RSHC_Print {
    Public:
        void RSHC_Print::Utilities(void);
        void print_switch_states (uint8_t nr_of_switches=NUMBER_OF_SWITCHES);
        void print_uint_16_hex(uint16_t value);
        void print_sensor_stat (bool available, String name);
        void print_full_sensor_status(System_Sensor_Status *sen_stat);
        void bno55_print_event (sensors_event_t* event);
        void print_wifi_status(void);
}
#endif