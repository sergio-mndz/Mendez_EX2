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
#define DELAY_A 0.0005
#define DELAY_S 0.0004
#define DELAY_D 0.00033
#define DELAY_F 0.00028
#define DELAY_G 0.00025
#define DELAY_H 0.00022
#define DELAY_J 0.0002
#define DELAY_NOTE 1.0

extern uint8_t pit1_inter_status;

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
	PIT_delayFloat(PIT_1, SYS_CLK, DELAY_NOTE);
	switch(note)
	{
	case LETTER_A:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_A);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	case LETTER_S:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_S);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	case LETTER_D:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_D);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	case LETTER_F:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_F);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	case LETTER_G:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_G);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	case LETTER_H:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_H);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	case LETTER_J:
		PIT_delayFloat(PIT_0 , SYS_CLK, DELAY_J);
		initPlayer();
		while(FALSE == pit1_inter_status){
			play_Signal();
		}
		DMA_disable();
		break;
	}
}

void play_Sequence(uint8_t* array, uint8_t len)
{
	for(uint8_t i=0; i<len; i++)
	{
		play_Manual(array[i]);
	}
}
