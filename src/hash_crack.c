//------Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <openssl/evp.h>

#include "../include/hash_crack.h"
#include "../include/word_gen.h"
#include "../include/utils.h"

//------Signatures
char* get_first_word(unsigned min, unsigned i, char* alf);

//------Implementations

/**
 * Calculates the hash digest of `txt` using the hash function #`h_func`.
 *
 * Values for `h_func`:
 *     1 : md5
 *     2 : sha1
 *     3 : sha256
 *     4 : sha512
 *
 * @param txt - the message to hash
 * @param len - the length of `txt`
 * @param h_func - the number of the hash function to use
 * @param digest - (out) the string to store the output digest
 */
void hash(char* txt, unsigned long len, int h_func, char* digest) {
    const EVP_MD* md;

    switch (h_func) {
        case 1:
            md = EVP_md5();
            break;

        case 2:
            md = EVP_sha1();
            break;

        case 3:
            md = EVP_sha256();
            break;

        case 4:
            md = EVP_sha512();
            break;

        default:
            return;
    }

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, txt, len);
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);

    for (unsigned int i = 0; i < md_len; ++i)
        sprintf(&digest[i * 2], "%02x", (unsigned int) md_value[i]);

    EVP_MD_CTX_free(mdctx);
}

/**
 * Tests if the hash of `word` is `expected`.
 *
 * @param word - the clear word to test ;
 * @param len - the length of `word` ;
 * @param expected - the expected hash digest ;
 * @param h_func - the number of the hash function to use. Cf the doc of `hash` for possible values.
 */
bool test_word(char* word, unsigned long len, char* expected, int h_func) {
    char digest[DIGEST_SIZE];
    hash(word, len, h_func, digest);

    return strcmp(expected, digest) == 0;
}

/**
 * Gets the first word for cracking.
 *
 * Do not forget to free the result.
 *
 * @param min - the length of the word to produce
 * @param i - the index of the current thread
 * @param alf - the alphabet to use.
 *
 * @returns the wanted word (do not forget to free after use)
 */
char* get_first_word(unsigned min, unsigned i, char* alf) {
    unsigned long s = min + 1;
    char* w = malloc(s * sizeof(char));

    for (unsigned k = 0 ; k < min ; ++k)
        w[k] = alf[0];

    w[min] = '\0';

    increment_word(&w, &s, i, alf);

    return w;
}

/**
 * Code run by a thread to crack the hash.
 *
 * @param i               - the id of the current thread (in [|0 ; n - 1|]) ;
 * @param n               - the total number of thread launched ;
 * @param alf             - the alphabet ;
 * @param expected_digest - the hash digest to crack ;
 * @param h_func          - the number of the hash function to use. Cf the doc of `hash` for the possible values ;
 * @param min             - the minimum length of the words to try ;
 * @param limit           - the maximum lenght of the words to try. If 0, there is no limit ;
 * @param silent          - if true, only prints the password. Otherwise, regularly shows progress ;
 * @param found_ptr       - a pointer to a flag indicating if the word has been found. Used to stop all the threads.
 */
void crack_thread_i(unsigned i, unsigned n, char* alf, char* expected_digest, int h_func, unsigned min, unsigned limit, bool silent, bool* found_ptr) {
    //---Get first word
    if (min == 0)
        min++;

    char* word = get_first_word(min, i, alf);

    unsigned long word_len = strlen(word);
    unsigned long word_size = strlen(word); // Will contain the size of the char* containing the word (can be greater than the string)

    //---Main loop
    int counter = 0;
    while (limit == 0 || word_len < limit) {
        //---Verbose
        if (i == 0 && (! silent) && counter % LARGE_NB == 0)
            printf("[Thread %d] Testing word '%s' (length: %ld)\n", i, word, word_len);

        //---Test word
        if (test_word(word, word_len, expected_digest, h_func)) {
            if (silent)
                printf("%s", word);

            else {
                printf("\nThread %d/%d: Found !\n", i + 1, n);
                boxed_print(word);
            }

            // Stop all the other threads
            *found_ptr = true;

            free(word);
            return;
        }

        //---Check if found (by an other thread). To be more efficient, the check is not done very often.
        if (counter % (LARGE_NB / 10) == 0 && *found_ptr)
            break;

        //---Get next word
        increment_word(&word, &word_size, n, alf);
        word_len = strlen(word);
        counter++;
    }

    free(word);
}

