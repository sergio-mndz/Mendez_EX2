/*
 * TeraTerm_Display.h
 *
 *  Created on: Apr 10, 2020
 *      Author: sergio_mndz
 */

#ifndef DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_
#define DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_

#include "UART.h"
#include "i2c_rtc.h"
#include "String_conversion.h"


typedef enum{
	TENTS,
	UNITS
}units_tents_str_t;


void terminal_init(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate);


void showHour_Display(uart_channel_t terminal);


void setHour_Display(uart_channel_t terminal);


void show_Hour(uart_channel_t terminal);



void write_Hour(uart_channel_t terminal, uint8_t * data);





void Hour_to_String_cast(uart_channel_t terminal);


void Date_to_String_cast(uart_channel_t terminal);

#endif /* DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_ */
