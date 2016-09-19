/**********************************************************
* Name: data.h
*
* Date: 9/14/16
*
* Description: This module contains several data
* manipulation functions.
*
* Author: Ben Heberlein & Jeff Venicx
*
**********************************************************/

#ifndef DATA_H
#define DATA_H

#include "stdint.h"

/****************************************************************************
*my_itoa     : int8_t *my_itoa(int8_t *str, int32_t data, int32_t base);
*   returns  : array pointer of trasnformed data
*   str      : array pointer for transformed data
*   data     : number to be transformed
*   base     : base number value
*Created by  : Jeff Venicx
*Date        : 9-16-16
*Description : takes a interger and converts it into ASCII string
*Notes       : Only works with base 10 or lower
****************************************************************************/
int8_t *my_itoa(int8_t *str, int32_t data, int32_t base);

/****************************************************************************
*my_atoi     : int32_t my_atoi(int8_t *str);
*   returns  : number value
*   str      : string pointer of ASCII
*Created by  : Jeff Venicx
*Date        : 9-16-16
*Description : takes in ASCII string and converts it too interger
****************************************************************************/
int32_t my_atoi(int8_t *str);

/****************************************************************************
*dump_memory : void dump_memory(uint8_t *start, uint32_t length);
*   returns  : void
*   start    : starting address
*   length   : length of data
*Created by  : Jeff Venicx
*Date        : 9-16-16
*Description : printf memory of length starting at address start
****************************************************************************/
void dump_memory(uint8_t *start, uint32_t length);

/****************************************************************************
*big_to_little: uint32_t big_to_little(uint32_t data);
*   returns   : transformed data
*   data      : date to be transformed
*Created by   : Jeff Venicx
*Date         : 9-16-16
*Description  : convert from big to little endian
****************************************************************************/
uint32_t big_to_little(uint32_t data);

/****************************************************************************
*little_to_big: uint32_t big_to_little(uint32_t data);
*   returns   : transformed data
*   data      : date to be transformed
*Created by   : Jeff Venicx
*Date         : 9-16-16
*Description  : convert from little to big endian
****************************************************************************/
uint32_t little_to_big(uint32_t data);

#endif
