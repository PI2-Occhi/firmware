#pragma once

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"



#ifdef __cplusplus
extern "C" {
#endif

#define ADC_RESOLUTION		4095.0
#define ADC_OFFSET			2048
#define ADC_VREF			5.0
#define ADC_GAIN			(ADC_VREF / ADC_RESOLUTION)


// Structure of battery
typedef struct {
    gpio_num_t pin;
    int8_t state;
    float current_value;
} battery_system;

void initAdcBaterry();
void getLevelBatery(battery_system *battery);
void monitorBatery(battery_system *battery);

#ifdef __cplusplus
}
#endif