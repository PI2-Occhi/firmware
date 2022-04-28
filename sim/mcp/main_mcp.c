#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include "motor.h"
#include "uart.h"
#include "buzzer.h"
#include "hcsr.h"
#include "mcp23017.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_system.h"

led_rgb led_2 = {.pin = 2, .color = "red"};
mcp_t mcp;


void blink(void *pvParameter) {
    // alternate every other output pin in group A
    while(1) {
        mcp_write_register(&mcp, MCP23017_GPIO, GPIOA, 0xAB);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        mcp_write_register(&mcp, MCP23017_GPIO, GPIOA, 0x25);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    mcp.i2c_addr = MCP23017_DEFAULT_ADDR;
    mcp.port = I2C_NUM_1;
    mcp.sda_pin = I2C_SDA;
    mcp.scl_pin = I2C_SCL;

    mcp.sda_pullup_en = GPIO_PULLUP_ENABLE;
    mcp.scl_pullup_en = GPIO_PULLUP_ENABLE;
    esp_err_t ret = mcp_init(&mcp);
    ESP_ERROR_CHECK(ret);

//    uint32_t hall_sensor_value = init_motor();
    init_led(&led_2);
    set_state_led(&led_2, 1);

    xTaskCreate(&blink,"blink",2048,NULL,5,NULL);

//    while (1)
//    {
//        run_motor(hall_sensor_value);
//    }
}