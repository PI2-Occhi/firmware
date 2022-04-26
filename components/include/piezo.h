#pragma once

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"



#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    gpio_num_t pin;
    int8_t state;
} piezo;

void initPiezo();
void getStatePiezo(piezo *p);

#ifdef __cplusplus
}
#endif