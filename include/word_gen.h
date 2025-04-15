#ifndef __WORD_GEN_H
#define __WORD_GEN_H

char* get_word(unsigned long n, char* alf);
void increment_word(char** word_ptr, unsigned long* size_ptr, unsigned long i, char* alf);

#endif
