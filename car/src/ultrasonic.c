#include <stdio.h>
#include "ultrasonic.h"

// Function to initialize the ultrasonic sensor
void sensor_init(uint trig_pin, uint echo_pin)
{
    gpio_init(trig_pin);
    gpio_set_dir(trig_pin, GPIO_OUT);
    gpio_put(trig_pin, false);

    gpio_init(echo_pin);
    gpio_set_dir(echo_pin, GPIO_IN);
}

// Function to measure distance using the ultrasonic sensor
float measure_distance(uint trig_pin, uint echo_pin)
{
    gpio_put(trig_pin, false);
    sleep_us(2);

    gpio_put(trig_pin, true);
    sleep_us(10);
    gpio_put(trig_pin, false);

    // Wait for the ECHO pin to go HIGH
    uint32_t start_time = time_us_32();
    while (!gpio_get(echo_pin))
    {
        if (time_us_32() - start_time > 40000) // 40ms timeout
        {
            printf("Timeout waiting for echo start\n");
            return -2.0;
        }
    }

    uint32_t echo_start = time_us_32();

    // Wait for the ECHO pin to go LOW
    while (gpio_get(echo_pin))
    {
        if (time_us_32() - echo_start > 40000) // 40ms timeout
        {
            printf("Timeout waiting for echo end\n");
            return -1.0;
        }
    }

    uint32_t echo_end = time_us_32();
    uint32_t pulse_duration = echo_end - echo_start;

    // printf("Pulse duration: %u us\n", pulse_duration);

    // Calculate distance
    float distance = (pulse_duration * 0.0343) / 2.0;

    if (distance < 2.0 || distance > 400.0) // Check for out-of-range values
    {
        printf("Out of range: %.2f cm\n", distance);
        return -3.0;
    }

    return distance;
}
