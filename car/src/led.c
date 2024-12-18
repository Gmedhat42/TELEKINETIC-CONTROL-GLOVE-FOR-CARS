#include "led.h"

void LED_Init(uint gpio_pin)
{
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_OUT);
}

void LED_On(uint gpio_pin)
{
    gpio_put(gpio_pin, 1);
}

void LED_Off(uint gpio_pin)
{
    gpio_put(gpio_pin, 0);
}

void Delay(uint ms)
{
    sleep_ms(ms);
}
