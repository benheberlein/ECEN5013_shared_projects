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

#ifdef PROJECT_2
int8_t logging_demo() {
	uint8_t buf[128];
	uint8_t int_buf[10];

	uint8_t *str;
	uint8_t length = 0;

	str = (uint8_t *) "Testing123, Serial Print Test, no params";
	length = 40;
	Log0(str, length);

	str = (uint8_t *) "This is an integer number: ";
	my_itoa(int_buf, 200, 10);
	concat_strings(buf, str, int_buf, 27, 3);
	length = 30;
	Log0(buf, length);

	my_itoa(int_buf, 4096, 10);
	concat_strings(buf, str, int_buf, 27, 4);
	length = 31;
	Log0(buf, length);

	my_itoa(int_buf, 123456, 10);
	concat_strings(buf, str, int_buf, 27, 6);
	length = 33;
	Log0(buf, length);

	str = (uint8_t *) "This is a floating point number: ";
	my_ftoa(1543.321, int_buf);
	concat_strings(buf, str, int_buf, 33, 8);
	length = 41;
	Log0(buf, length);

}
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

	#ifdef UNIT_TESTS
    test_circbuf_all();
	#endif

	#ifdef BENCHMARK
    profile_all();
	#endif

	#ifdef LOG_DEMO
    logging_demo();
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
