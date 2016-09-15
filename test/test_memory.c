/**********************************************************
* Name: test_memory.c
*
* Date: 9/14/16
*
* Description:
* This file contains unit tests for several memory
* management functions.
*
* Author: Ben Heberlein
*
**********************************************************/

#include "stdint.h"
#include "memory.h"
#include "minunit.h"

static char *test_my_memmove() {
    //mu_assert("error_string", condition);
    //...
    //...
    return 0;
}

static char *test_my_memzero() {
    return 0;
}

static char *test_my_reverse() {
    return 0;
}

static char *all_tests_data() {
    mu_run_test(test_my_memmove);
    mu_run_test(test_my_memzero);
    mu_run_test(test_my_reverse);
    return 0;
}

