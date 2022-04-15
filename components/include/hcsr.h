#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "rom/ets_sys.h"
#include "esp_timer.h"
#include "esp_sleep.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_ECHO       18 // ECHO
#define GPIO_TRIGGER    5 // TRIGGER
#define GPIO_HIGH       1
#define GPIO_LOW        0
#define MAX             100
#define BUF_SIZE        (1024)

// Structure of sensor
typedef struct {
	gpio_num_t echo;
	gpio_num_t trigger;
    float space_cm;
    float pulse_width;
    char direction;
    char* address;
} hcsr;


// Define functions
void measurements(hcsr *sensor);
void hcsr_initialization(hcsr *sensor);
void set_direction(hcsr *sensor, char direction);

#ifdef __cplusplus
}
#endif