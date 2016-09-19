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
#include "data.h"
#include "memory.h"
#include <string.h>
#include <stdio.h>

int8_t *my_itoa(int8_t *str, int32_t data, int32_t base) {
    //array for storing ascii string
    static int8_t string[256];
    int i = 0;
    int8_t sign = 1;

    if (data < 0){
      printf("-");
      sign = -1;
      data = data *-1;
    }

    //entered in reverse order must use reverse
    while(data != 0){
        string[i] = data%base + '0';
        if (string[i] >= 10 + '0') {
            string[i] = string[i] + 7;
        }
        i++;
        data = data/base;
    }
    //add the negative sign
    if(sign < 1){
      string[i] = '-';
      i++;
    }
    //add null terminator
    string[i] = '\0';
    //reverse the string
    my_reverse(string, i);
    str = string;
    return string;
}

int32_t my_atoi(int8_t *str) {
    int32_t result = 0;
    int8_t sign = 1;

    int8_t *pos = str;

    if(*pos == '-'){
      sign = -1;
      pos++;
    }

    while(*pos != '\0'){
      if( (*pos < '0') | (*pos > '9')) return 0;
      result = result * 10;
      result = result + *pos -'0';
      pos++;
      if(result > 127 | result < -128) return 0;
    }
    return result*sign;
}

void dump_memory(uint8_t *start, uint32_t length) {

    if(!start) printf("invalid start addresse\n");

    if(length < 1) printf("invalid length < 1\n");

    uint8_t *ptr = start;

    for(uint32_t i = 0; i < length; i++){

        if(!(i%11) & i != 0) printf("\n");
        printf("%02X ", *ptr);
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
