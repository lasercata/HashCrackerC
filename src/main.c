//------Include
#include <stdio.h>
#include <string.h>

#include "../include/word_gen.h"

//------Constants
char* az = "abcdefghijklmnopqrstuvwxyz";

//------Main
int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    printf("test\n");

    // for (int k = 0 ; k < 1000 ; ++k) {
    //     char* w = get_word((unsigned long) k, az);
    //     printf("%d: %s\n", k, w);
    //     free(w);
    // }

    // int s = 2;
    // char* a = malloc(((unsigned long) s) * sizeof(char));
    // a[0] = 'a';
    // a[1] = '\0';

    // char* a = get_word(1, az);
    // unsigned long s = strlen(a);
    //
    // printf("%s\n", a);
    // increment_word(&a, &s, 20, az);
    // printf("%s\n", a);

    char* w = get_word(1, az);
    unsigned long s = strlen(w);

    for (int k = 0 ; k < 1000 ; ++k) {
        printf("%d: %s\n", k, w);
        increment_word(&w, &s, 1, az);
    }

    return 0;
}
