/**********************************************************
* Name: main.c
*
* Date: 9/14/16
*
* Description: This module contains the main routine
*
* Author: Ben Heberlein
*
***********************************************************/
#include "project1.h"
#ifdef FRDM
#include "MKL25Z4.h"
#include "uart.h"
#endif

int main(int argc, const char* argv[]) {

    #ifdef PROJECT_1
    project_1_report();
    #endif

    #ifdef PROJECT_2

    init_uart();
    while(1) {
    	//tx_char((uint8_t) 'z');
    }

    #endif


    return 0;
}
