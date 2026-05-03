/**************************************************************
 *  Function Prototypes
 *************************************************************/
#ifndef FUNCTION_PROTORYPES_H
#define FUNCTION_PROTORYPES_H

#include  "Arduino.h"
#include  "Robot_Definitions.h"

//void blink_rgb (ColorRGB color, uint8_t blink_rate_ms, uint8_t nr_cycles);
void blink_rgb (ColorRGB color, uint8_t blink_rate_ms=DEFAULT_BLINK_RATE_MS, uint8_t nr_cycles=DEFAULT_NR_CYCLES);

#endif