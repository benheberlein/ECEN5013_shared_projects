/**********************************************************
* Name: memory.c
*
* Date: 9/14/16
*
* Description: This module contains several memory
* manipulation functions.
*
* Author: Ben Heberlein <3 Jeff Venicx
*
***********************************************************/

#include <stdint.h>
#include "memory.h"

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length) {
    //invalid strings
    if(!src|!dst) return -1;
    //if memmove to same location
    if(src == dst) return 0;

    //if src < dest start at end to prevent possible overlap/overwrite
    if(src < dst){
      //start from end
      src = src + length-1;
      dst = dst + length-1;
      for (uint32_t i = 0; i < length; i++){
          *dst = *src;
          dst--;
          src--;
      }
    }

    //if dest < src start at begining to prevent overlap
    else if(src > dst) {
      for(uint32_t i = 0; i < length; i++){
        *dst = *src;
        dst++;
        src++;
      }
    }
    //unknown error
    else return -1;
    //proper execution
    return 0;
}

int8_t my_memzero(uint8_t *src, uint32_t length) {
    //invalid string
    if(!src) return -1;

    //place zeros
    for(uint32_t i = 0; i < length; i++){
      *src = 0;
      src++;
    }

    return 0;
}

int8_t my_reverse(uint8_t *src, uint32_t length) {
    //invalid string
    if(!src) return -1;
     //invalid length
     if(length < 1) return -1;

     //end of string pointer
     uint8_t *end = src + length -1;
     //swap space variable
     uint8_t swap;
    //perform swap function
     while(src < end){
       swap = *src;
       *src = *end;
       *end = swap;
       src++;
       end--;
     }

    return 0;
}
