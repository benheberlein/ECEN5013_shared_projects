/**********************************************************
* Name: test_circbuf.c
*
* Date: 10/6/2016
*
* Author: Ben Heberlein
*
* Description: This file tests circular buffer functions.
*
**********************************************************/

#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"
#include "test_circbuf.h"
#include "data.h"
#include "log.h"

void test_circbuf_buffer_full() {
	uint8_t fail = 0;
	int8_t result = 0;
	
	// Check null circular buffer error
	if (circbuf_buffer_full(NULL) != -1) {
		fail = 1;
	}
	circbuf_t *cb = circbuf_initialize(3);
	
	// Check not full
	if (circbuf_buffer_full(cb) != 0) {
		fail = 2;
	}
	for (int i = 0; i < 3; i++) {
		result = circbuf_add_item(i, cb);
	}
	
	// Check full
	if (circbuf_buffer_full(cb) != 1) {
		fail = 3;
	}
	
	// Log output
	if (fail == 0) {
		Log0("TEST PASSED: test_circbuf_full", 30);
	} else {
		Log1("TEST FAILED: test_circbuf_full", 30, &fail, 1);
		//static uint8_t *temp1 = "TEST FAILED: test_circbuf_full with failure code _";
		//uint8_t *temp2 = NULL;
		//temp2 = my_itoa(temp2, fail, 10);
		//*(temp1) = *temp2;
		//Log0(temp1, 1);
		//Log0("TEST FAILED: test_circbuf_full with failure code ", 50);
	}
	
}

void test_circbuf_buffer_empty() {
	uint8_t fail = 0;
	uint8_t result = 0;
	
	// Check null circular buffer error
	if (circbuf_buffer_empty(NULL) != -1) {
		fail = 1;
	}
	circbuf_t *cb = circbuf_initialize(3);
	
	// Check not full
	if (circbuf_buffer_empty(cb) != 1) {
		fail = 2;
	}
	result = circbuf_add_item(53, cb);
	
	// Check full
	if (circbuf_buffer_empty(cb) != 0) {
		fail = 3;
	}
	
	// Log output
	if (fail == 0) {
		Log0("TEST PASSED: test_circbuf_empty", 31);
	} else {
		Log1("TEST FAILED: test_circbuf_empty", 31, &fail, 1);
		//static uint8_t *temp1 = "TEST FAILED: test_circbuf_full with failure code _";
		//uint8_t *temp2 = NULL;
		//temp2 = my_itoa(temp2, fail, 10);
		//*(temp1) = *temp2;
		//Log0(temp1, 1);
		//Log0("TEST FAILED: test_circbuf_full with failure code ", 50);
	}

}

void test_circbuf_add_item() {
	uint8_t fail = 0;
	int8_t result = 0;
	uint8_t *h = NULL;
	uint8_t *t = NULL;
	uint8_t *buf = NULL;
	
	// Check null circular buffer error
	if (circbuf_add_item(53, NULL) != -1) {
		fail = 1;
	}
	circbuf_t *cb = circbuf_initialize(3);

	h = cb->head;
	t = cb->tail;
	buf = cb->buf;
	if (circbuf_add_item(53, cb) != 0) {
		fail = 2;
	}

	if (cb->head == h) {
		fail = 3;
	}
	
	if (cb->tail != t) {
		fail = 4;
	}
	
	if (cb->buf != buf) {
		fail = 5;
	}

	if (*(cb->buf) != 53) {
		fail = 6;
	}
	
	if (cb->STATUS != PARTIAL) {
		fail = 7;
	}
	
	if (cb->size != 1) {
		fail = 8;
	}

	circbuf_add_item(52, cb);
	circbuf_add_item(51, cb);
	
	if (cb->STATUS != FULL) {
		fail = 9;
	}

	if (circbuf_add_item(100, cb) !=  -1) {
		fail = 10;
	}
	
	if (circbuf_remove_item(cb) != 53) {
		fail = 11;
	}
	
	if (cb->head != cb->buf) {
		fail = 12;
	}

	// Log output
	if (fail == 0) {
		Log0("TEST PASSED: test_circbuf_add_item", 34);
	} else {
		Log1("TEST FAILED: test_circbuf_add_item", 34, &fail, 1);
	}
}

void test_circbuf_remove_item() {
	uint8_t fail = 0;
	int8_t result = 0;
	uint8_t *h = NULL;
	uint8_t *t = NULL;
	uint8_t *buf = NULL;
	
	// Check null circular buffer error
	if (circbuf_remove_item(NULL) != 0) {
		fail = 1;
	}
	circbuf_t *cb = circbuf_initialize(3);

	if (circbuf_remove_item(cb) != 0) {
		fail = 2;
	}
	
	circbuf_add_item(53, cb);
	circbuf_add_item(52, cb);
	circbuf_add_item(51, cb);

	h = cb->head;
	t = cb->tail;
	buf = cb->buf;	
	if (circbuf_remove_item(cb) != 53) {
		fail = 3;
	}
	
	if (cb->head != h) {
		fail = 4;
	}
	
	if (cb->tail == t) {
		fail = 5;
	}
	
	if (cb->buf != buf) {
		fail = 6;
	}
	
	if (cb->STATUS != PARTIAL) {
		fail = 7;
	}
	
	if (cb->size != 2) {
		fail = 8;
	}
#if 0
	// Check tail rollover
	circbuf_remove_item(cb);
	circbuf_add_item(100, cb);
	circbuf_remove_item(cb);
	if (cb->buf != cb->tail) {
		fail = 9;
	}
	
	if (circbuf_remove_item(cb) != 53) {
		fail = 11;
	}
	
	// Log output
	if (fail == 0) {
		Log0("TEST PASSED: test_circbuf_remove_item", 37);
	} else {
		Log1("TEST FAILED: test_circbuf_remove_item", 37, &fail, 1);
	}

#endif
}

void test_circbuf_initialize() {

}

void test_circbuf_destroy() {

}

void test_circbuf_all() {
	test_circbuf_buffer_full();
	test_circbuf_buffer_empty();
	test_circbuf_add_item();
	test_circbuf_remove_item();
}

