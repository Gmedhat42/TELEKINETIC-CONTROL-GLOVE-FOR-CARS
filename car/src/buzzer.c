#include "buzzer.h"

void BUZZER_Init(uint gpio_pin)
{
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_OUT);
}

void BUZZER_On(uint gpio_pin)
{
    gpio_put(gpio_pin, 1);
}

void BUZZER_Off(uint gpio_pin)
{
    gpio_put(gpio_pin, 0);
}
