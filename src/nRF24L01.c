/**********************************************************
* Name: nRF24L01.c
*
* Date: 10/1/2016
*
* Description: This module contains implementations for
* nRF24L01 interface functions
*
* Author: Jeff Venicx
*
***********************************************************/
#include "nRF24L01.h"
#include "MKL25Z4.h"
#include "SPI.h"
#include <stdint.h>
#include <stdlib.h>

#define NRF_SS_ENABLE (PTC_BASE_PTR->PCOR |= 1<<8)
#define NRF_SS_DISABLE (PTC_BASE_PTR->PSOR |= 1<<8)

#define SPI_WAIT_SPTEF (!(SPI0_S & SPI_S_SPTEF_MASK))
#define SPI_WAIT_SPRF (!(SPI0_S & SPI_S_SPRF_MASK))


uint8_t nrf_get_status(){

	uint8_t sreg = 0;
	NRF_SS_ENABLE;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send NOP
	SPI0_D = NRF_NOP;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	sreg = SPI0_D;
	NRF_SS_DISABLE;
	return sreg;
}

uint8_t nrf_get_config(){
	uint8_t sreg = 0;
	uint8_t creg = 0;
	NRF_SS_ENABLE;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send read config command
	SPI0_D = (NRF_RD_CMD|NRF_CONFIG_REG);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store status register
	sreg = SPI0_D;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send NOP
	SPI0_D = NRF_NOP;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store config register
	creg = SPI0_D;

	NRF_SS_DISABLE;
	return creg;
}

uint8_t nrf_write_config(uint8_t val){

	uint8_t sreg = 0, tmp;

	NRF_SS_ENABLE;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send write config command
	SPI0_D = (NRF_CONFIG_REG|NRF_WR_CMD);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store status register
	sreg = SPI0_D;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send NOP
	SPI0_D = val;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);
    tmp = SPI0_D;

	NRF_SS_DISABLE;
	return sreg;
}

uint8_t nrf_read_tx_addr(uint8_t * address){

	uint8_t sreg = 0;

	NRF_SS_ENABLE;

	while(SPI_WAIT_SPTEF);

	SPI0_D = (NRF_RD_CMD|NRF_TX_ADDR_REG);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store status register
	sreg = SPI0_D;

	for(int i=0; i < 5; i++){
		//wait for tx to fill
		while(SPI_WAIT_SPTEF);

		//write nop code for clock ticks
		SPI0_D = NRF_NOP;

		//wait for rx to fill
		while(SPI_WAIT_SPRF);

		//write address
		address[i] = SPI0_D;
	}

	NRF_SS_DISABLE;
	return sreg;
}

uint8_t nrf_write_tx_addr(uint8_t * address){

	uint8_t sreg = 0, tmp;

	NRF_SS_ENABLE;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//transmit write command
	SPI0_D = (NRF_WR_CMD|NRF_TX_ADDR_REG);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);
	sreg = SPI0_D;

	//transmit tx address
	for(int i=0 ; i<5; i++){
		while(SPI_WAIT_SPTEF);
		SPI0_D = address[i];

		while(SPI_WAIT_SPTEF);

		//wait for Read buffer to fill
		while(SPI_WAIT_SPRF);
		tmp = SPI0_D;
	}

	//send NOP command
	SPI0_D = NRF_NOP;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);
    tmp = SPI0_D;

	NRF_SS_DISABLE;
    return tmp;

}

uint8_t nrf_read_rf_setup(){

	uint8_t sreg,rfreg;

	NRF_SS_ENABLE;

	while(SPI_WAIT_SPTEF);

	SPI0_D = (NRF_RD_CMD|NRF_RF_SETUP_REG);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store status register
	sreg = SPI0_D;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send NOP
	SPI0_D = NRF_NOP;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store rf setup register
	rfreg = SPI0_D;


	NRF_SS_DISABLE;
	return rfreg;
}

uint8_t nrf_write_rf_setup_power(uint8_t POWER_LEVEL){

	uint8_t sreg = 0, tmp;

	NRF_SS_ENABLE;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send write config command
	SPI0_D = (NRF_WR_CMD|NRF_RF_SETUP_REG);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store status register
	sreg = SPI0_D;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send power level
	SPI0_D = POWER_LEVEL;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);
    tmp = SPI0_D;

	NRF_SS_DISABLE;
	return sreg;
}

uint8_t nrf_get_fifo_status(){
	uint8_t sreg = 0;
	uint8_t fiforeg = 0;
	NRF_SS_ENABLE;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send read config command
	SPI0_D = (NRF_RD_CMD|NRF_FIFO_STATUS_REG);

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store status register
	sreg = SPI0_D;

	//check tx buffer
	while(SPI_WAIT_SPTEF);

	//send NOP
	SPI0_D = NRF_NOP;

	//wait for Read buffer to fill
	while(SPI_WAIT_SPRF);

	//store fifo_status register
	fiforeg = SPI0_D;

	NRF_SS_DISABLE;
	return fiforeg;
}


