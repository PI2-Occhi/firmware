#pragma once

#include <stdio.h>
#include <math.h>
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
#include "driver/i2c.h"
#include "freertos/task.h"

// registers
#define MCP23017_IODIRA		0x00
#define MCP23017_IPOLA 		0x02
#define MCP23017_GPINTENA 	0x04
#define MCP23017_DEFVALA 	0x06
#define MCP23017_INTCONA 	0x08
#define MCP23017_IOCONA 	0x0A
#define MCP23017_GPPUA 		0x0C
#define MCP23017_INTFA 		0x0E
#define MCP23017_INTCAPA 	0x10
#define MCP23017_GPIOA 		0x12
#define MCP23017_OLATA 		0x14


#define MCP23017_IODIRB 	0x01
#define MCP23017_IPOLB 		0x03
#define MCP23017_GPINTENB 	0x05
#define MCP23017_DEFVALB 	0x07
#define MCP23017_INTCONB 	0x09
#define MCP23017_IOCONB 	0x0B
#define MCP23017_GPPUB 		0x0D
#define MCP23017_INTFB 		0x0F
#define MCP23017_INTCAPB 	0x11
#define MCP23017_GPIOB 		0x13
#define MCP23017_OLATB 		0x15

#define MCP23017_DEFAULT_ADDR	0x20

#define I2C_SDA	    21
#define I2C_SCL     22

typedef enum {
    MCP23017_ERR_OK      = 0x00,
    MCP23017_ERR_CONFIG  = 0x01,
    MCP23017_ERR_INSTALL = 0x02,
    MCP23017_ERR_FAIL    = 0x03
} mcp_err_t;

#ifndef WRITE_BIT
#define WRITE_BIT  I2C_MASTER_WRITE /*!< I2C master write */
#endif

#ifndef READ_BIT
#define READ_BIT   I2C_MASTER_READ  /*!< I2C master read */
#endif

#ifndef ACK_CHECK_EN
#define ACK_CHECK_EN   0x1
#endif

typedef enum {
    MCP23017_IODIR		= 0x00,
    MCP23017_IPOL		= 0x01,
    MCP23017_GPINTEN	= 0x02,
    MCP23017_DEFVAL	= 0x03,
    MCP23017_INTCON	= 0x04,
    MCP23017_IOCON		= 0x05,
    MCP23017_GPPU		= 0x06,
    MCP23017_INTF		= 0x07,
    MCP23017_INTCAP	= 0x08,
    MCP23017_GPIO		= 0x09,
    MCP23017_OLAT		= 0x0A
} mcp_reg_t;

typedef enum {
    GPIOA = 0x00,
    GPIOB = 0x01
} mcp_gpio_t;

typedef struct {
    uint8_t i2c_addr;
    i2c_port_t port;
    uint8_t sda_pin;
    uint8_t scl_pin;
    gpio_pullup_t sda_pullup_en;
    gpio_pullup_t scl_pullup_en;
} mcp_t;

// Functions
mcp_err_t mcp_init(mcp_t *mcp);
mcp_err_t mcp_write_register(mcp_t *mcp, mcp_reg_t reg, mcp_gpio_t group, uint8_t v);
mcp_err_t mcp_read_register(mcp_t *mcp, mcp_reg_t reg, mcp_gpio_t group, uint8_t *data);
mcp_err_t mcp_set_bit(mcp_t *mcp, uint8_t bit, mcp_reg_t reg, mcp_gpio_t group);
mcp_err_t mcp_clear_bit(mcp_t *mcp, uint8_t bit, mcp_reg_t reg, mcp_gpio_t group);

#ifdef __cplusplus
}
#endif