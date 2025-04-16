#ifndef __HASH_CRACK_H
#define __HASH_CRACK_H

//------Includes
#include <stdbool.h>

//------Signatures
void hash(char* txt, unsigned long len, int h_func, char* digest_ptr);
bool test_word(char* word, unsigned long len, char* expected, int h_func);

#endif

