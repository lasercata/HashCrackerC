//------Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <openssl/evp.h>

#include "../include/hash_crack.h"
// #include "../include/word_gen.h"
#include "../include/constants.h"

//------Signatures

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
