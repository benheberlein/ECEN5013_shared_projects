/**********************************************************
* Name: profiler.c
*
* Date: 10/7/2016
*
* Description: This module contains implementations for the
* profiler
*
* Author: Ben Heberlein & Jeff Venicx
*
***********************************************************/

#include "memory.h"
#include <sys/time.h>
#include "log.h"
#include "data.h"
#include "circbuf.h"
#include "uart.h"
#include "MKL25Z4.h"
#include "stdlib.h"
#include "string.h"
//binary bits for PRESCALE starting at 000 = 1 ... 111=128
#define PRESCALE 111
//decimal translation of PRESCALE
#define PRESCALE_MULTI 128

void profile_memory(uint32_t length) {

	int message_length;
	uint16_t cycles_128;
	//uint32_t length = 16;
	uint8_t src[length];
	uint8_t dst[length];
	int32_t test;
	uint8_t time_buffer[32];


	/*benchmark my_memmove*************************/
#ifdef FRDM
	TPM1_CNT = 0;
	my_memmove(src, dst, length);
	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("my_memove time usec:", 20);
	Log0(time_buffer, message_length);

	/*benchmark memmove*********************/
#ifdef FRDM
	TPM1_CNT = 0;

	memmove(dst, src, length);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("memmove time usec:", 18);
	Log0(time_buffer, message_length);

	/*benchmark my_memzero******************/
#ifdef FRDM
	TPM1_CNT = 0;

	my_memzero(src, length);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("my_memove time usec:", 20);
	Log0(time_buffer, message_length);

	/*benchmark memset for 0 *******************/
#ifdef FRDM
	TPM1_CNT = 0;

	memset(src, 0, length);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("memset time usec:", 17);
	Log0(time_buffer, message_length);

	/*benchmark my_reverse********************/
#ifdef FRDM
	TPM1_CNT = 0;

	my_reverse(src, length);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("my_reverse time usec:", 21);
	Log0(time_buffer, message_length);
	
	// Benchmark reverse but how?
	// Output all profile data with log.h functions
}

void profile_data () {
	int message_length;
	uint16_t cycles_128;
	uint32_t length = 16;
	uint8_t buffer[32];
	int32_t interger = 12345;
	int32_t test;
	uint8_t time_buffer[32];

	float flt = 123123213121.234;


	/*benchmark my_itoa*********************/
#ifdef FRDM
	TPM1_CNT = 0;

	my_itoa(buffer, interger, 10);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("my_itoa time usec:", 18);
	Log0(time_buffer, message_length);

#ifndef FRDM
	/*benchmark itoa**********************/
#endif

	/*benchmark my_ftoa**********************/
#ifdef FRDM
	TPM1_CNT = 0;

	my_ftoa(flt, buffer);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("my_ftoa time usec:", 18);
	Log0(time_buffer, message_length);

#ifndef FRDM
	/*benchmark ftoa**********************/
#endif

	/*benchmark my_atoi*********************/
#ifdef FRDM
	TPM1_CNT = 0;

	interger = my_atoi(buffer);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("my_atoi time usec:", 18);
	Log0(time_buffer, message_length);

#ifndef FRDM
	/*benchmark atoi**********************/
#endif


}

void profile_malloc(uint32_t num_bytes) {

	int32_t test;
	uint8_t time_buffer[32];
	int message_length;
	uint16_t cycles_128;


#ifdef FRDM
	TPM1_CNT = 0;

	malloc(num_bytes);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("malloc time usec:", 17);
	Log0(time_buffer, message_length);

	// profile malloc with different data sizes
	// profile free
}

void profile_circbuf() {

	uint8_t time_buffer[32];
	int message_length;
	uint16_t cycles_128;
	int32_t test;

	circbuf_t *cb;
	cb = circbuf_initialize(10);


	/*benchmark circbuf_add_item*************************/
#ifdef FRDM
	TPM1_CNT = 0;

	circbuf_add_item(32, cb);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("add item time usec:", 19);
	Log0(time_buffer, message_length);

	/*benchmark ircbuf_remove_item *************************/
#ifdef FRDM
	TPM1_CNT = 0;

	circbuf_remove_item(cb);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);
#else
	//add beagle code
#endif
	Log3("remove item time usec:", 22);
	Log0(time_buffer, message_length);


	circbuf_destroy(cb);
}

void profile_log() {
#ifdef FRDM

	int32_t test;
	uint8_t time_buffer[32];
	int message_length;
	uint16_t cycles_128;

	TPM1_CNT = 0;

	Log0("test log time", 13);

	cycles_128 = (uint16_t)TPM1_CNT;
	test = (cycles_128*PRESCALE_MULTI);
	test = test/48;
	message_length = my_itoa(time_buffer, test, 10);

	Log3("Log0 time usec:", 15);
	Log0(time_buffer, message_length);
#endif
}

void profile_init(){
	//set clock gate for TPM1
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;

	//set clock mode and prescale factor
	TPM_SC_REG(TPM1) = TPM_SC_CMOD(1) | TPM_SC_PS(PRESCALE);

	//set mod number for max
	TPM_MOD_REG(TPM1) = 65535;
}

uint8_t* profile_convert_time(uint8_t * dst, uint16_t cycles, int ps){

	//time = (cycles*ps)/48000;

}
void profile_all() {
	profile_init();

	/*
	Log0("10 bytes", 8);
	profile_memory(10);
	Log0("5000 bytes", 10);
	profile_memory(5000);
	*/

	//profile_data();

	/*
	Log0("malloc 10 bytes", 15);
	profile_malloc(10);

	Log0("malloc 100 bytes", 16);
	profile_malloc(10);

	Log0("malloc 500 bytes", 16);
	profile_malloc(10);

	Log0("malloc 1000 bytes", 17);
	profile_malloc(10);
	 */

	//profile_circbuf();

	profile_log();
}

