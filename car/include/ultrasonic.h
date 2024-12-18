#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include "pico/stdlib.h"

// Function declaration for initializing the sensor
void sensor_init(uint trig_pin, uint echo_pin);

// Function declaration for measuring distance
float measure_distance(uint trig_pin, uint echo_pin);

#endif
