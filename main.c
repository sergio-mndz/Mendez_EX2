 /**
 * @file    Examen2.c
 * @brief   Application entry point.
 */

#include <stdio.h>

#define DELAY_PIT 0.0001
#define SYS_CLK 21000000

#include "MK64F12.h"

int main(void) {

	DAC_clock_gating();
	DAC_init();
	NVIC_enable_interrupt_and_priotity(DMA_CH0_IRQ, PRIORITY_5);
	initPlayer();
	NVIC_global_enable_interrupts;
	PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_PIT);

    while(1) {

    }
    return 0 ;
}
