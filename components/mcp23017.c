/*
    Project MCP23017
    author: Debora Fernandes e Matheus Gois
    description: Control occhi
    base_code: mcp23017.c
*/

#include <driver/gpio.h>
#include <driver/i2c.h>
#include "esp_log.h"
#include "mcp23017.h"

static const size_t I2C_MASTER_TX_BUF_DISABLE = 0;
static const size_t I2C_MASTER_RX_BUF_DISABLE = 0;
static const int INTR_FLAGS = 0;

static const char *TAG_MCP = "MCP_OCCHI";

uint8_t mcp_register(mcp_reg_t reg, mcp_gpio_t group) {
    return (group == GPIOA)?(reg << 1):(reg << 1) | 1;
}

mcp_err_t mcp_init(mcp_t *mcp) {

    esp_err_t ret;

    // setup i2c controller
    i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = mcp->sda_pin,
            .scl_io_num = mcp->scl_pin,
            .sda_pullup_en = mcp->sda_pullup_en,
            .scl_pullup_en = mcp->scl_pullup_en,
            .master.clk_speed = 100000
    };
    ret = i2c_param_config(mcp->port, &conf);


    if( ret != ESP_OK ) {
        ESP_LOGE(TAG_MCP,"PARAM CONFIG FAILED");
        return MCP23017_ERR_CONFIG;
    }
    ESP_LOGV(TAG_MCP,"PARAM CONFIG done");

    // install the driver
    ret = i2c_driver_install(mcp->port, I2C_MODE_MASTER, I2C_MASTER_TX_BUF_DISABLE, I2C_MASTER_RX_BUF_DISABLE, INTR_FLAGS);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG_MCP,"I2C driver install failed");
        return MCP23017_ERR_INSTALL;
    }
    ESP_LOGV(TAG_MCP,"I2C DRIVER INSTALLED");

    // make all I/O's output
    mcp_write_register(mcp, MCP23017_IODIR, GPIOA, 0x00);
    mcp_write_register(mcp, MCP23017_IODIR, GPIOB, 0x00);

    return MCP23017_ERR_OK;
}

mcp_err_t mcp_write_register(mcp_t *mcp, mcp_reg_t reg, mcp_gpio_t group, uint8_t v) {
    uint8_t r = mcp_register(reg, group);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, mcp->i2c_addr << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, r, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, v, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(mcp->port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_FAIL) {
        ESP_LOGE(TAG_MCP,"ERROR: unable to write to register");
        return MCP23017_ERR_FAIL;
    }
    return MCP23017_ERR_OK;
}

mcp_err_t mcp23017_read_register(mcp_t *mcp, mcp_reg_t reg, mcp_gpio_t group, uint8_t *data) {
    // from the generic register and group, derive register address
    uint8_t r = mcp_register(reg, group);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (mcp->i2c_addr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, r, 1);
    i2c_master_stop(cmd);
    esp_err_t ret =i2c_master_cmd_begin(mcp->port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if( ret == ESP_FAIL ) {
        ESP_LOGE(TAG_MCP,"ERROR: unable to write address %02x to read reg %02x",mcp->i2c_addr,r);
        return MCP23017_ERR_FAIL;
    }

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (mcp->i2c_addr << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, data, 1);
    ret =i2c_master_cmd_begin(mcp->port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if( ret == ESP_FAIL ) {
        ESP_LOGE(TAG_MCP,"ERROR: unable to read reg %02x from address %02x",r,mcp->i2c_addr);
        return MCP23017_ERR_FAIL;
    }

    return MCP23017_ERR_OK;
}

mcp_err_t mcp_set_bit(mcp_t *mcp, uint8_t bit, mcp_reg_t reg, mcp_gpio_t group) {
    uint8_t current_value;
    if( mcp23017_read_register(mcp, reg, group, &current_value) != MCP23017_ERR_OK ) {
        uint8_t r = mcp_register(reg, group);
        ESP_LOGE(TAG_MCP, "ERROR: unable to read current value of register %02x",r);
        return MCP23017_ERR_FAIL;
    }
    current_value |= 1 << bit;
    if( mcp_write_register(mcp, reg, group, current_value) != MCP23017_ERR_OK ) {
        uint8_t r = mcp_register(reg, group);
        ESP_LOGE(TAG_MCP, "ERROR: unable to write new value %02X to register %02x",current_value, r);
        return MCP23017_ERR_FAIL;
    }
    return MCP23017_ERR_OK;
}

mcp_err_t mcp_clear_bit(mcp_t *mcp, uint8_t bit, mcp_reg_t reg, mcp_gpio_t group) {
    uint8_t current_value;
    if( mcp23017_read_register(mcp, reg, group, &current_value) != MCP23017_ERR_OK ) {
        uint8_t r = mcp_register(reg, group);
        ESP_LOGE(TAG_MCP, "ERROR: unable to read current value of register %02x",r);
        return MCP23017_ERR_FAIL;
    }
    current_value &= ~(1 << bit);
    if( mcp_write_register(mcp, reg, group, current_value) != MCP23017_ERR_OK ) {
        uint8_t r = mcp_register(reg, group);
        ESP_LOGE(TAG_MCP, "ERROR: unable to write new value %02X to register %02x",current_value, r);
        return MCP23017_ERR_FAIL;
    }
    return MCP23017_ERR_OK;
}
