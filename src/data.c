/**********************************************************
* Name: data.c
*
* Date: 9/14/16
*
* Description: This module contains several data
* manipulation functions.
*
* Author: Ben Heberlein
*
***********************************************************/

#include "stdint.h"
#include <stdio.h>

int8_t *my_itoa(int8_t *src, int32_t data, int32_t length) {

}

int32_t my_atoi(int8_t *str) {
    int32_t result = 0;
    int8_t sign = 1;

    int8_t *pos = str;

    printf("%d\n", *pos);


    if(*pos == '-'){
      sign = -1;
      pos++;
    }

    while(*pos != '\0'){
      printf("position value: %d\n", *pos);
      result = result * 10;
      result = result + *pos -'0';
      printf("inline results: %d\n", result);
      pos++;
    }
    return result*sign;
}

void dump_memory(uint8_t *start, uint32_t length) {

    if(!start) printf("invalid start addresse\n");

    if(length < 1) printf("invalid length < 1\n");

    uint8_t *ptr = start;

    //printf("%x ", *ptr);

    for(uint32_t i = 0; i < length; i++){
        printf("%x ", *ptr);
        ptr++;
    }
    printf("\n");
}

uint32_t big_to_little(uint32_t data) {
  uint32_t return_val;

  return_val = ((data>>24)&0xff)|
               ((data<<8)&0xff0000)|
               ((data>>8)&0xff00)|
              ((data<<24)&0xff000000);

  return return_val;
}

uint32_t little_to_big(uint32_t data) {
  
    return big_to_little( data);
}
