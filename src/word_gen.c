//------Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/word_gen.h"


/*
 * TODO: a function `get_next_word(char* current_word, int offset)` that calculates and returns the "next" word (more precisely the k-th next one, with k = `offset`).
 *
 * E.g
 * get_next_word("aaa", 1) == "aab"
 * get_next_word("aaa", 2) == "aac"
 * get_next_word("aaz", 1) == "aba"
 * get_next_word("zzz", 1) == "aaaa"
 *
 * I think that this would be more efficient than malloc an int array, convert an int to base len(alf), convert the array to string (malloc a char*), free the array (that is `get_word`), free the string.
 *
 * And even malloc the `word` at the beginning (one for each thread) with a long enough size, and edit the string given in param.
 *
 *
 * The function `get_word` will be used to get the first word for each thread (thread i will `get_word(i)`, and then `get_next_word(&word, n)`, where `n` is the number of threads).
 */


//------Structs
typedef struct {
    unsigned long* arr;
    unsigned long size;
}
arr;


//------Signatures
arr convert_to_base(unsigned long n, unsigned long b);
void print_arr(arr a);

//------Implementations
void print_arr(arr a) {
    printf("[");

    for (unsigned long k = 0 ; k < a.size ; ++k)
        printf("%ld, ", a.arr[k]);

    printf("\b\b  \b\b]");
}

/**
 * Converts `n` from base 10 to base `b` :
 *
 * n = sum_{k = 0}^{p - 1} a_k b^k
 *
 * @returns the array [a_p, a_{p - 1}, ..., a_0].
 */
arr convert_to_base(unsigned long n, unsigned long b) {
    if (n == 0 || n == 1) {
        arr ret;
        ret.arr = malloc(sizeof(unsigned long));
        ret.arr[0] = n;
        ret.size = 1;

        return ret;
    }

    // List size : calculate p (here s)
    unsigned long s = 0;
    unsigned long B = 1;

    while (n >= B) {
        B *= b;
        s++;
    }

    // Create the return array
    arr ret;
    ret.arr = malloc(s * sizeof(unsigned long));
    ret.size = s;

    // Fill the array
    unsigned long i = s - 1;
    while (n > 0) {
        ret.arr[i] = n % b;
        n /= b;
        i--;
    }

    return ret;
}

/**
 * Return the word number `n` from alphabet `alf`.
 *
 * It converts `n` to base N, where N is the length of `alf`.
 *
 * @param n - the index of the word to generate ;
 * @param alf - the alphabet to use.
 */
char* get_word(unsigned long n, char* alf) { //TODO: free result
    arr digits = convert_to_base(n, strlen(alf) + 1);

    // print_arr(digits);

    char* word = (char*) malloc((digits.size + 1) * sizeof(char));

    for (unsigned long k = 0 ; k < digits.size ; ++k) {
        word[k] = alf[(digits.arr[k] - 1) % strlen(alf)];
    }

    word[digits.size] = '\0';

    free(digits.arr);

    return word;
}
