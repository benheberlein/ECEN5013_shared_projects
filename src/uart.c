/**********************************************************
* Name: uart.c
*
* Date: 10/1/2016
*
* Description: This module contains implementations for
* UART functions
*
* Author: Ben Heberlein
*
***********************************************************/
#include "MKL25Z4.h"
#include <stdint.h>

#define BAUD_RATE 	115200
#define OVERSAMPLE 	16

uint8_t init_uart() {
	// Enable port A
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	// Enable UART Rx on pin PTA1
	PORTA_PCR1 = PORT_PCR_MUX(0x2);
	// Enable UART Tx on pin PTA2
	PORTA_PCR2 = PORT_PCR_MUX(0x2);
	// Set MCGFLLCLK as UART0 clock source
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	// Open the UART0 clock gate
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

	// Find division to put in Baud registers
	uint16_t div = SystemCoreClock / OVERSAMPLE / BAUD_RATE;
	// Set oversampling, should be constant
    UART0_C4 = UARTLP_C4_OSR(OVERSAMPLE-1);
    // Set Baud registers
    UART0_BDH = (div >> 8) & UARTLP_BDH_SBR_MASK;
    UART0_BDL = div & UARTLP_BDL_SBR_MASK;

    // Enable Rx and Tx
    UART0_C2 |= UART0_C2_RE_MASK | UART0_C2_TE_MASK;

	// Enable Rx interrupt
    UART0_C2 |= UART0_C2_RIE_MASK;
    NVIC_EnableIRQ(UART0_IRQn);
}

uint8_t tx_char(uint8_t ch) {
	// There is room in the tx register
	while(!(UART0_S1_REG(UART0_BASE_PTR) & UART0_S1_TDRE_MASK)){};

	// Write the character to the data register
	UART0_D_REG(UART0_BASE_PTR) = ch;
}

uint8_t tx_string(uint8_t *str) {
	while(*str) {
		tx_char(*str++);
	}
}

void UART0_IRQHandler (void) {
  uint8_t ch = 0;
  if (UART0_S1 & UART_S1_RDRF_MASK) {
    ch = UART0_D;
  }
  tx_char(ch);
}
