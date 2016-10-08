#include "memory.h"
#include <time.h>
#include "log.h"
#include "data.h"
#include "circbuf.h"

void profile_memory() {
	// Benchmark library memmove
	// Benchmark my_memmove
	// Benchmark library memset
	// Benchmark my_memzero
	// Benchmark reverse
	// Benchmark my_reverse
	
	// Output all profile data with log.h functions
}

void profile_data () {
	// itoa
	// my_itoa
	//ftoa
	// my_ftoa
	// atoi
	// my_atoi
}

void profile_malloc() {
	// profile malloc with different data sizes
	// profile free
}

void profile_circbuf() {
	// circbuf add item
	// circbuf remove item
}

void profile_log() {
	#ifdef FRDM
	// profile log
	#endif
}

void profile_all() {
	profile_memory();
	profile_data();
	profile_malloc();
	profile_circbuf();
	profile_log();
}

