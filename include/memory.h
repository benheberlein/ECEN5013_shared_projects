/**********************************************************
* Name: memory.h
* 
* Date: 9/14/16
*
* Description: This module contains several memory 
* manipulation functions.
*
* Author: Ben Heberlein
*
***********************************************************/

#ifndef MEMORY_H
#define MEMORY_H

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length);

int8_t my_memzero(uint8_t *src, uint32_t length);

int8_t my_reverse(uint8_t *src, uint32_t length);

#endif
