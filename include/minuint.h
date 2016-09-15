/**********************************************************
* Name: minunit.h
* 
* Date: 9/14/16
*
* Description: This module contains the macros that define
* the MinUnit testing framework. See
* http://www.jera.com/techinfo/jtns/jtn002.html   
*
* Author: Ben Heberlein
*
**********************************************************/

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
extern int tests_run
