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

	PORTC_PCR8 |= PORT_PCR_MUX(0x01);  //Set PTC8 to mux 1 [SPI0_PCS0]
	//PORTC_PCR4 = PORT_PCR_MUX(0x2);    //Set PTC4 to mux 2 [SPI0_PCS0]
	PORTC_PCR5 = PORT_PCR_MUX(0x2);    //Set PTC5 to mux 2 [SPI0_SCK]
	PORTC_PCR6 = PORT_PCR_MUX(0x2);    //Set PTC6 to mux 2 [SPI0_MOSI]
	PORTC_PCR7 = PORT_PCR_MUX(0x2);    //Set PTC7 to mux 2 [SPIO_MISO]

	// Set port C, pin 8 data direction to output
	PTC_BASE_PTR->PDDR |= 1<<8;

	//Enable SPI0
	SPI0_C1 = SPI_C1_SPE_MASK;

	//Set SPI0 to Master & SS pin to auto SS. now its general io
	SPI0_C1 |= SPI_C1_MSTR_MASK; //| SPI_C1_SSOE_MASK;

	//Master SS pin acts as slave select output
	SPI0_C2 = SPI_C2_MODFEN_MASK;

	//Set baud rate prescale divisor to 3 & set baud rate divisor to 2 for baud rate of 250 khz
	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0b0010));

	//set SS pin to high
	PTC_BASE_PTR->PSOR |= 1<<8;
}





void spi_send_uint8(uint8_t data){
	//wait for tx buffer to clear
	while(!(SPI0_S & SPI_S_SPTEF_MASK))
	{
		__NOP;
	}
	//send data
	SPI0_D = data;
}




void SPI0_handler(void){



}
