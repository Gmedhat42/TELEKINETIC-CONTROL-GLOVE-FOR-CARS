#include "motor_driver.h"

void motor_init(void)
{
    // Initialize the DIR pins
    gpio_init(MOTOR_DIR_PIN_A1);
    gpio_init(MOTOR_DIR_PIN_A2);
    gpio_init(MOTOR_DIR_PIN_B1);
    gpio_init(MOTOR_DIR_PIN_B2);

    // Set the direction pins as output
    gpio_set_dir(MOTOR_DIR_PIN_A1, GPIO_OUT);
    gpio_set_dir(MOTOR_DIR_PIN_A2, GPIO_OUT);
    gpio_set_dir(MOTOR_DIR_PIN_B1, GPIO_OUT);
    gpio_set_dir(MOTOR_DIR_PIN_B2, GPIO_OUT);

    // Initialize the PWM pins
    gpio_set_function(MOTOR_PWM_PIN_A, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_PWM_PIN_B, GPIO_FUNC_PWM);

    // Set the PWM wrap value
    uint slice_num_a = pwm_gpio_to_slice_num(MOTOR_PWM_PIN_A);
    uint slice_num_b = pwm_gpio_to_slice_num(MOTOR_PWM_PIN_B);
    pwm_set_wrap(slice_num_a, 255);
    pwm_set_wrap(slice_num_b, 255);

    pwm_set_clkdiv(slice_num_a, 4.0f);
    pwm_set_clkdiv(slice_num_b, 4.0f);

    pwm_set_enabled(slice_num_a, true);
    pwm_set_enabled(slice_num_b, true);
}

void motor_control(uint16_t speed, uint16_t direction)
{
    if (speed > 255)
    {
        speed = 255;
    }

    if (direction == 1) // RIGHT
    {
        gpio_put(MOTOR_DIR_PIN_A1, 1);
        gpio_put(MOTOR_DIR_PIN_A2, 0);
        gpio_put(MOTOR_DIR_PIN_B1, 1);
        gpio_put(MOTOR_DIR_PIN_B2, 0);
    }
    else if (direction == 2) // LEFT
    {
        gpio_put(MOTOR_DIR_PIN_A1, 0);
        gpio_put(MOTOR_DIR_PIN_A2, 1);
        gpio_put(MOTOR_DIR_PIN_B1, 0);
        gpio_put(MOTOR_DIR_PIN_B2, 1);
    }
    else if (direction == 3) // FORWARD
    {
        gpio_put(MOTOR_DIR_PIN_A1, 1);
        gpio_put(MOTOR_DIR_PIN_A2, 0);
        gpio_put(MOTOR_DIR_PIN_B1, 0);
        gpio_put(MOTOR_DIR_PIN_B2, 1);
    }
    else if (direction == 4) // BACKWARD
    {
        gpio_put(MOTOR_DIR_PIN_A1, 0);
        gpio_put(MOTOR_DIR_PIN_A2, 1);
        gpio_put(MOTOR_DIR_PIN_B1, 1);
        gpio_put(MOTOR_DIR_PIN_B2, 0);
    }
    else // STOP
    {
        gpio_put(MOTOR_DIR_PIN_A1, 0);
        gpio_put(MOTOR_DIR_PIN_A2, 0);
        gpio_put(MOTOR_DIR_PIN_B1, 0);
        gpio_put(MOTOR_DIR_PIN_B2, 0);
    }

    pwm_set_gpio_level(MOTOR_PWM_PIN_A, speed);
    pwm_set_gpio_level(MOTOR_PWM_PIN_B, speed);
}