/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/timer.h" 
#include "hardware/dma.h"
#include "hardware/i2c.h"

const uint8_t address_slave = 0x20 ; 

void initI2C(uint8_t port_sda,uint8_t port_scl){
    ///FIXME: ASSERT FOR A PORT ERROR
    i2c_init(i2c0,100000) ; 
    i2c_set_slave_mode(i2c0, true, 70) ; 
    gpio_set_function(4,GPIO_FUNC_I2C ) ; 
    gpio_set_function(5,GPIO_FUNC_I2C ) ; 
    gpio_pull_up(4) ; 
    gpio_pull_up(5) ; 
    

}  

volatile bool dma_end = false ; 

void rx_dma_handler(void){ 
    const uint32_t status = i2c_get_hw(i2c0)->intr_stat;
    if (status & I2C_IC_INTR_STAT_R_STOP_DET_BITS){
        printf("dma_end\r\n") ; 
        dma_end = true ; 

    }
}


    
void main() {
    stdio_init_all() ; 
    initI2C(4,5) ; 
    uint8_t rx_i2c[4] = {0x00,0x00,0x00,0x00}; 
    uint rx_channel = 0 ; 
    // dma_channel_config rx_config = dma_channel_get_default_config(rx_channel);
    // channel_config_set_read_increment(&rx_config, false);
    // channel_config_set_write_increment(&rx_config, true);
    // channel_config_set_transfer_data_size(&rx_config, DMA_SIZE_8);
    // channel_config_set_dreq(&rx_config, i2c_get_dreq(i2c0, false));
    // dma_channel_configure(
    //   rx_channel, &rx_config, rx_i2c, &i2c_get_hw(i2c0)->rxflr, 4, true
    // );
    //i2c_get_hw(i2c0)->dma_cr = 0x01u ; // enable a dma transfer rx   
    //irq_set_exclusive_handler(I2C0_IRQ, rx_dma_handler);
    //irq_set_enabled(I2C0_IRQ, true);



    while (true) {
        // printf("bytes received: %d - %d- %d- %d\r\n", rx_i2c[0],rx_i2c[1],rx_i2c[2],rx_i2c[3] ) ; 
        // sleep_ms(2000) ; 
       if (i2c_get_read_available(i2c0)<4){
           continue ; 
       } 
       i2c_read_raw_blocking(i2c0,rx_i2c,4) ; 
       printf("bytes received: %d - %d- %d- %d\r\n", rx_i2c[0],rx_i2c[1],rx_i2c[2],rx_i2c[3] ) ; 

    }
}
