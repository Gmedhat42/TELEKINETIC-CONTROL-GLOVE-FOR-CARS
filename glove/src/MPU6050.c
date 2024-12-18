#include "MPU6050.h"

void mpu6050_init(uint8_t sda_pin, uint8_t scl_pin, uint32_t i2c_speed)
{
    // Initialize I2C with specified pins and speed
    i2c_init(i2c_default, i2c_speed);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    // Reset MPU6050
    uint8_t buf[] = {0x6B, 0x00}; // Reset the power management register
    i2c_write_blocking(i2c_default, MPU6050_ADDR, buf, 2, false);
}

void mpu6050_read_acceleration(int16_t accel[3])
{
    uint8_t buffer[6];
    uint8_t reg = ACCEL_XOUT_H;

    // Request accelerometer data
    i2c_write_blocking(i2c_default, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c_default, MPU6050_ADDR, buffer, 6, false);

    for (int i = 0; i < 3; i++)
    {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }
}

void calculate_pitch_roll(int16_t accel[3], float *pitch, float *roll)
{
    float ax = accel[0] / 16384.0; // Convert raw data to 'g'
    float ay = accel[1] / 16384.0;
    float az = accel[2] / 16384.0;

    *roll = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;
    *pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / M_PI;
}
