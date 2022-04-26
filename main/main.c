#include <stdio.h>
#include <string.h>
#include "led.h"
#include "uart.h"

led_rgb led_2 = {.pin = 2, .color = "red"};

void app_main(void)
{
    init_led(&led_2);
    initUart();

    while (1)
    {
        char* byte_command = readByte();

        if (strcmp(byte_command, "a") == 0) {
            set_state_led(&led_2,  1);
        }
        if (strcmp(byte_command, "d") == 0) {
            set_state_led(&led_2,  0);
        }
    }
}