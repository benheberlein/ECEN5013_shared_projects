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
#include "timer.h"
#endif
#include "log.h"

int main(int argc, const char* argv[]) {

    #ifdef PROJECT_1
    project_1_report();
    #endif

    #ifdef PROJECT_2

    #ifdef FRDM
    init_uart();
    init_timer();
	#endif

    while(1) {
    	__NOP;
    }

    #endif

    return 0;
}

void TPM0_IRQHandler(){
	GPIOB_PTOR |= (1<<18);
	return;
}
