/*
 * @file:			UART.c
 * @company:		ITESO
 * @Engineer Team:	K.C.D - S.A.M.
 */

#include "UART.h"
#include "stdint.h"

uart_mail_box_t g_mail_box_uart_0 = {};
uart_mail_box_t g_mail_box_uart_4 = {};

void UART0_RX_TX_IRQHandler( )
{
	uint32_t temp = UART0->S1;
	g_mail_box_uart_0.mailBox = UART0->D;
	g_mail_box_uart_0.flag = 1;
//	UART_put_char(UART_0, g_mail_box_uart_0.mailBox);
}

void UART4_RX_TX_IRQHandler( )
{
	uint32_t temp = UART4->S1;
	g_mail_box_uart_4.mailBox = UART4->D;
	g_mail_box_uart_4.flag = 1;
//	UART_put_char (UART_4, g_mail_box_uart_4.mailBox);
}

void UART_init(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate)
{
	if (UART_0 == uart_channel)
	{
		/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
		SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		/**Configures the pin control register of pin16 in PortB as UART RX*/
		PORTB->PCR[16] = PORT_PCR_MUX(3);
		/**Configures the pin control register of pin16 in PortB as UART TX*/
		PORTB->PCR[17] = PORT_PCR_MUX(3);

		UART0->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
		UART0->C1 = 0;

		uint32_t BR = 0;
		BR = system_clk / (16*baud_rate);
		UART0->BDL = (BR & UART_BDL_SBR_MASK);
		UART0->BDH = BR>>8;

		uint32_t BRFD = 0;
		uint32_t BRFA = BRFD*32;
		UART0->C4 = (UART_C4_BRFA_MASK & ~UART_C4_BRFA_MASK) | BRFA;
		UART0->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;

		NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);
	}
	if (UART_4 == uart_channel)
	{
		SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
		SIM->SCGC5 = SIM_SCGC5_PORTC_MASK;
		PORTC->PCR[14] = PORT_PCR_MUX(3);
		PORTC->PCR[15] = PORT_PCR_MUX(3);

		UART4->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
		UART4->C1 = 0;

		if(BD_115200 == baud_rate)
		{
			uint32_t BR = 11;
			UART4->BDL = (BR & UART_BDL_SBR_MASK);
			UART4->BDH = BR>>8;

			uint32_t BRFA = 15;
			UART4->C4 = (UART_C4_BRFA_MASK & ~UART_C4_BRFA_MASK) | BRFA;
		}
		else if(BD_9600 == baud_rate)
		{
			uint32_t BR = 393;
			UART4->BDL = (BR & UART_BDL_SBR_MASK);
			UART4->BDH = BR>>8;
		}

		UART4->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;

		NVIC_enable_interrupt_and_priotity(UART4_IRQ, PRIORITY_10);
	}

	NVIC_global_enable_interrupts;
}

void UART_interrupt_enable(uart_channel_t uart_channel)
{
	if (UART_0 == uart_channel)
	{
		UART0->C2 |= UART_C2_RIE_MASK;
//		SIM->SCGC5 = SIM_SCGC5_PORTC_MASK;
	}
	if (UART_4 == uart_channel) {
		UART4->C2 |= UART_C2_RIE_MASK;
	}
}

void UART_put_char(uart_channel_t uart_channel, uint8_t character)
{
	if (UART_0 == uart_channel)
	{
		/* Blocking code to ensure the end of transmissio */
		while (!(UART0->S1 & UART_S1_TC_MASK))
		{
			// Nothing until the flag is active
		}
		UART0->D = character;
	}
	else if (UART_4 == uart_channel)
	{
		/* Blocking code to ensure the end of transmissio */
		while (!(UART4->S1 & UART_S1_TC_MASK))
		{
			// Nothing until the flag is active
		}
		UART4->D = character;
	}
}

void UART_put_string(uart_channel_t uart_channel, char* string)
{
//	while(*string)
//	UART_put_char(uart_channel, *string++);
	uint8_t counter = 0;
	while (1)
	{
		if (string[counter] == '\0')
		{
			break;
		}
		UART_put_char(uart_channel, string[counter]);
		counter++;
	}
}

uint8_t UART_MailBoxFlag(uart_channel_t uart_channel)
{
	uint8_t flag = 0;
	if (UART_0 == uart_channel)
	{
		flag = g_mail_box_uart_0.flag;
	}
	else if(UART_4 == uart_channel)
	{
		flag = g_mail_box_uart_4.flag;
	}

	return flag;

}

uint8_t UART_MailBoxData(uart_channel_t uart_channel)
{
	if(UART_0 == uart_channel)
	{
		g_mail_box_uart_0.flag = 0;
		return g_mail_box_uart_0.mailBox;
	}
	else if(UART_4 == uart_channel)
	{
		g_mail_box_uart_4.flag = 0;
		return g_mail_box_uart_4.mailBox;
	}
	else {
		return 0;
	}
}

