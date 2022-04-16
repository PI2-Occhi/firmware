#pragma once

#include <stdint.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// Variables
static const char TAG[] = "opc";

// Defines
#define OPC_HOST    HSPI_HOST
#define NUMBYTES     20
uint8_t data[NUMBYTES];


#define PIN_NUM_MISO 12
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   15

#define OPCN2_CLK_FREQ 500 * 1000

#ifdef CONFIG_IDF_TARGET_ESP32
#define OPCN2_HOST HSPI_HOST
#define PIN_NUM_MISO GPIO_NUM_25
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CLK GPIO_NUM_19
#define PIN_NUM_SS GPIO_NUM_22
#endif

// Functions
void spi_send(uint8_t value);
void spi_receiver();

#ifdef __cplusplus
}
#endif