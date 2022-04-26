#include "piezo.h"
#include "battery.h"

void initPiezo(){
    adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_0);
}
void getStatePiezo(piezo *p){
    int val = adc1_get_raw(ADC1_CHANNEL_1);
    if(val*ADC_GAIN > 10) {
        p->state = 1;
    } else {
        p->state = 0;
    }
}