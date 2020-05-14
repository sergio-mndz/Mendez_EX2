/*
 * String_conversion.c
 *
 *  Created on: Apr 10, 2020
 *      Author: sergio_mndz
 */

#include "String_conversion.h"

#define STRING_SECONDS &g_string_time_secs[0] // Seconds string address
#define STRING_MINUTES &g_string_time_mins[0] // Minutes string address
#define STRING_HOURS   &g_string_time_hrs[0]  // Hours string address
#define STRING_DAY	   &g_string_date_day[0]
#define STRING_MONTH   &g_string_date_month[0]
#define STRING_YEAR    &g_string_date_year[0]

uint8_t g_tents = 0;
uint8_t g_units = 0;

uint8_t g_string_time_secs[3] = "XX";
uint8_t g_string_time_mins[3] = "XX";
uint8_t g_string_time_hrs[3] =  "XX";

uint8_t g_string_date_day[3] = "XX";
uint8_t g_string_date_month[3] = "XX";
uint8_t g_string_date_year[3] = "XX";

uint8_t g_string_char = '0';

void Time_to_String(int32_t time_int, time_type_t type)
{

	g_tents = time_int/16;
	g_units = time_int - (g_tents*16);

	if(SEC == type)
	{
		g_string_time_secs[0] = Number_to_Char(g_tents);
		g_string_time_secs[1] = Number_to_Char(g_units);
	}
	if(MIN == type)
	{
		g_string_time_mins[0] = Number_to_Char(g_tents);
		g_string_time_mins[1] = Number_to_Char(g_units);
	}
	if(HOUR == type)
	{
		g_string_time_hrs[0] = Number_to_Char(g_tents);
		g_string_time_hrs[1] = Number_to_Char(g_units);
	}
}

void Date_to_String(uint32_t date_int, date_type_t type)
{
	g_tents = date_int/16;
	g_units = date_int - (g_tents*16);

	if(DAY == type)
	{
		g_string_date_day[0] = Number_to_Char(g_tents);
		g_string_date_day[1] = Number_to_Char(g_units);
	}
	if(MONTH == type)
	{
		g_string_date_month[0] = Number_to_Char(g_tents);
		g_string_date_month[1] = Number_to_Char(g_units);
	}
	if(YEAR == type)
	{
		g_string_date_year[0] = Number_to_Char(g_tents);
		g_string_date_year[1] = Number_to_Char(g_units);
	}
}

uint8_t* Get_String_Date(date_type_t type)
{
	if (DAY == type) {
		return STRING_DAY;
	}

	else if (MONTH == type) {
		return STRING_MONTH;
	}

	else if (YEAR == type) {
		return STRING_YEAR;
	}
	else
	{
		return 0;
	}
}

uint8_t* Get_String_Time(time_type_t type)
{
	if (SEC == type) {
		return STRING_SECONDS;
	}

	else if (MIN == type) {
		return STRING_MINUTES;
	}

	else if (HOUR == type) {
		return STRING_HOURS;
	}
	else
	{
		return 0;
	}
}

uint8_t Number_to_Char(uint8_t integer){
	switch(integer)
	{
		case ZERO:
			g_string_char = '0';
			break;
		case ONE:
			g_string_char = '1';
			break;
		case TWO:
			g_string_char = '2';
			break;
		case THREE:
			g_string_char = '3';
			break;
		case FOUR:
			g_string_char = '4';
			break;
		case FIVE:
			g_string_char = '5';
			break;
		case SIX:
			g_string_char = '6';
			break;
		case SEVEN:
			g_string_char = '7';
			break;
		case EIGHT:
			g_string_char = '8';
			break;
		case NINE:
			g_string_char = '9';
			break;
		default:
			break;
	}
	return g_string_char;
}

uint8_t Char_to_Number(uint8_t cha){
	uint8_t num;
	switch(cha)
	{
		case ZERO_STR:
			num = 0;
			break;
		case ONE_STR:
			num = 1;
			break;
		case TWO_STR:
			num = 2;
			break;
		case THREE_STR:
			num = 3;
			break;
		case FOUR_STR:
			num = 4;
			break;
		case FIVE_STR:
			num = 5;
			break;
		case SIX_STR:
			num = 6;
			break;
		case SEVEN_STR:
			num = 7;
			break;
		case EIGHT_STR:
			num = 8;
			break;
		case NINE_STR:
			num = 9;
			break;
		default:
			num = 0;
	}
	return num;
}
