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

#ifdef FRDM
#include "MKL25Z4.h"
#include "uart.h"
#include "timer.h"
#endif

#include <stdlib.h>
#include "log.h"
#include "test_circbuf.h"
#include "profiler.h"
#include "circbuf.h"
#include "data.h"

#define ECHO_BUF_CAP 128

int8_t logging_demo() {
	Log0("a",1);
}

int main(int argc, const char* argv[]) {

    #ifdef PROJECT_1
    project_1_report();
    #endif

    #ifdef PROJECT_2
    #ifdef FRDM
    init_uart();
    init_timer();
	#endif

	#ifdef UNIT_TESTS
    test_circbuf_all();
	#endif

	#ifdef BENCHMARK
    profile_all();
	#endif

    uint8_t echo = 0;
    uint8_t echo_size = 0;
    uint8_t ch = 0;
    circbuf_t *echo_buffer = NULL;
    echo_buffer = circbuf_initialize(ECHO_BUF_CAP);
    while(1) {

    	if (rx_valid()) {
    		ch = rx_char();
			if (ch == '\\') {
				// Toggle echo mode
				echo = !echo;
				if (echo) {
					tx_string("Entered echo mode.", 18);
					tx_char('\r');
				} else {
					tx_string("Exited echo mode.", 17);
					tx_char('\r');
				}
				continue;
			}

			if (echo) {
				if (ch == '\r') {
					// output all data after newline
					while(circbuf_buffer_empty(echo_buffer) != 1) {
						tx_char(circbuf_remove_item(echo_buffer));
					}
					tx_char('\r');
				} else {
					if (circbuf_buffer_full(echo_buffer) != 1) {
						circbuf_add_item(ch, echo_buffer);
					}
				}
				continue;
			}

			// Normal parse mode
			switch (ch) {
			case ('z'):
				change_duty(-5);
				break;
			case ('Z'):
				change_duty(-5);
				break;
			case ('x'):
				change_duty(5);
				break;
			case ('X'):
				change_duty(5);
				break;
			case ('r'):
				toggle_led(RED);
				break;
			case ('b'):
				toggle_led(BLUE);
				break;
			case ('g'):
				toggle_led(GREEN);
				break;
			case ('R'):
				toggle_led(RED);
				break;
			case ('B'):
				toggle_led(BLUE);
				break;
			case ('G'):
				toggle_led(GREEN);
				break;

			default:
				__NOP;

			}
		}

    	tx_buf();
    }
	#endif

    return 0;
}
