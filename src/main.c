//------Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/word_gen.h"
#include "../include/hash_crack.h"
#include "../include/utils.h"
#include "../include/parser.h"

//------Constants
// char* az = "abcdefghijklmnopqrstuvwxyz";

//------Functions
void tests() {
    printf("test\n");

    // for (int k = 0 ; k < 1000 ; ++k) {
    //     char* w = get_word((unsigned long) k, az);
    //     printf("%d: %s\n", k, w);
    //     free(w);
    // }

    unsigned long s = 6;
    char* a = malloc(((unsigned long) s) * sizeof(char));
    for (int k = 0 ; k < 5 ; ++k)
        a[k] = 'a';

    a[5] = '\0';

    // char* a = get_word(1, az);
    // unsigned long s = strlen(a);

    printf("%s\n", a);
    increment_word(&a, &s, 1, (char*) alf_arr[1]);
    printf("%s\n", a);

    // Test increment_word
    char* w = get_word(1, (char*) alf_arr[1]);
    unsigned long s_ = strlen(w);

    for (int k = 0 ; k < 10 ; ++k) {
        printf("%d: %s\n", k, w);
        increment_word(&w, &s_, 10, (char*) alf_arr[1]);
    }

    free(w);
    w = NULL;

    // Test hash
    char* w_h = get_word(1000, (char*) alf_arr[1]);
    unsigned long len = strlen(w_h);

    char digest[DIGEST_SIZE];
    hash(w_h, len, 1, digest);

    printf("digest of '%s': %s\n", w_h, digest);
    free(w_h);

    bool b1, b2;
    b1 = test_word("Aja", strlen("Aja"), digest, 1);
    b2 = test_word("aja", strlen("aja"), digest, 1);

    printf("b1 : %d, b2: %d\n", b1, b2);
}

void test_crack_md5(char* h_digest) {
    char* w = get_word(1, (char*) alf_arr[1]);
    unsigned long s = strlen(w);

    unsigned long k = 0;
    while (! test_word(w, s, h_digest, 1)) {
        increment_word(&w, &s, 1, (char*) alf_arr[1]);
        s = strlen(w);

        if (++k % 1000000 == 0)
            printf("Testing word '%s', length %ld\n", w, strlen(w));
    }

    printf("\nFound : '%s'\n", w);

    free(w);
    w = NULL;
}

//------Main
int main(int argc, char* argv[]) {
    // tests();
    // test_crack_md5("1a528bb096164775b3cc347ca7293fe6");


    return parse(argc, argv);
}
