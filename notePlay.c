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

#define LETTER_A 97
#define LETTER_S 115
#define LETTER_D 100
#define LETTER_F 102
#define LETTER_G 103
#define LETTER_H 104
#define LETTER_J 106

#define SYS_CLK 21000000
#define DELAY_A 0.001
#define DELAY_S 0.000875
#define DELAY_D 0.00075
#define DELAY_F 0.00625
#define DELAY_G 0.0005
#define DELAY_H 0.000375
#define DELAY_J 0.000250

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

void play_Manual(uint8_t note)
{
	switch(note)
	{
	case LETTER_A:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_A);
		break;
	case LETTER_S:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_S);
		break;
	case LETTER_D:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_D);
		break;
	case LETTER_F:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_F);
		break;
	case LETTER_G:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_G);
		break;
	case LETTER_H:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_H);
		break;
	case LETTER_J:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_J);
		break;
	}
}
