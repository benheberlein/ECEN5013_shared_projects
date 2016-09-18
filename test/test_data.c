/**********************************************************
* Name: test_data.c
*
* Date: 9/14/16
*
* Description:
* This file contains unit tests for several data
* manipulation functions
*
* Author: Ben Heberlein
*
***********************************************************/

#include <stdint.h>
#include <stdio.h>
#include "data.h"
#include "minunit.h"

static char *test_my_itoa() {
    printf("Testing my_itoa\n");

    // Error strings
    static char *error1 = "Failed to convert decimal number";
    static char *error2 = "Failed to convert negative number";
    static char *error3 = "Failed to convert binary number";
    static char *error4 = "Failed to convert hex number";
    static char *error5 = "Should return -1 for invalid bases";

    //mu_assert("error_string", condition);
    //...
    //...
    return NULL;
}

static char *test_my_atoi() {
    printf("Testing my_atoa\n");

    // Error strings
    static char *error1 = "Failed to convert positive integer";
    static char *error2 = "Failed to convert negative integer";
    static char *error3 = "Failed to convert zero";
    static char *error4 = "Should return 0 if input string is not a number";
    static char *error5 = "Should return 0 if input number is too big or too small";
    static char *error6 = "Should be able to handle leading zeros";

    mu_assert(error1, my_atoi("100") == 100);
    mu_assert(error2, my_atoi("-100") == -100);
    mu_assert(error3, my_atoi("0") == 0);
    mu_assert(error6, my_atoi("0000") == 0);
    mu_assert(error3, my_atoi("-0") == 0);
    mu_assert(error4, my_atoi("abc") == 0);
    mu_assert(error4, my_atoi("123abc") == 0);
    mu_assert(error5, my_atoi("3000000000") == 0);
    mu_assert(error5, my_atoi("-3000000000") == 0);
    mu_assert(error6, my_atoi("000123") == 123);
    mu_assert(error6, my_atoi("-000123") == -123);

    return NULL;
}

static char *test_dump_memory() {
    printf("Testing dump_memory\n");

    int32_t buffer_length = 100;
    uint8_t buffer[buffer_length];

    // Initialize data
    for (uint32_t i = 0; i < buffer_length; i++) {
        buffer[i] = i;
    }

    printf("The following command should print\n"
           "00 01 02 03 04 05 06 07 08 09 0A\n"
           "0B 0C 0D 0E 0F 10 11 12 13 14 15\n");
    dump_memory(buffer, 20);

    printf("The following command should print\n"
           "16 17 18 19 1A 1B 1C 1D 1E 1F 20\n");
    dump_memory(buffer+20, 10);

    printf("The following command should print 00\n");
    dump_memory(buffer, 1);

    return NULL;
}

static char *test_big_to_little() {
    printf("Testing bit_to_little\n");

    static char *error1 = "Failed to convert a 1 byte number";
    static char *error2 = "Failed to convert a 2 byte number";
    static char *error3 = "Failed to convert a 3 byte number";
    static char *error4 = "Failed to convert a 4 byte number";
    static char *error5 = "Failed to convert an 8 byte number";

    mu_assert(error1, big_to_little(0x000A) == 0xA000);
    mu_assert(error2, big_to_little(0x00AB) == 0xBA00);
    mu_assert(error3, big_to_little(0x0ABC) == 0xCBA0);
    mu_assert(error4, big_to_little(0xABCD) == 0xDCBA);
    mu_assert(error5, big_to_little(0xABCDEF12) == 0x21FEDCBA);

    return NULL;
}

static char *test_little_to_big() {
    printf("Testing little_to_big\n");

    static char *error1 = "Failed to convert a 1 byte number";
    static char *error2 = "Failed to convert a 2 byte number";
    static char *error3 = "Failed to convert a 3 byte number";
    static char *error4 = "Failed to convert a 4 byte number";
    static char *error5 = "Failed to convert an 8 byte number";

    mu_assert(error1, little_to_big(0xA000) == 0x000A);
    mu_assert(error2, little_to_big(0xBA00) == 0x00AB);
    mu_assert(error3, little_to_big(0xCBA0) == 0x0ABC);
    mu_assert(error4, little_to_big(0xDCBA) == 0xABCD);
    mu_assert(error5, little_to_big(0x21FEDCBA) == 0xABCDEF21);

    return NULL;
}

char *all_tests_data() {
    mu_run_test(test_my_itoa);
    mu_run_test(test_my_atoi);
    mu_run_test(test_dump_memory);
    mu_run_test(test_big_to_little);
    mu_run_test(test_little_to_big);
    return NULL;
}
