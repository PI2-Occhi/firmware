#pragma once

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h" 
#include "esp_timer.h" 
#include "esp_attr.h" 
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_DEFAULT_FREQ   14400
#define PWM_MIN_DUTY       40.0
#define PWM_MAX_DUTY       80.0
#define PWM_DUTY_STEP      5.0
#define BLDC_MCPWM_GROUP   0
#define BLDC_MCPWM_TIMER_U 0
#define BLDC_MCPWM_TIMER_V 1
#define BLDC_MCPWM_TIMER_W 2
#define BLDC_MCPWM_GEN_HIGH MCPWM_GEN_A
#define BLDC_MCPWM_GEN_LOW  MCPWM_GEN_B


#define BLDC_DRV_EN_GPIO    18
#define BLDC_DRV_FAULT_GPIO 19
#define BLDC_DRV_OVER_CURRENT_FAULT MCPWM_SELECT_F0

#define BLDC_PWM_UH_GPIO 21
#define BLDC_PWM_UL_GPIO 22
#define BLDC_PWM_VH_GPIO 23
#define BLDC_PWM_VL_GPIO 25
#define BLDC_PWM_WH_GPIO 26
#define BLDC_PWM_WL_GPIO 27

//Variables from sensor Hall
#define HALL_CAP_U_GPIO  2
#define HALL_CAP_V_GPIO  4
#define HALL_CAP_W_GPIO  5

// Structure sensor hall
typedef void (*bldc_hall_phase_action_t)(void);

// Funtion of control
uint32_t init_motor();
void run_motor(int32_t hall_sensor_value);

#ifdef __cplusplus
}
#endif
