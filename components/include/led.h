#pragma once

#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"


#ifdef __cplusplus
extern "C" {
#endif

// Structure of sensor
typedef struct {
	gpio_num_t pin;
    char* color;
} led_rgb;

void configure_led(led_rgb *led, gpio_num_t pin, char* color);
void set_state_led(led_rgb *led, uint8_t state);

#ifdef __cplusplus
}
#endif