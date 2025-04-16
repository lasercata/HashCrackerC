//------Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/word_gen.h"
#include "../include/hash_crack.h"

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

    // Test increment_word
    char* w = get_word(1, az);
    unsigned long s = strlen(w);

    for (int k = 0 ; k < 1000 ; ++k) {
        printf("%d: %s\n", k, w);
        increment_word(&w, &s, 1, az);
    }

    free(w);
    w = NULL;

    // Test hash
    char* w_h = get_word(1000, az);
    unsigned long len = strlen(w_h);

    char digest[DIGEST_SIZE];
    hash(w_h, len, 1, digest);

    printf("digest of '%s': %s\n", w_h, digest);
    free(w_h);

    bool b1, b2;
    b1 = test_word("Aja", strlen("Aja"), digest, 1);
    b2 = test_word("aja", strlen("aja"), digest, 1);

    printf("b1 : %d, b2: %d\n", b1, b2);

    return 0;
}
