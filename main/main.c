/* 
    Main Project
    author: Debora Fernandes e Matheus Gois
    description: control occhi
*/


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "driver/gpio.h"

#include "led.h"

static const char *TAG = "OCCHI";

led_rgb led2 = {.pin = 2, .color = "red"};

void app_main(void)
{
    configure_led(&led2, 2, "red");
    set_state_led(&led2, 1);

    while (1) {
        ESP_LOGI(TAG, "Turning the occhi!");
    }
}
