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

    if(!src) return -1;

    //if memmove to same location
    if(src == dst) return 0;

    uint8_t *source = src;
    uint8_t *dest = dst;

    //if src < dest start at end to prevent possible overlap/overwrite
    if(src < dst){
      //start from end
      source = source + length-1;
      dest = dest + length-1;
      for (uint32_t i = 0; i < length; i++){
          *dest = *source;
          dest--;
          source--;
      }
    }

    //if dest < src start at begining to prevent overlap
    else if(src > dst) {

      for(uint32_t i = 0; i < length; i++){
        *source = *dest;
        dest++;
        source++;
      }
    }

    //wtf? either src and dst are the same or shit went bad
    else return -1;

    return 0;
}

int8_t my_memzero(uint8_t *src, uint32_t length) {

    if(!src) return -1;

    uint8_t *source = src;

    for(uint32_t i = 0; i < length; i++){
      *source = 0;
      source++;
    }

    return 0;
}

int8_t my_reverse(uint8_t *src, uint32_t length) {
    //invalid string
     if(!src) return -1;

     //invalid length
     if(length < 1) return -1;

     uint8_t *start = src;
     uint8_t *end = src + length -1;

     uint8_t swap;

     while(start < end){
       swap = *start;
       *start = *end;
       *end = swap;
       start++;
       end--;
     }

    return 0;
}
