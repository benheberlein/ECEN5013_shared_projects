/**********************************************************
* Name: dma.c
*
* Date: 10/25/2016
*
* Description: This module contains implementations of DMA
* control functions
*
* Author: Ben Heberlein
*
***********************************************************/

#include "dma.h"
#include <stdint.h>
#include "MKL25Z4.h"
#include "log.h"

volatile uint8_t ready_flag;

/* Initialization function for DMA control */
int8_t dma_init() {

	ready_flag = 1;

	// Set clock gate to DMA module
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	// Enable interrupt
	DMA_DCR0 |= DMA_DCR_EINT_MASK;

	NVIC_EnableIRQ(DMA0_IRQn);
}


/* Start a DMA transfer */
int8_t dma_start(uint8_t *src, uint8_t *dst, uint8_t chunk_size, uint32_t len) {
	// Spin while DMA is busy
	if (!(chunk_size == 1 || chunk_size == 2 || chunk_size == 4)) {
		Log0("DMA transfer was started with invalid byte size.", 49);
		return -1;
	}

	if (len >= 1<<24) {
		Log0("DMA transfer too large.", 23);
		return -2;
	}

	while(!ready_flag){
		__NOP;
	}
	DMA_SAR0 = (uint32_t) src;
	DMA_DAR0 = (uint32_t) dst;
	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR0 |= (len & DMA_DSR_BCR_BCR_MASK);

	// Check for valid configuration
	if (DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) {
		Log0("Invalid DMA configuration. Transfer aborted.", 44);
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
		return -3;
	}

	DMA_DCR0 &= ~DMA_DCR_SSIZE_MASK;
	DMA_DCR0 &= ~DMA_DCR_DSIZE_MASK;
	if (chunk_size == 1) {
		DMA_DCR0 |= DMA_DCR_SSIZE(1);
		DMA_DCR0 |= DMA_DCR_DSIZE(1);
	} else if (chunk_size == 2) {
		DMA_DCR0 |= DMA_DCR_SSIZE(2);
		DMA_DCR0 |= DMA_DCR_DSIZE(2);
	}

	DMA_DCR0 |= DMA_DCR_SINC_MASK;
	DMA_DCR0 |= DMA_DCR_DINC_MASK;

	// Set transfer flag
	ready_flag = 0;

	DMA_DCR0 |= DMA_DCR_START_MASK;

}

void DMA0_IRQHandler(void) {
	if (DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) {
		Log0("Invalid DMA transfer. Data may be incomplete.", 45);
	}

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	ready_flag = 1;
}
