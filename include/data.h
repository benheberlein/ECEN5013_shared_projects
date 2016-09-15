/**********************************************************
* Name: data.h
* 
* Date: 9/14/16
*
* Description: This module contains several data 
* manipulation functions.
*
* Author: Ben Heberlein
*
**********************************************************/

#ifndef DATA_H
#define DATA_H

#include "stdint.h"

int8_t *my_itoa(int8_t *src, int32_t data, int32_t length);

int32_t my_atoi(int8_t *str);

void dump_memory(uint8_t *start, uint32_t length);

uint32_t big_to_little(uint32_t data);

uint32_t little_to_big(uint32_t data);

#endif
