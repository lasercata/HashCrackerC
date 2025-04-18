//------Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/word_gen.h"


//------Structs
typedef struct {
    unsigned long* arr;
    unsigned long size;
}
arr;


//------Signatures
arr convert_to_base(unsigned long n, unsigned long b);
void print_arr(arr a);
unsigned long get_index(char* alf, char c);

//------Implementations
void print_arr(arr a) {
    printf("[");

    for (unsigned long k = 0 ; k < a.size ; ++k)
        printf("%ld, ", a.arr[k]);

    printf("\b\b  \b\b]");
}

/**
 * Calculates the index of the first occurence of the character `c` in `alf`.
 *
 * @param alf - the string in which search for `c` ;
 * @param c - the character to which search the index in `alf`
 *
 * @returns the index of the first occurence of `c` in `alf`. If not found, return `(unsigned long) -1`.
 */
unsigned long get_index(char* alf, char c) {
    unsigned long i = 0;

    while (alf[i] != '\0' && alf[i] != c)
        i++;

    if (alf[i] == '\0')
        return (unsigned long) -1;

    return i;
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
 *
 * @returs the word corresponding to the number `n`.
 */
char* get_word(unsigned long n, char* alf) {
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

/**
 * 'Increments' a word by `i`.
 *
 * E.g :
 *     'a' + 1 = 'b' ;
 *     'a' + 2 = 'c' ;
 *     'z' + 1 = 'aa' ;
 *     'az' + 1 = 'ba' ;
 *     ...
 *
 * If the word needs to be elongated (more than `*size_ptr`), then the size will be doubled.
 * 
 * @param word_ptr - a pointer to the word to increment. It will be modified to contain the new word
 * @param size_ptr - a pointer to the size of the char array containing the word.
 * @param i - the value of the increment to make
 * @param alf - the alphabet to use
 */
void increment_word(char** word_ptr, unsigned long* size_ptr, unsigned long i, char* alf) {
    if (i == 0)
        return;

    //------De-reference the variables
    char* word = *word_ptr;
    unsigned long size = *size_ptr;

    //------Init
    unsigned long k = 0;
    unsigned long overflow = 0;
    const unsigned long len = strlen(word);
    const unsigned long alf_len = strlen(alf);

    //------Main loop
    while (true) {
        unsigned long idx = len - k - 1;

        if (k < len) {
            i += overflow;

            //---Calculate the new character for the current index
            unsigned long new_i = get_index(alf, word[idx]) + i;
            char new_c = alf[new_i % alf_len];

            word[idx] = new_c;

            //---Calculate the overflow and update `i`
            overflow = new_i / alf_len;
            i -= i % alf_len;

            //---Exit if finished
            if (overflow == 0)
                break;
        }
        else {
            unsigned long new_i = i + overflow - 1;

            //---Adding the new char in front of the word (i.e word = new_c + word, where + is the concatenation here)
            //-Check the size
            if (len + 1 >= size) { // There is not enough room in `word` to store an other char (including the trailing '\0'), so we double the size
                size *= 2;
                word = realloc(word, sizeof(char) * (size));
            }

            //-Sliding the word
            word[len + 1] = '\0';

            for (unsigned long j = 0 ; j < len ; ++j) {
                unsigned long idx = len - j - 1;
                word[idx + 1] = word[idx];
            }

            word[0] = alf[new_i % alf_len];
            

            //---Calculate the overflow and update `i`
            overflow = new_i / alf_len;
            i = overflow;

            //---Exit if finished
            if (overflow <= alf_len)
                break;
        }

        k++;
    }

    //---Save the variables
    *word_ptr = word;
    *size_ptr = size;
}
