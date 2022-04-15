/* 
    Main Project
    author: Debora Fernandes e Matheus Gois
    description: control occhi
*/

#include <stdio.h>
#include "led.h"

static const char *TAG = "LED OCCHI";

void set_state_led(led_rgb *led, uint8_t state)
{
    gpio_set_level(led->pin, state); /* Set the GPIO level according to the state (LOW or HIGH)*/
}

void configure_led(led_rgb *led, gpio_num_t pin, char* color)
{
    ESP_LOGI(TAG, "Configured GPIO LED %d %s!", pin, color);

    led -> pin = pin;    
    led -> color = color; 

    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT); /* Set the GPIO as a push/pull output */
}
