/*
 * String_conversion.h
 *
 *  Created on: Apr 10, 2020
 *      Author: sergio_mndz
 */

#ifndef DIAZ_DE_SANDI_MENDEZ_T13_STRING_CONVERSION_H_
#define DIAZ_DE_SANDI_MENDEZ_T13_STRING_CONVERSION_H_

#include "stdint.h"

/*
 \ brief The different kind of values in an hour
 */
typedef enum {
	SEC,  MIN,  HOUR,
} time_type_t;

/*
 \ brief The different kind of values in a date
 */
typedef enum {
	DAY, MONTH, YEAR
} date_type_t;

/*
 \ brief The unit values as an enumeration
 */
typedef enum {
	ZERO, ONE, TWO, THREE, FOUR,
	FIVE, SIX, SEVEN, EIGHT, NINE,
} num_t ;

/*
 \ brief The corresponding values of the numbers in ASCII
 */
typedef enum {
	ZERO_STR = 48, ONE_STR, TWO_STR, THREE_STR, FOUR_STR,
	FIVE_STR, SIX_STR, SEVEN_STR, EIGHT_STR, NINE_STR
} num_string_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function converts the time data received into a string, and it is stored
 	 \		in a global string of the module

 	 \param[in] time_int, the hour value received
 	 \param[in] type, the type of hour value received, important to know to which global
 	 \			variable to assign the string
 	 \return void
 */
void Time_to_String(int32_t time_int, time_type_t type);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function converts the date data received into a string, and it is stored
 	 \		in a global string of the module

 	 \param[in] date_int, the date value received
 	 \param[in] type, the type of date value received, important to know to which global
 	 \			variable to assign the string
 	 \return void
 */
void Date_to_String(uint32_t date_int, date_type_t type);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function returns the string in which it's stored each kind of time data

 	 \param[in] type, the kind of time value which will be returned
 	 \return The string of the kind of time data requested
 */
uint8_t* Get_String_Time(time_type_t type);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function returns the string in which it's stored each kind of date data

 	 \param[in] type, the kind of date value which will be returned
 	 \return The string of the kind of date data requested
 */
uint8_t* Get_String_Date(date_type_t type);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function returns the char value in ASCII corresponding to the integer one
 	 \ digit value given

 	 \param[in] integer, a one digit integer value
 	 \return The ASCII value of the given integer
 */
uint8_t Number_to_Char(uint8_t integer);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function returns the integer value corresponding to the char value given
 	 \ in ASCII

 	 \param[in] cha, an ASCII value of one of the ten digits
 	 \return The integer value of the char given
 */
uint8_t Char_to_Number(uint8_t cha);

#endif /* DIAZ_DE_SANDI_MENDEZ_T13_STRING_CONVERSION_H_ */
