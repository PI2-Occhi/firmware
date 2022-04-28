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

//Variáveis que recebem os valores dos sensores Hall
#define GPIO_HALL1       2 
#define GPIO_HALL2       3
#define GPIO_HALL3       4

// Saídas para ativação dos MOSFET's do inversor trifásico
#define GPIO_HIGHSIZE_A  5 // Saídas digitais HIGH SIDE (0 ou 1)
#define GPIO_HIGHSIZE_B  6
#define GPIO_HIGHSIZE_C  7
#define GPIO_LOWSIZE_A   9 // Saídas PWM LOW SIDE (0 a 254)
#define GPIO_LOWSIZE_B   10
#define GPIO_LOWSIZE_C   11
#define GPIO_LOW         0

// Definição para configuração do PWM
#define LEDC_FADE_TIME    500
#define LEDC_RESOLUTION   1024
#define LEDC_FREQ         5000

// Structure of motor
typedef struct {
	gpio_num_t hall1;
    gpio_num_t hall2;
    gpio_num_t hall3;

    gpio_num_t HighSizeA;
    gpio_num_t HighSizeB;
    gpio_num_t HighSizeC;

    gpio_num_t LowSizeA;
    gpio_num_t LowSizeB;
    gpio_num_t LowSizeC;
} motor;

int8_t SensorHall1; // Variáveis para os três sensores Hall (1,2,3)
int8_t SensorHall2;
int8_t SensorHall3;
uint32_t VarHall = 1; // Variável para armazenar o valor decimal convertido dos 3 sensores hall
int8_t hSpeed = 0; //Variável para receber o valor PWM para rotação do motor no sentido horário
int8_t ahSpeed = 0; //Variável para receber o valor PWM para rotação do motor no sentido anti-horário
int8_t frSpeed = 0; //Variável para receber o valor PWM para o freio regenerativo
int8_t throttle = 0; //Variável para receber o valor análógico do potenciômetro de controle do
//motor ligado em A0
int8_t brake = 0; /*Variável para receber o valor análógico do potenciômetro de controle do freio
    regenerativo ligado em A1*/

void init_motor(motor *motor);
void set_state_motor(motor *motor);
void toggle_motor_time(motor *motor);
void motor_initialization(motor *motor);
void loop();

#ifdef __cplusplus
}
#endif
