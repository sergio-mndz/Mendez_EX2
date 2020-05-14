/*
 * DAC.c
 *
 *  Created on: May 10, 2020
 *      Author: sergio_mndz
 */

#include "DAC.h"
#include "Bits.h"
#include "MK64F12.h"

void DAC_clock_gating()
{
	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
}

void DAC_init()
{
	DAC0->C0 |= DAC_C0_DACRFS_MASK | DAC_C0_DACEN_MASK;
	DAC0->DAT[0].DATL = 0;
	DAC0->DAT[0].DATH = 0;
}
