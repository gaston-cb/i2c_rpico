

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/i2c.h" 
#define CLK_SPEED 100000
#define I2C_SLAVE_ADDRESS 70 




void initI2C(uint port_a, uint port_b) ; 
void dma_handler(void); 







void main() {
    stdio_init_all() ; 
    sleep_ms(1000) ; 
    initI2C(4,5) ; 

    while (true) {

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
