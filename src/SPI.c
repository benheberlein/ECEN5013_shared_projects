/**********************************************************
* Name: SPI.c
*
* Date: 10/1/2016
*
* Description: This module contains implementations for
* SPI functions
*
* Author: Jeff Venicx
*
***********************************************************/
#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>


void spi_init(){

	//turn on clock to D module
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	//enable SPIO0
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	PORTC_PCR4 = PORT_PCR_MUX(0x2);    //Set PTC4 to mux 2 [SPI0_PCS0]
	PORTC_PCR5 = PORT_PCR_MUX(0x2);    //Set PTC5 to mux 2 [SPI0_SCK]
	PORTC_PCR6 = PORT_PCR_MUX(0x2);    //Set PTC6 to mux 2 [SPI0_MOSI]
	PORTC_PCR7 = PORT_PCR_MUX(0x2);    //Set PTC7 to mux 2 [SPIO_MISO]

	//Set SPI0 to Master & SS pin to auto SS
	SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;

	//Master SS pin acts as slave select output
	SPI0_C2 = SPI_C2_MODFEN_MASK;

	//Set baud rate prescale divisor to 3 & set baud rate divisor to 64 for baud rate of 15625 hz
	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));

	//Enable SPI0
	SPI0_C1 |= SPI_C1_SPE_MASK;

}


void spi_send(char spiMsg)
{

  while(!(SPI_S_SPTEF_MASK & SPI0_S))
  {
   __NOP;  //While buffer is not empty do nothing
  }

  SPI0_D = spiMsg;    //Write char to SPI

}
