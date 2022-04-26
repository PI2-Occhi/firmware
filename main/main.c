#include <stdio.h>
#include <string.h>
#include "led.h"
#include "uart.h"
#include "battery.h"
led_rgb led_2 = {.pin = 2, .color = "red"};

void app_main(void)
{
    init_led(&led_2);

    while (1)
    {
        printf("Projeto Occhi");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}