#ifndef __HASH_CRACK_H
#define __HASH_CRACK_H

//------Includes
#include <stdbool.h>

//------Signatures
void hash(char* txt, unsigned long len, int h_func, char* digest_ptr);
bool test_word(char* word, unsigned long len, char* expected, int h_func);
void crack_thread_i(unsigned i, unsigned n, char* alf, char* expected_digest, int h_func, unsigned min, unsigned limit, bool silent, bool* found_ptr);

#endif

