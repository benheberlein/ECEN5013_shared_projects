/**********************************************************
* Name: test_main.c
*
* Date: 9/14/16
*
* Description:
* This file holds the main routine for
* the test executable.
*
* Author: Ben Heberlein
*
***********************************************************/

static char *all_tests() {
    all_tests_data();
    all_tests_memory();
    //...
    return 0;
}

int main() {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
}
