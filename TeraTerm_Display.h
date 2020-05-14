/*
 * TeraTerm_Display.h
 *
 *  Created on: Apr 10, 2020
 *      Author: sergio_mndz
 */

#ifndef DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_
#define DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_

#include "UART.h"
#include "String_conversion.h"


typedef enum{
	TENTS,
	UNITS
}units_tents_str_t;


void terminal_init(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate);



void showManual_Display(uart_channel_t terminal);

void showSequence_Display(uart_channel_t terminal);



#endif /* DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_ */
