/* 
    Project Motor BLDC
    author: Debora Fernandes e Matheus Gois
    description: Control occhi
*/

#include <stdio.h>
#include "motor.h"


long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void motor_initialization(motor *motor) {

    gpio_set_direction(GPIO_HALL1, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_HALL2, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_HALL3, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_HIGHSIZE_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_HIGHSIZE_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_HIGHSIZE_C, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LOWSIZE_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LOWSIZE_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LOWSIZE_C, GPIO_MODE_OUTPUT);

}

mcpwm_set_frequency( mcpwm_unit_t mcpwm_num , mcpwm_timer_t timer_num, uint32_t frequência)

void control_loop() {
    throttle = gpio_get_level(0);
    hSpeed = map(throttle, 560, 1023, 0, 254);
    ahSpeed = map(throttle, 0, 460, 254, 0);
    static inline uint32_t

    VarHall = gpio_get_level(GPIO_HALL1) + (2 * gpio_get_level(GPIO_HALL2)) + (4 * gpio_get_level(GPIO_HALL3));

    if (throttle > 560) {
        sentido_horario();
    } else if (throttle < 460) {
        sentido_anti_horario();
    } else if (throttle < 560 && throttle > 460) {
        brake = gpio_get_level(1);
        frSpeed = map(brake, 0, 1023, 0, 255);
        freio_regenerativo();
    }
}

void sentido_horario() {
    switch (VarHall) {
        case 5:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(7, 0);

            gpio_set_level(5, 1);

            gpio_set_level(9, 0);
            gpio_set_level(10, hSpeed);
            gpio_set_level(11, 0);
            break;

        case 1:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(7, 0);

            gpio_set_level(7, 1);

            gpio_set_level(9, 0);
            gpio_set_level(10, hSpeed);
            gpio_set_level(1, 0);
            break;

        case 3:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(7, 0);

            gpio_set_level(7, 1);
            gpio_set_level(9, hSpeed);
            gpio_set_level(10, 0);
            gpio_set_level(11, 0);
            break;

        case 2:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(6, 0);

            gpio_set_level(6, 1);
            gpio_set_level(9, hSpeed);
            gpio_set_level(0, 0);
            gpio_set_level(11, 0);
            break;

        case 6:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(6, 0);

            gpio_set_level(6, 1);
            gpio_set_level(9, 0);
            gpio_set_level(10, 0);
            gpio_set_level(11, hSpeed);
            break;

        case 4:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(5, 0);

            gpio_set_level(5, 1);
            gpio_ggpio_set_levelet_level(9, 0);
            gpio_set_level(10, 0);
            gpio_set_level(11, hSpeed);
            break;
    }
}

void sentido_anti_horario() {
    switch (VarHall) {

        case 5:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(6, 0);

            gpio_set_level(6, 1);
            gpio_set_level(9, hSpeed);
            gpio_set_level(10, 0);
            gpio_set_level(11, 0);
            break;

        case 1:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(6, 0);

            gpio_set_level(6, 1);
            gpio_set_level(9, 0);
            gpio_set_level(10, 0);
            gpio_set_level(11, hSpeed);
            break;

        case 3:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(5, 0);

            gpio_set_level(5, 1);
            gpio_ggpio_set_levelet_level(9, 0);
            gpio_set_level(10, 0);
            gpio_set_level(11, hSpeed);
            break;

        case 2:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(5, 0);

            gpio_set_level(5, 1);
            gpio_ggpio_set_levelet_level(9, 0);
            gpio_set_level(10, hSpeed);
            gpio_set_level(11, 0);
            break;

        case 6:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(7, 0);

            gpio_set_level(7, 1);
            gpio_ggpio_set_levelet_level(9, 0);
            gpio_set_level(10, hSpeed);
            gpio_set_level(11, 0);
            break;

        case 4:
            gpio_set_level(0, 1);
            gpio_set_level(1, 1);
            gpio_set_level(2, 1);
            gpio_set_level(3, 1);
            gpio_set_level(4, 1);
            gpio_set_level(7, 0);

            gpio_set_level(7, 1);
            gpio_ggpio_set_levelet_level(9, hSpeed;
            gpio_set_level(10, 0);
            gpio_set_level(11, 0);
            break;
            break;
    }
}

void freio_regenerativo() {
    gpio_set_level(0, 1);
    gpio_set_level(1, 1);
    gpio_set_level(2, 1);
    gpio_set_level(3, 1);
    gpio_set_level(4, 1);
    gpio_set_level(5, 0);
    gpio_set_level(6, 0);
    gpio_set_level(7, 0);

    switch (VarHall) {

        case 3:
            gpio_set_level(9, frSpeed);
            gpio_set_level(10, 0);
            gpio_set_level(11, 0);
            break;

        case 1:
            gpio_set_level(9, frSpeed);
            gpio_set_level(0, 0);
            gpio_set_level(11, 0);
            break;

        case 5:
            gpio_set_level(9, 0);
            gpio_set_level(10, 0);
            gpio_set_level(11, frSpeed);
            break;

        case 4:
            gpio_set_level(9, 0);
            gpio_set_level(10, 0);
            gpio_set_level(11, frSpeed);
            break;

        case 6:
            gpio_set_level(9, 0);
            gpio_set_level(10, frSpeed);
            gpio_set_level(11, 0);
            break;

        case 2:
            gpio_set_level(9, 0);
            gpio_set_level(10, frSpeed);
            gpio_set_level(11, 0);
            break;
    }
}