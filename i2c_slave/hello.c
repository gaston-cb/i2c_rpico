/**
 * @file main.c
 * @author Gaston Valdez (gvaldez@iar.unlp.edu.ar)
 * @brief : Slave rp2040 using with a rx/tx i2c with dma channel 
 * @version 0.1
 * @date 2023-03-22
 * 
 * 
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/dma.h"

#include "hardware/i2c.h" 
#define CLK_SPEED 100000
#define I2C_SLAVE_ADDRESS 70 
#define BUFFER_TX 5 
#define BUFFER_RX 4 


void initI2C(uint port_a, uint port_b) ; 
void dma_handler(void); 
void dma_init_tx() ; 
void dma_init_rx() ; 

/// @brief variabbles 
uint dma_tx ; //dma tx channel 
uint dma_rx ; //dma_rx channel 

uint8_t rx_i2c[BUFFER_RX] ; 
uint8_t tx_i2c[BUFFER_RX] ; 
bool dma_end_rx = false ; 







void main() {
    stdio_init_all() ; 
    sleep_ms(1000) ; 
    initI2C(4,5) ; 
    uint index = 0 ; 
    for (index = 0; index<BUFFER_TX;index++){
        tx_i2c[BUFFER_TX] = index +1 ; 
    } ///tx_i2c buffer is tx[j] = j+1   
    dma_init_rx() ; 
    dma_init_tx() ; 
    





    while (true) {
        if (dma_end_rx == true){ 
            dma_end_rx = false ; 
            printf("rxI2C: ") ;    
            for ( uint i = 0; i<BUFFER_RX; i++){
                printf("%02x", rx_i2c[i]) ; 
            }
            printf("\r\n") ; 

        }

    }
}






void initI2C(uint port_a, uint port_b){
    i2c_init(i2c0,CLK_SPEED) ; 
    i2c_set_slave_mode(i2c0, true, I2C_SLAVE_ADDRESS) ; 
    gpio_set_function(port_a,GPIO_FUNC_I2C ) ; 
    gpio_set_function(port_b,GPIO_FUNC_I2C ) ; 
    gpio_pull_up(port_a) ; 
    gpio_pull_up(port_b) ; 
}


void dma_handler(void){ 
    hw_set_bits(&dma_hw->ints0,1<<dma_rx) ; 
    dma_channel_set_write_addr(dma_rx, rx_i2c,true) ; 
    dma_end_rx = true ; 
}


void dma_init_tx(){ 
    
}


void dma_init_rx(){ 
    dma_rx =  dma_claim_unused_channel(true) ; 
    dma_channel_config c_rx = dma_channel_get_default_config(dma_rx) ; 
    channel_config_set_transfer_data_size(&c_rx,DMA_SIZE_8) ; 
    channel_config_set_read_increment(&c_rx,false) ; 
    channel_config_set_write_increment(&c_rx,true) ; 
    channel_config_set_dreq(&c_rx, i2c_get_dreq(i2c0,false)) ; 
    dma_channel_configure(
        dma_rx, 
        &c_rx,
        rx_i2c, 
        &i2c_get_hw(i2c0)->data_cmd, 
        BUFFER_RX,
        true  
    ) ; 
    i2c0->hw->dma_cr = 1 ; 
    dma_channel_set_irq0_enabled(dma_rx,true) ; 
    dma_irqn_set_channel_enabled(DMA_IRQ_0,dma_rx,true) ; 
    irq_set_exclusive_handler(DMA_IRQ_0,dma_handler) ; 
    irq_set_enabled(DMA_IRQ_0,true) ; 



}

