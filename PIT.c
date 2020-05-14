
#include "MK64F12.h"
#include "PIT.h"
#include "Bits.h"
#define SYSTEM_CLOCK (21000000U)
#define DELAY (0.00050)

static void (*PIT_0_callback)(void) = 0;
static void (*PIT_1_callback)(void) = 0;
static void (*PIT_2_callback)(void) = 0;
static void (*PIT_3_callback)(void) = 0;

static PIT_interrupt_flags_t g_intrPIT_status_flag = {0};
uint8_t pit1_inter_status = FALSE;

void PIT_callback_init(PIT_timer_t pit_timer, void (*handler)(void)) {
	if (PIT_0 == pit_timer) {
		PIT_0_callback = handler;
	}
	if (PIT_1 == pit_timer) {
		PIT_1_callback = handler;
	}
	if (PIT_2 == pit_timer) {
		PIT_2_callback = handler;
	}
	if (PIT_3 == pit_timer) {
		PIT_3_callback = handler;
	}
}

void PIT0_IRQHandler(void)
{
	g_intrPIT_status_flag.flag_PIT_channel_0 = TRUE;
	PIT_clear_interrupt(PIT_0);
}

void PIT1_IRQHandler(void)
{
	pit1_inter_status = TRUE;
	g_intrPIT_status_flag.flag_PIT_channel_1 = TRUE;
	PIT_clear_interrupt(PIT_1);
}

void PIT2_IRQHandler(void)
{
	g_intrPIT_status_flag.flag_PIT_channel_2 = TRUE;
	PIT_clear_interrupt(PIT_2);
}

void PIT_clock_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;	// Set bit 23 - enable module PIT
}

void PIT_enable(void)
{
	PIT->MCR &= ~(0x02);	//PIT_MCR_MDIS_MASK;		// bit 1 - MDIS enable PIT section
}

void FRZ_enable(void)
{
	PIT->MCR |= PIT_MCR_FRZ_MASK;		// bit 0 - FRZ enable Mode Debug
}

void PIT_delayInteger(PIT_timer_t pit_timer, uint32_t system_clock, uint32_t delay)
{

	My_float_pit_t clock_PIT;		/*! This variable hold the PIT clock	  	*/
	My_float_pit_t period_PIT;		/*! This variable hold the PIT period	  	*/
	uint32_t cycles_number;			/*! This variable is the cycles to spend	*/

	clock_PIT = system_clock / 2;
	period_PIT = (My_float_pit_t)(1 / clock_PIT);

	cycles_number = (int)(delay / period_PIT);
	PIT->CHANNEL[pit_timer].LDVAL = cycles_number - 1; /** Load of number of cycles */
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TIE_MASK;// set TIE - enable interrupts Timer
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN_MASK;// set TEN - start Timer
}

void PIT_delayFloat(PIT_timer_t pit_timer, uint32_t system_clock, My_float_pit_t delay)
{

	My_float_pit_t clock_PIT;		/*! This variable hold the PIT clock	  	*/
	My_float_pit_t period_PIT;		/*! This variable hold the PIT period	  	*/
	uint32_t cycles_number;			/*! This variable is the cycles to spend	*/

	clock_PIT = system_clock / 2;
	period_PIT = (My_float_pit_t)(1 / clock_PIT);

	cycles_number = (int)(delay / period_PIT);
	PIT->CHANNEL[pit_timer].LDVAL = cycles_number - 1;
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void PIT_stop(PIT_timer_t pit_timer)
{
	if (PIT_0 == pit_timer) {
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
		}
		if (PIT_1 == pit_timer) {
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TEN_MASK);

		}
		if (PIT_2 == pit_timer) {
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TEN_MASK);

		}
		if (PIT_3 == pit_timer) {
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
		PIT->CHANNEL[pit_timer].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
		}
}
uint8_t PIT_get_irq_flag_status(PIT_timer_t pit_timer)
{
	uint8_t status = 0;

		// Esta es Software
	if (PIT_0 == pit_timer) {
		status = g_intrPIT_status_flag.flag_PIT_channel_0;
	}
	if (PIT_1 == pit_timer) {
		status = g_intrPIT_status_flag.flag_PIT_channel_1;
	}
	if (PIT_2 == pit_timer) {
		status = g_intrPIT_status_flag.flag_PIT_channel_2;
	}
	if (PIT_3 == pit_timer) {
		status = g_intrPIT_status_flag.flag_PIT_channel_3;
	}

	return (status);
}

void PIT_clear_irq_flag_status(PIT_timer_t pit_timer)
{
	if (PIT_0 == pit_timer) {
		g_intrPIT_status_flag.flag_PIT_channel_0 = FALSE;
	}
	if (PIT_1 == pit_timer) {
		g_intrPIT_status_flag.flag_PIT_channel_1 = FALSE;
	}
	if (PIT_2 == pit_timer) {
		g_intrPIT_status_flag.flag_PIT_channel_2 = FALSE;
	}
	if (PIT_3 == pit_timer) {
		g_intrPIT_status_flag.flag_PIT_channel_3 = FALSE;
	}
}

void PIT_clear_interrupt(PIT_timer_t pit_timer)
{
	PIT->CHANNEL[pit_timer].TFLG = TRUE;
}

void PIT_init(void){
	PIT_clock_gating();
	PIT_enable();

}
