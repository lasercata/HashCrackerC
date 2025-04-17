#ifndef __UTILS_H
#define __UTILS_H

//------Constants
//---Version
#define version "v1.0.0"

//---Hash
#define DIGEST_SIZE 256
#define LARGE_NB 1000000

//---Alphabets
#define ALF_MAX_SIZE 512
#define ALF_NB 6

extern const char alf_arr[ALF_NB][ALF_MAX_SIZE];
extern const char alf_keys[ALF_NB][ALF_MAX_SIZE];

//------Signatures
unsigned long uint_pow(unsigned long base, unsigned long exp);
void boxed_print(char* txt);

#endif

