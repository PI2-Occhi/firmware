#include "battery.h"

void initAdcBaterry(){
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
}
void getLevelBatery(battery_system *battery) {
    int val = adc1_get_raw(ADC1_CHANNEL_0);
    battery -> current_value = val*ADC_GAIN;
    //printf("value is %.2f\n", val*ADC_GAIN);
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
}
void monitorBatery(battery_system *battery) {
    if(battery->current_value < 0.30*ADC_VREF){
        battery->state = 1;
    }
    if(battery->current_value > 0.30*ADC_VREF) {
        battery->state = 0;
    } else {
        battery->state = -1;
    }
}
