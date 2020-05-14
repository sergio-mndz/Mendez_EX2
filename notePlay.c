/*
 * notePlay.c
 *
 *  Created on: May 14, 2020
 *      Author: sergio_mndz
 */

#include "DMA.h"
#include "Bits.h"
#include "PIT.h"
#include "notePlay.h"
#include "stdio.h"
#include "MK64F12.h"

void initPlayer()
{
	DMA_clock_gating();
	DMA_init();
	PIT_init();
}

void play_Signal()
{
	uint8_t DMA_full = DMA_SADDR_Check();
	if(TRUE == DMA_full)
	{
		DMA_SADDR_Reset();
	}
}
