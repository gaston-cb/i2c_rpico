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
#include "hardware/i2c.h" 
#define CLK_SPEED 100000
#define I2C_SLAVE_ADDRESS 70 
#define BUFFER_TX 5 
#define BUFFER_RX 5 


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






/// @brief 
/// @param port_a 
/// @param port_b 
void initI2C(uint port_a, uint port_b){
    i2c_init(i2c0,CLK_SPEED) ; 
    i2c_set_slave_mode(i2c0, true, I2C_SLAVE_ADDRESS) ; 
    gpio_set_function(port_a,GPIO_FUNC_I2C ) ; 
    gpio_set_function(port_b,GPIO_FUNC_I2C ) ; 
    gpio_pull_up(port_a) ; 
    gpio_pull_up(port_b) ; 
}


void dma_handler(void){ 

}


void dma_init_tx(){ 
    
}


void dma_init_rx(){ 

}

