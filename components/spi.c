#include <stdint.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>
#include "spi.h"

void spi_send(spi_device_handle_t spi, const uint8_t *data)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=NUMBYTES*8;            //Transaction length in bits.
    t.tx_buffer=data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    printf ("Transmitting...\n");
//    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    ret=spi_device_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

void spi_init(){
    esp_err_t ret;
    spi_device_handle_t spi;
    spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=NUMBYTES
    };
    spi_device_interface_config_t devcfg={
        .command_bits=0,
        .address_bits=0,
        .dummy_bits=0,
        .mode=0,                       //SPI mode 0
        .duty_cycle_pos=128,
        .clock_speed_hz=8*1000*1000,   //Clock out frequency (Hz)
        .queue_size=1,
        .spics_io_num=PIN_NUM_CS      //CS pin
    };

     //Initialize the SPI bus
    ret=spi_bus_initialize(HSPI_HOST, &buscfg, 1); // 1 pour DMA
    ESP_ERROR_CHECK(ret);
    printf ("-------------------------------------\n\n");
    printf ("Adding device\n");
       ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
       ESP_ERROR_CHECK(ret);
    printf ("-------------------------------------\n\n");

}

void spi_send_example(uint8_t value) {
    esp_err_t ret;

    spi_device_handle_t spi;

    spi_bus_config_t buscfg={
      .mosi_io_num=PIN_NUM_MOSI,
      .miso_io_num=PIN_NUM_MISO,
      .sclk_io_num=PIN_NUM_CLK,
      .quadwp_io_num=-1,
      .quadhd_io_num=-1,
      .max_transfer_sz=0
    };

    spi_device_interface_config_t devcfg={
      .mode=0,                                //SPI mode 0
      .clock_speed_hz=500*1000,               //Clock out at 500 kHz
      .spics_io_num=PIN_NUM_CS,               //CS pin
      .queue_size=1,                          //We want to be able to queue 7 transactions at a time
    };

    //Initialize the SPI bus
    ret=spi_bus_initialize(OPC_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(OPC_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

    const uint8_t cmd = 0x03;       //Turn on OPC command

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&cmd;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.

    memset(&t, 0, sizeof(t));
    t.length=8;
    t.flags = SPI_TRANS_USE_RXDATA;
    t.user = (void*)1;

    ret = spi_device_polling_transmit(spi, &t);
    assert( ret == ESP_OK );

    ESP_LOGI(TAG, "response: 0x%02x", (uint8_t)t.rx_data[0]);
}


void spi_receiver(void) {
    esp_err_t err;

    spi_device_handle_t opcn2_handle;

    spi_bus_config_t buscfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
    };
    err = spi_bus_initialize(OPCN2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    assert( err == ESP_OK );

    spi_device_interface_config_t devcfg = {
        .mode = 1,
        .clock_speed_hz = OPCN2_CLK_FREQ,
        .spics_io_num = PIN_NUM_SS,
        .flags = SPI_TRANS_USE_RXDATA,
        .queue_size = 1
    };
    err = spi_bus_add_device(OPCN2_HOST, &devcfg, &opcn2_handle);
    assert( err == ESP_OK );

    uint8_t cmd = 0x03;

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));

    t.length = 8;
    t.tx_buffer = &cmd;

    gpio_set_level(PIN_NUM_SS, 0);
    err = spi_device_transmit(opcn2_handle, &t);
    gpio_set_level(PIN_NUM_SS, 1);
    assert( err == ESP_OK );

    ESP_LOGI(TAG, "response: 0x%02x", t.rx_data[0]);
 }
