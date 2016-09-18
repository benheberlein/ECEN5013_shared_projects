/**********************************************************
* Name: project1.c
*
* Date: 9/14/16
*
* Description: This module contains the main routine for
* ECEN 5013 project 1
*
* Author: Ben Heberlein
*
**********************************************************/
#include "project1.h"
#include "memory.h"
#include "data.h"
#include <stdio.h>

void project_1_report() {

    int32_t base = 10;
    int32_t data = -321;
    int8_t * dest = NULL;
    dest = my_itoa(dest, data, base);
    printf("dest addresse: %d\n", dest);

    int i = 0;
    printf("asci string: ");
    while(dest[i] != '\0'){
        printf("%c", dest[i]);
        i++;
    }
    printf("\n");

    /*
    uint8_t test_dump[] = {'n','b','c','\0'};
    dump_memory(test_dump, 3);
*/

    /*
    int32_t transform = 0;
    int8_t test[] = {'-','1','2','\0'};
    printf("intial value %d\n", *test);
    transform = my_atoi(test);

    printf("%d\n", transform);
    */

}
