#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>
#include <math.h>
#include "hardware/i2c.h"
#include "pico/stdlib.h"

// MPU6050 I2C Address and Register Definitions
#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B

// Function Prototypes
void mpu6050_init(uint8_t sda_pin, uint8_t scl_pin, uint32_t i2c_speed);
void mpu6050_read_acceleration(int16_t accel[3]);
void calculate_pitch_roll(int16_t accel[3], float *pitch, float *roll);

#endif // MPU6050_H
