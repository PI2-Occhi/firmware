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
#include "buzzer.h"
#include "hcsr.h"

static const char *TAG = "OCCHI";

void app_main(void)
{

    while (1) {
            ESP_LOGI(TAG, "Project");
    }
}
