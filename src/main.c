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
#undef FRDM
#undef PROJECT_1
#define PROJECT_2


#include "project1.h"
#include "log.h"

#ifdef FRDM
#include "MKL25Z4.h"
#include "uart.h"
#include "timer.h"
//prints test results to log0/log1
//undef uses printf
#define LOG
#endif



int main(int argc, const char* argv[]) {

    #ifdef PROJECT_1
    project_1_report();
    #endif

    #ifdef PROJECT_2
        #ifdef FRDM
        init_uart();
        init_timer();
	       #endif

        #ifdef FRDM
        while(1) {
        	__NOP;
        }
        #endif
    #endif

    return 0;
}

/*
void TPM0_IRQHandler(){
	GPIOB_PTOR |= (1<<18);
	return;
}*/
