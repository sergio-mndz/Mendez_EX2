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

void showHour_Display(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[2J");
	UART_put_string(terminal,"\033[38;5;202m");
	UART_put_string(terminal,"\033[48;5;15m");
	UART_put_string(terminal,"\033[H");
	UART_put_string(terminal,"La hora actual es: \r\n");
	UART_put_string(terminal,"\r\n");
}

void setHour_Display(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[2J");
	UART_put_string(terminal,"\033[38;5;202m");
	UART_put_string(terminal,"\033[48;5;15m");
	UART_put_string(terminal,"\033[H");
	UART_put_string(terminal,"Establecer hora\r\n");
	UART_put_string(terminal,"Escribir hora en hh:mm:ss : \r\n");
	UART_put_string(terminal,"\r\n");
}

void showDate_Display(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[2J");
	UART_put_string(terminal,"\033[38;5;202m");
	UART_put_string(terminal,"\033[48;5;15m");
	UART_put_string(terminal,"\033[H");
	UART_put_string(terminal,"La fecha actual es: \r\n");
	UART_put_string(terminal,"\r\n");
}

void setDate_Display(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[2J");
	UART_put_string(terminal,"\033[38;5;202m");
	UART_put_string(terminal,"\033[48;5;15m");
	UART_put_string(terminal,"\033[H");
	UART_put_string(terminal,"Establecer fecha\r\n");
	UART_put_string(terminal,"Escribir fecha en dd/mm/aa : \r\n");
	UART_put_string(terminal,"\r\n");
}

void show_Hour(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[4;5H");
	Hour_to_String_cast(terminal);
}

void show_Date(uart_channel_t terminal)
{
	UART_put_string(terminal,"\033[4;5H");
	Date_to_String_cast(terminal);
}

void write_Hour(uart_channel_t terminal, uint8_t * data)
{
	for(uint8_t byte = 0; byte < CHARS_STR; byte++)
	{
		data[byte] -= '0';
	}

	uint8_t secs = data[SEC_TENTS]*HEX_TENTH + data[SEC_UNITS];
	uint8_t mins = data[MIN_TENTS]*HEX_TENTH + data[MIN_UNITS];
	uint8_t hours = data[HOUR_TENTS]*HEX_TENTH + data[HOUR_UNITS];

	Time new_time = {hours, mins, secs};

	set_time(new_time);
}

void write_Date(uart_channel_t terminal, uint8_t * data)
{
	for(uint8_t byte = 0; byte < CHARS_STR; byte++)
	{
		data[byte] -= '0';
	}

	uint8_t day = data[DAY_TENTS]*HEX_TENTH + data[DAY_UNITS];
	uint8_t month = data[MONTH_TENTS]*HEX_TENTH + data[MONTH_UNITS];
	uint8_t year = data[YEAR_THOUSANDS]*HEX_TENTH + data[YEAR_HUNDRETHS];

	Date new_date = {ONE, day, month, year};

	set_date(new_date);
}

void Hour_to_String_cast(uart_channel_t terminal)
{
	char actual_time_string[CHARS_STR];
	uint8_t* secs_temp;
	uint8_t* mins_temp;
	uint8_t* hours_temp;

	Time actual_time = get_time();
	Time_to_String(actual_time.seconds, SEC);
	Time_to_String(actual_time.minutes, MIN);
	Time_to_String(actual_time.hours, HOUR);
	secs_temp = Get_String_Time(SEC);
	mins_temp = Get_String_Time(MIN);
	hours_temp = Get_String_Time(HOUR);
	actual_time_string[HOUR_TENTS] = hours_temp[TENTS];
	actual_time_string[HOUR_UNITS] = hours_temp[UNITS];
	actual_time_string[COMMA_1] = COMMA_STR;
	actual_time_string[MIN_TENTS] = mins_temp[TENTS];
	actual_time_string[MIN_UNITS] = mins_temp[UNITS];
	actual_time_string[COMMA_2] = COMMA_STR;
	actual_time_string[SEC_TENTS] = secs_temp[TENTS];
	actual_time_string[SEC_UNITS] = secs_temp[UNITS];
	actual_time_string[FINISHER_1] = '\0';
	UART_put_string(terminal, actual_time_string);
}

void Date_to_String_cast(uart_channel_t terminal)
{
	char actual_date_string[CHARS_DT];
	uint8_t* day_temp;
	uint8_t* month_temp;
	uint8_t* year_temp;

	Date actual_date = get_date();
	Date_to_String(actual_date.day, DAY);
	Date_to_String(actual_date.month, MONTH);
	Date_to_String(actual_date.year, YEAR);
	day_temp = Get_String_Date(DAY);
	month_temp = Get_String_Date(MONTH);
	year_temp = Get_String_Date(YEAR);
	actual_date_string[DAY_TENTS] = day_temp[TENTS];
	actual_date_string[DAY_UNITS] = day_temp[UNITS];
	actual_date_string[SLASH_1] = SLASH_STR;
	actual_date_string[MONTH_TENTS] = month_temp[TENTS];
	actual_date_string[MONTH_UNITS] = month_temp[UNITS];
	actual_date_string[SLASH_2] = SLASH_STR;
	actual_date_string[YEAR_THOUSANDS] = TWO_STR;
	actual_date_string[YEAR_HUNDRETHS] = ZERO_STR;
	actual_date_string[YEAR_TENTS] = year_temp[TENTS];
	actual_date_string[YEAR_UNITS] = year_temp[UNITS];
	actual_date_string[FINISHER_2] = '\0';

	UART_put_string(terminal, actual_date_string);
}
