 /**
 * @file    Examen2.c
 * @brief   Application entry point.
 */

#include <stdio.h>

#define DELAY_PIT 0.0001
#define MAN_MODE 1
#define SEQ_MODE 2
#define LETTER_A 97
#define LETTER_S 115
#define LETTER_D 100
#define LETTER_F 102
#define LETTER_G 103
#define LETTER_H 104
#define LETTER_J 106
#define ENTER_CHAR 13
#define ESC_CHAR 27
#define MAX_NOTES 10

#include "MK64F12.h"
#include "DAC.h"
#include "Bits.h"
#include "DMA.h"
#include "GPIO.h"
#include "notePlay.h"
#include "NVIC.h"
#include "PIT.h"
#include "String_conversion.h"
#include "TeraTerm_Display.h"
#include "UART.h"

typedef enum {
	MENU_ST,
	MANUAL_ST,
	SEQUENCE_ST
} Menu_states_t;

Menu_states_t menu_state(uart_channel_t terminal);

Menu_states_t manual_state(uart_channel_t terminal);

Menu_states_t sequence_state(uart_channel_t terminal);

uint8_t g_notes[10];

int main(void) {

	Menu_states_t (* state_function[]) (uart_channel_t) =
	{
			menu_state,
			manual_state,
			sequence_state
	};

	terminal_init(UART_0, SYSTEM_CLOCK, BD_115200);


	Menu_states_t term_state = MENU_ST;

	DAC_clock_gating();
	DAC_init();
	NVIC_enable_interrupt_and_priotity(DMA_CH0_IRQ, PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_6);
	NVIC_global_enable_interrupts;

    while(1) {
    	term_state = state_function[term_state](UART_0);
    }
    return 0 ;
}



Menu_states_t menu_state(uart_channel_t terminal)
{
	static uint8_t menu_initialized = FALSE;
	Menu_states_t state = MENU_ST;

	if(FALSE == menu_initialized)
	{
		UART_put_string(terminal, "\033[2J");
		UART_put_string(terminal, "\033[38;5;202m");
		UART_put_string(terminal, "\033[48;5;15m");
		UART_put_string(terminal, "\033[H");
		UART_put_string(terminal, "1) Modo manual\r\n");
		UART_put_string(terminal, "2) Modo secuencia\r\n");
		UART_put_string(terminal, "\r\n");
		menu_initialized = TRUE;
	}

	if(UART_MailBoxFlag(terminal))
	{
		/* Moves the mailbox data to start in 0 */
		uint8_t data = UART_MailBoxData(terminal) - '0';
		/* Checks if it's a valid value */
		if(MAN_MODE == data)
		{
			menu_initialized = FALSE;
			state = MANUAL_ST;

		}
		else if(SEQ_MODE == data)
		{
			menu_initialized = FALSE;
			state = SEQUENCE_ST;
		}
	}
	return state;
}


Menu_states_t manual_state(uart_channel_t terminal)
{
	static uint8_t manual_menu_initialized = FALSE;
	Menu_states_t state = MANUAL_ST;

	if(FALSE == manual_menu_initialized)
	{
		showManual_Display(terminal);
		manual_menu_initialized = TRUE;
	}

	if(UART_MailBoxFlag(terminal))
	{
		uint8_t data = UART_MailBoxData(terminal);
		if(data == LETTER_A || data == LETTER_S || data == LETTER_D ||
		   data == LETTER_F || data == LETTER_G || data == LETTER_H ||
		   data == LETTER_J)
		{
			play_Manual(data);
		}
		else if(data == ESC_CHAR)
		{
			DMA_disable();
			manual_menu_initialized = FALSE;
			state = MENU_ST;
		}
	}
	return state;
}

Menu_states_t sequence_state(uart_channel_t terminal)
{
	static uint8_t sequence_menu_initialized = FALSE;
	static uint8_t counter = 0;
	Menu_states_t state = SEQUENCE_ST;

	if(FALSE == sequence_menu_initialized)
	{
		showSequence_Display(terminal);
		sequence_menu_initialized = FALSE;
	}

	if(UART_MailBoxFlag(terminal))
	{
		uint8_t data = UART_MailBoxData(terminal);
		if(data == LETTER_A || data == LETTER_S || data == LETTER_D ||
		   data == LETTER_F || data == LETTER_G || data == LETTER_H ||
		   data == LETTER_J)
		{
			if(counter < MAX_NOTES)
			{
				g_notes[counter] = data;
				counter++;
			}
		}
		else if(ESC_CHAR == data)
		{
			sequence_menu_initialized = FALSE;
			state = MENU_ST;
		}
		else if(ENTER_CHAR == data)
		{
			play_Sequence(&g_notes[0], counter);
		}
	}
	return state;
}
