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

bool repeating_timer_callback(struct repeating_timer *t) {
    printf("Repeat at %lld\n", time_us_64());
    return true;
}

void alarm_irq(void){
    printf("alarm irq \r\n") ; 
    //hw_set_bits(&timer_hw->inte,1u<<0) ; 
    hw_clear_bits(&timer_hw->intr, 1u << 0);
    timer_hw->alarm[0] = (uint32_t) ( (uint64_t) (timer_hw->timerawl + 1000000 * 2));
    hw_set_bits(&timer_hw->inte,1u<<0) ; 

} ; 



void main() {
    stdio_init_all() ; 
   // struct repeating_timer timer;
   // add_repeating_timer_ms(2000, repeating_timer_callback, NULL, &timer);
    hw_set_bits(&timer_hw->inte,1u<<0) ; 
    irq_set_exclusive_handler(TIMER_IRQ_0, alarm_irq);
    irq_set_enabled(TIMER_IRQ_0, true);
    timer_hw->alarm[0] = (uint32_t) 1000000 * 2; 
    
    
    uint32_t contador = 0 ; 
    while (true) {
//        sleep_ms(1000) ;
//        printf("count %d\r\n",contador++) ;  
    }
}
