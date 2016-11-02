/**********************************************************
* Name: SPI.h
*
* Date: 11/1/16
*
* Description: This module defines the SPI interface
*
* Author: Jeff Venicx
*
***********************************************************/

#ifndef UART_H
#define UART_H

#include <stdint.h>

void spi_init();

void spi_send(char spiMsg);

void spi_tx();

void spi_flush();


#endif
