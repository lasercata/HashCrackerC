//------Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include <pthread.h>

#include "../include/hash_crack.h"
#include "../include/utils.h"

//------Structures
typedef struct {
    unsigned i;
    unsigned n;
    char* alf;
    char* expected_digest;
    int h_func;
    unsigned min;
    unsigned limit;
    bool silent;
    bool* found_ptr;
} crack_thread_arguments;

//------Signatures
void* crack_thread_wrapper(void* args);

//------Implementations

/**
 * Wrapper around `crack_thread_i` to use it with pthread.
 *
 * @param args - the arguments for `crack_thread_i` as a `crack_thread_arguments` struct.
 */
void* crack_thread_wrapper(void* args) {
    crack_thread_arguments a = *(crack_thread_arguments*) args;

    crack_thread_i(a.i, a.n, a.alf, a.expected_digest, a.h_func, a.min, a.limit, a.silent, a.found_ptr);

    return NULL;
}

/**
 * Launch the cracking on multiple threads.
 *
 * @param hash_digest - the hash digest to crack ;
 * @param alf         - the alphabet ;
 * @param h_func      - the number of the hash function to use. Cf the doc of `hash` for the possible values ;
 * @param min         - the minimum length of the words to try ;
 * @param limit       - the maximum lenght of the words to try. If 0, there is no limit ;
 * @param silent      - if true, only prints the password. Otherwise, regularly shows progress.
 * @param nb_threads  - the number of threads to use. If 0, it will use the number of threads available on the current machine.
 */
void launch_multithreads(char* hash_digest, char* alf, int h_func, unsigned min, unsigned limit, bool silent, unsigned nb_threads) {
    //---Thread number
    if (nb_threads == 0) {
        nb_threads = (unsigned) sysconf(_SC_NPROCESSORS_ONLN);
    }

    //---Init
    pthread_t* threads = malloc(nb_threads * sizeof(pthread_t));
    crack_thread_arguments* args_arr = malloc(nb_threads * sizeof(crack_thread_arguments));
    bool found = false;

    //---Creation
    for (unsigned k = 0 ; k < nb_threads ; ++k) {
        args_arr[k].i = k;
        args_arr[k].n = nb_threads;
        args_arr[k].alf = alf;
        args_arr[k].expected_digest = hash_digest;
        args_arr[k].h_func = h_func;
        args_arr[k].min = min;
        args_arr[k].limit = limit;
        args_arr[k].silent = silent;
        args_arr[k].found_ptr = &found;


        pthread_create(threads + k, NULL, crack_thread_wrapper, args_arr + k);
    }

    //---Launch
    for (unsigned k = 0 ; k < nb_threads ; ++k)
        pthread_join(threads[k], NULL);

    //---Free
    free(threads);
}
