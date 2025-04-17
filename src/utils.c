//------Includes
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

//------Constants
const char alf_arr[ALF_NB][ALF_MAX_SIZE] = {
    "0123456789",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyz0123456789",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
};

const char alf_keys[ALF_NB][ALF_MAX_SIZE] = {
    "09",
    "az",
    "AZ",
    "az09",
    "azAZ",
    "azAZ09"
};

//------Functions

/**
 * Calculates `base`^`exp`, only with integers.
 */
unsigned long uint_pow(unsigned long base, unsigned long exp) {
    unsigned long result = 1;

    while (exp) {
        if (exp % 2)
            result *= base;

        exp /= 2;
        base *= base;
    }

    return result;
}

/**
 * Prints `txt` in a box, e.g:
 *
 *     +------+
 *     | test |
 *     +------+
 *
 * @param txt - the text to print in a box.
 */
void boxed_print(char* txt) {
    unsigned long len = strlen(txt);

    printf("+");

    for (unsigned long k = 0 ; k < len + 2 ; ++k)
        printf("-");

    printf("+");

    printf("\n| %s |\n", txt);

    printf("+");

    for (unsigned long k = 0 ; k < len + 2 ; ++k)
        printf("-");

    printf("+\n");
}

