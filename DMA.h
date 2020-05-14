/*
 * DMA.h
 *
 *  Created on: May 10, 2020
 *      Author: sergio_mndz
 */

#ifndef DIAZ_DE_SANDI_MENDEZ_P4_DMA_H_
#define DIAZ_DE_SANDI_MENDEZ_P4_DMA_H_
#include "stdint.h"

#define SYSTEM_CLOCK (21000000u)

void DMA_clock_gating(void);

void DMA_init(void);

void DMA_SADDR_Reset();

uint8_t DMA_SADDR_Check();

#endif /* DIAZ_DE_SANDI_MENDEZ_P4_DMA_H_ */
