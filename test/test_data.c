/**************************************
* This file contains unit tests for   *
* several data manipulation           *
* functions.                          *
**************************************/

#include "stdint.h"
#include "data.h"
#include "munit.h"

static char *test_my_itoa() {
    //mu_assert("error_string", condition);
    //...
    //...
    return 0;
}

static char *test_my_atoi() {
    return 0;
}

static char *test_dump_memory() {
    return 0;
}

static char *test_big_to_little() {
    return 0;
}

static char *test_little_to_big() {
    return 0;
}

static char *all_tests_data() {
    mu_run_test(test_my_itoa);
    mu_run_test(test_my_atoi);
    mu_run_test(test_dump_memory);
    mu_run_test(test_big_to_little);
    mu_run_test(test_little_to_big);
    return 0;
}

