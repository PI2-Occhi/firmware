#include <stdio.h>
#include "led.h"
#include "motor.h"
#include "uart.h"
#include "buzzer.h"
#include "hcsr.h"

led_rgb led_2 = {.pin = 2, .color = "red"};

void app_main(void)
{
    uint32_t hall_sensor_value = init_motor();
    init_led(&led_2);
    set_state_led(&led_2, 1);

    while (1)
    {
        run_motor(hall_sensor_value);
    }
}