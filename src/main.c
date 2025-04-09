//------Include
#include <stdio.h>
#include <stdlib.h>

#include "../include/word_gen.h"

//------Constants
char* az = "abcdefghijklmnopqrstuvwxyz";

//------Main
int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    printf("test\n");

    for (int k = 0 ; k < 1000 ; ++k) {
        char* w = get_word((unsigned long) k, az);
        printf("%d: %s\n", k, w);
        free(w);
    }

    return 0;
}
