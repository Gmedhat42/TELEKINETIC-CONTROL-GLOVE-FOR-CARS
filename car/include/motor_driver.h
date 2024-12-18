#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define MOTOR_PWM_PIN_A 16
#define MOTOR_PWM_PIN_B 21

#define MOTOR_DIR_PIN_A1 20
#define MOTOR_DIR_PIN_A2 19

#define MOTOR_DIR_PIN_B1 17
#define MOTOR_DIR_PIN_B2 18

void motor_init(void);
void motor_control(uint16_t speed, uint16_t direction);

#endif