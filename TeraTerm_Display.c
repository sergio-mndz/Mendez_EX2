/*
 * TeraTerm_Display.c
 *
 *  Created on: Apr 10, 2020
 *      Author: sergio_mndz
 */

#include "TeraTerm_Display.h"

#define DOUBLE_POINT 58
#define HEX_TENTH 16
#define ENTER_CHAR 13
#define CHARS_STR 8
#define SLASH_STR 47
#define COMMA_STR 58
#define ESC_CHAR 27
#define ONE_PRESSED '1'
#define TWO_PRESSED '2'
#define CHARS_DT 10

uint8_t g_hour_string[CHARS_STR];
uint8_t g_date_string[CHARS_STR];
uint8_t g_read_access_granted = FALSE;
uint8_t g_write_access_granted = FALSE;

uint8_t* g_string_secs;
uint8_t* g_string_mins;
uint8_t* g_string_hours;

void terminal_init(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate)
{
	/**Configures UART 0 to transmit/receive at 115200 bauds with a 21 MHz of clock core*/
	UART_init(uart_channel,  system_clk, baud_rate);
	UART_interrupt_enable(uart_channel);
	/**The following sentences send strings to PC using the UART_put_string function. Also, the string
	 * is coded with terminal code*/
	/*VT100 command for clearing the screen*/
	UART_put_string(uart_channel,"\033[2J");
	UART_put_string(uart_channel,"\033[38;5;202m");
	UART_put_string(uart_channel,"\033[48;5;15m");
	UART_put_string(uart_channel,"\033[H");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(uart_channel,"\033[10;10H");
}

void showManual_Display(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[2J");
	UART_put_string(terminal,"\033[38;5;202m");
	UART_put_string(terminal,"\033[48;5;15m");
	UART_put_string(terminal,"\033[H");
	UART_put_string(terminal,"Modo manual \r\n");
	UART_put_string(terminal,"\r\n");
}

void showSequence_Display(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[2J");
	UART_put_string(terminal,"\033[38;5;202m");
	UART_put_string(terminal,"\033[48;5;15m");
	UART_put_string(terminal,"\033[H");
	UART_put_string(terminal,"Modo secuencia \r\n");
	UART_put_string(terminal,"\r\n");
}


