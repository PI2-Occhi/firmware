#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hcsr.h"


// Anything over 400 cm (23200 us pulse) is "out of range"
const int32_t MAX_DIST = 23200;

// hcsr sensor_front = {.echo = GPIO_ECHO, .trigger = GPIO_TRIGGER};

void measurements(hcsr *sensor){
	// Variables of times
	int64_t initial_time = 0;
	int64_t final_time = 0;

	// Hold the trigger pin high for at least 10 us
	gpio_set_level(sensor->trigger, GPIO_HIGH);
	ets_delay_us(10);
	gpio_set_level(sensor->trigger, GPIO_LOW);

	// Wait for pulse on echo pin
	while(gpio_get_level(sensor->echo) == GPIO_LOW);

	// Measure how long the echo pin was held high (pulse width)
	// Note: the esp_timer_get_time() counter will overflow after ~70 min
	initial_time = esp_timer_get_time();

	while(gpio_get_level(sensor->echo) == GPIO_HIGH);
	initial_time = esp_timer_get_time();


	sensor->pulse_width = final_time - initial_time;

	// Calculate distance in centimeters. The constants
	// are found in the datasheet, and calculated from the assumed speed
	//of sound in air at sea level (~340 m/s).
	sensor->space_cm = sensor->pulse_width / 58.0;
}


void hcsr_initialization(hcsr *sensor){
	sensor->address = "0A";
	sensor->pulse_width = 0;
	sensor->space_cm = 0;
}

void set_direction(hcsr *sensor, char direction){
	sensor->direction = direction;
}