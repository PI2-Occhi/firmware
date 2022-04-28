#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "led.h"
#include <sys/time.h>
#include "rom/ets_sys.h"
#include "esp_timer.h"
#include "esp_sleep.h"

const int trigPin = 19;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

static inline uint32_t get_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec;
}

void app_main(void)
{
    gpio_set_direction(trigPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(echoPin, GPIO_MODE_OUTPUT);

    while (1)
    {
        // Variables of times
        int64_t initial_time = 0;
        int64_t final_time = 0;
        
        // Clears the trigPin
        gpio_set_level(trigPin, 0);
        ets_delay_us(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        gpio_set_level(trigPin, 1);
        ets_delay_us(10);
        gpio_set_level(trigPin, 0);

        // Reads the echoPin, returns the sound wave travel time in microseconds
        // Wait for pulse on echo pin
        while(gpio_get_level(echoPin) == 0);

        // Measure how long the echo pin was held high (pulse width)
        // Note: the get_time_us() counter will overflow after ~70 min
        initial_time = get_time_us();

        while(gpio_get_level(echoPin) == 1);
        final_time = get_time_us();

        duration =  final_time - initial_time;

        // Calculate the distance
        distanceCm = duration * SOUND_SPEED/2;

        // Convert to inches
        distanceInch = distanceCm * CM_TO_INCH;

        // Prints the distance in the Serial Monitor
        printf("Pulse width:  %2.f\n", distanceInch);
        printf("Distance (cm):   %2.f\n", distanceCm);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}