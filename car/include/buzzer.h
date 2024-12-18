#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

void BUZZER_Init(uint gpio_pin);
void BUZZER_On(uint gpio_pin);
void BUZZER_Off(uint gpio_pin);

#endif
