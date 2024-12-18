#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

void LED_Init(uint gpio_pin);
void LED_On(uint gpio_pin);
void LED_Off(uint gpio_pin);
void Delay(uint ms);

#endif
