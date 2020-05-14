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

/*
 \ brief An enumeration of the values in each term of the time array
 */
typedef enum{
	HOUR_TENTS,
	HOUR_UNITS,
	COMMA_1,
	MIN_TENTS,
	MIN_UNITS,
	COMMA_2,
	SEC_TENTS,
	SEC_UNITS,
	FINISHER_1
}array_position_t;

/*
 \ brief An enumeration of the values in each term of the date array
 */
typedef enum{
	DAY_TENTS,
	DAY_UNITS,
	SLASH_1,
	MONTH_TENTS,
	MONTH_UNITS,
	SLASH_2,
	YEAR_THOUSANDS,
	YEAR_HUNDRETHS,
	YEAR_TENTS,
	YEAR_UNITS,
	FINISHER_2
}arra_position_date_t;

/*
 \ brief An enumeration for the position of the two char strings
 */
typedef enum{
	TENTS,
	UNITS
}units_tents_str_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function initializes the UART that will function as the main terminal,
 	 \	setting the channel, the clock and the baud rate

 	 \param[in] uart_channel, the value that corresponds to one of the UART channels
 	 \param[in] system_clk, the int value corresponing to the clock frequency of the system
 	 \param[in] baud_rate, the value that would be the baud rate of the UART communication
 	 \return void
 */
void terminal_init(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function configure and displays the first lines of the read hour mode

 	 \param[in] terminal, the value that corresponds to the uart channel of the terminal
 	 \return void
 */
void showHour_Display(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function configure and displays the first lines of the set hour mode

 	 \param[in] terminal, the value that corresponds to the uart channel of the terminal
 	 \return void
 */
void setHour_Display(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function configure and displays the first lines of the read date mode

 	 \param[in] terminal, the value that corresponds to the uart channel of the terminal
 	 \return void
 */
void showDate_Display(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function configure and displays the first lines of the set date mode

 	 \param[in] terminal, the value that corresponds to the uart channel of the terminal
 	 \return void
 */
void setDate_Display(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function displays the hour that is stored at the moment in the rtc

 	 \param[in] terminal, the value that corresponds to the uart channel of the terminal
 	 \return void
 */
void show_Hour(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function displays the date that is stored at the moment in the rtc

 	 \param[in] terminal, the value that corresponds to the uart channel of the terminal
 	 \return void
 */
void show_Date(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function captures the values received from the terminal that correspond
 	 \			to the new hour to be set in the RTC, it has the format HH:MM:SS

 	 \param[in] terminal, the value that corresponds to the UART channel of the terminal
 	 \param[in] data, the string that will contain the values received from the UART terminal
 	 \			to be assigned to the RTC
 	 \return void
 */
void write_Hour(uart_channel_t terminal, uint8_t * data);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function captures the values received from the terminal that correspond
 	 \			to the new date to be set in the RTC, it has the format DD:MM:YY

 	 \param[in] terminal, the value that corresponds to the UART channel of the terminal
 	 \param[in] data, the string that will contain the values received from the UART terminal
 	 \			to be assigned to the RTC
 	 \return void
 */
void write_Date(uart_channel_t terminal, uint8_t * data);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function realizes the cast of the hour values in the rtc to convert them to
 	 \		the corresponding string to be shown on the terminal

 	 \param[in] terminal, the value that corresponds to the UART channel of the terminal
 	 \return void
 */
void Hour_to_String_cast(uart_channel_t terminal);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function realizes the cast of the date values in the rtc to convert them to
 	 \		the corresponding string to be shown on the terminal

 	 \param[in] terminal, the value that corresponds to the UART channel of the terminal
 	 \return void
 */
void Date_to_String_cast(uart_channel_t terminal);

#endif /* DIAZ_DE_SANDI_MENDEZ_T13_TERATERM_DISPLAY_H_ */
