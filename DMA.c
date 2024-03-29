/*
 * DMA.c
 *
 *  Created on: May 10, 2020
 *      Author: sergio_mndz
 */

#include "DMA.h"
#include "MK64F12.h"
#include "Bits.h"
#include <stdio.h>

#define NUM_STEPS (1u)
#define DMA_CH0 (0x01u)
#define DMA_SOURCE_MUX (63u)
#define SRC_OFFST (1u)
#define WRD_WDTH (2u)
#define MAX 160
#define ZERO_N 0

const uint16_t DAC_SineWave[MAX] =
{
		0x7d0,0x81f,0x86d,0x8bb,0x909,0x956,0x9a3,0x9ef,
		0xa3a,0xa84,0xacd,0xb15,0xb5c,0xba1,0xbe5,0xc27,
		0xc68,0xca6,0xce3,0xd1e,0xd56,0xd8d,0xdc1,0xdf3,
		0xe22,0xe4f,0xe79,0xea1,0xec6,0xee8,0xf08,0xf24,
		0xf3e,0xf55,0xf69,0xf7a,0xf87,0xf92,0xf9a,0xf9e,
		0xfa0,0xf9e,0xf9a,0xf92,0xf87,0xf7a,0xf69,0xf55,
		0xf3e,0xf24,0xf08,0xee8,0xec6,0xea1,0xe79,0xe4f,
		0xe22,0xdf3,0xdc1,0xd8d,0xd56,0xd1e,0xce3,0xca6,
		0xc68,0xc27,0xbe5,0xba1,0xb5c,0xb15,0xacd,0xa84,
		0xa3a,0x9ef,0x9a3,0x956,0x909,0x8bb,0x86d,0x81f,
		0x7d0,0x781,0x733,0x6e5,0x697,0x64a,0x5fd,0x5b1,
		0x566,0x51c,0x4d3,0x48b,0x444,0x3ff,0x3bb,0x379,
		0x338,0x2fa,0x2bd,0x282,0x24a,0x213,0x1df,0x1ad,
		0x17e,0x151,0x127,0xff ,0xda ,0xb8 ,0x98 ,0x7c,
		0x62 ,0x4b ,0x37 ,0x26 ,0x19 ,0xe  ,0x6  ,0x2,
		0x0  ,0x2  ,0x6  ,0xe  ,0x19 ,0x26 ,0x37 ,0x4b,
		0x62 ,0x7c ,0x98 ,0xb8 ,0xda ,0xff ,0x127,0x151,
		0x17e,0x1ad,0x1df,0x213,0x24a,0x282,0x2bd,0x2fa,
		0x338,0x379,0x3bb,0x3ff,0x444,0x48b,0x4d3,0x51c,
		0x566,0x5b1,0x5fd,0x64a,0x697,0x6e5,0x733,0x781,
};

void DMA_clock_gating(void)
{
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}

void DMA_init(void)
{
	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_TRIG_MASK |
					   DMAMUX_CHCFG_SOURCE(DMA_SOURCE_MUX);;


	DMA0->ERQ = 0x01;//enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t)(&DAC_SineWave[0]);
	DMA0->TCD[0].SOFF = SRC_OFFST*WRD_WDTH;


	DMA0->TCD[0].DADDR = (uint32_t)(&DAC0->DAT[0].DATL);
	DMA0->TCD[0].DOFF = 1;

	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);
	DMA0->TCD[0].NBYTES_MLNO = 2 ;

	DMA0->TCD[0].ATTR = DMA_ATTR_SSIZE(1);
	DMA0->TCD[0].SLAST = 0 ;
	DMA0->TCD[0].DLAST_SGA =  -2;
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;
}

void DMA0_IRQHandler(void)
{
	DMA0->INT = DMA_CH0;
}

void DMA_SADDR_Reset()
{
	DMA0->TCD[0].SADDR =(uint32_t) &(DAC_SineWave[ZERO_N]);
}

uint8_t DMA_SADDR_Check()
{
	return (uint8_t) (DMA0->TCD[0].SADDR >= (uint32_t)&(DAC_SineWave[MAX-4]));
}

void DMA_disable()
{
	DMAMUX->CHCFG[0] = ~DMAMUX_CHCFG_ENBL_MASK;
}
