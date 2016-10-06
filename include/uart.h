/**********************************************************
* Name: uart.h
*
* Date: 10/1/16
*
* Description: This module defines the UART interface
*
* Author: Ben Heberlein
*
***********************************************************/

#include <stdint.h>

uint8_t init_uart();

uint8_t tx_char(uint8_t ch);

uint8_t tx_string(uint8_t *str, int32_t length);
