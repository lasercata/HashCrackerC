//------Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/parser.h"
#include "../include/utils.h"
#include "../include/multithread.h"

//------Signatures
void print_usage(char* argv0);
void print_help(char* argv0);

//------Implementations

void print_usage(char* argv0) {
    printf("Usage : %s [-h] [-V] [-s] [-A ALGORITHM] [-a ALPHABET] [-t NB_THREADS] [-m MIN] [-l LIMIT] HASH\n", argv0);
}

/**
 * Print the help message for the command line parser.
 *
 * @param argv0 - program name (argv[0] in the main function).
*/
void print_help(char* argv0) {
    print_usage(argv0);

    printf("\nMultithreaded hash cracker\n");

    printf("\nPositional arguments :\n");
    printf("    HASH                         The hash digest to crack (hex format)\n");

    printf("\nOptional arguments :\n");
    printf("    -h, --help                   Show this help message and exit\n");
    printf("    -V, --version                Show version and exit\n");
    printf("    -s, --silent                 Only print the password and nothing else\n");
    printf("    -A, --algorithm ALGORITHM    The hash algorithm. Defaults to 'md5'\n");
    printf("    -a, --alphabet ALPHABET      The alphabet to use. Can be '09', 'az', 'AZ', 'az09', 'azAZ', 'azAZ09', or a custom one\n");
    printf("    -t, --nb-threads NB_THREADS  Specify the number of threads to use\n");
    printf("    -m, --min MIN                try only words with at least MIN characters\n");
    printf("    -l, --limit LIMIT            If used, limit the length of words to LIMIT\n");
}


/**
 * Parse command line arguments and execute associated functions.
 */
int parse(int argc, char** argv) {
    //---Init
    char hash_digest[DIGEST_SIZE];
    char algo[7] = "md5";
    int h_func = 1;
    char alf[ALF_MAX_SIZE];
    strcpy(alf, alf_arr[1]);
    unsigned nb_threads = 0;
    unsigned min = 0;
    unsigned limit = 0;

    bool hash_digest_is_def = false;
    bool silent_is_def = false;
    bool algo_is_def = false;
    bool alf_is_def = false;
    bool thread_nb_is_def = false;
    bool min_is_def = false;
    bool limit_is_def = false;

    //---Parsing
    if (argc == 1) { //No arguments
        print_usage(argv[0]);
        printf("HashCracker: error: the following argument is requied: HASH\n");
        return 1;
    }

    for (int k = 1 ; k < argc ; k++) {
        if (strcmp(argv[k], "-h") == 0 || strcmp(argv[k], "--help") == 0) { // Help
            print_help(argv[0]);
            return 0;
        }
        else if (strcmp(argv[k], "-V") == 0 || strcmp(argv[k], "--version") == 0) { // Version
            printf("HashCracker %s (C implementation)\n", version);
            return 0;
        }

        else if (strcmp(argv[k], "-s") == 0 || strcmp(argv[k], "--silent") == 0) { // Silent
            silent_is_def = true;
        }

        else if (strcmp(argv[k], "-A") == 0 || strcmp(argv[k], "--algorithm") == 0) { // Algorithm
            if (algo_is_def) {
                print_usage(argv[0]);
                printf("HashCracker: error: too many arguments (argument -A/--algorithm repeated)\n");
                return 1;
            }

            if (k + 1 >= argc) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -A/--algorithm: expected one argument ALGO\n");
                return 1;
            }
            if (
                strcmp(argv[k + 1], "md5") != 0
                && strcmp(argv[k + 1], "sha1") != 0
                && strcmp(argv[k + 1], "sha256") != 0
                && strcmp(argv[k + 1], "sha512") != 0
            ) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -A/--algorithm: value should be 'md5', 'sha1', 'sha256' or 'sha512', but '%s' was found\n", argv[k + 1]);
                return 1;
            }

            strcpy(algo, argv[k + 1]);

            if (strcmp(algo, "md5") == 0)
                h_func = 1;
            else if (strcmp(algo, "sha1") == 0)
                h_func = 2;
            else if (strcmp(algo, "sha256") == 0)
                h_func = 3;
            else if (strcmp(algo, "sha512") == 0)
                h_func = 4;

            k++; // Jump the next value (it is algo).

            algo_is_def = true;
        }
        else if (strcmp(argv[k], "-a") == 0 || strcmp(argv[k], "--alphabet") == 0) { // Alphabet
            if (alf_is_def) {
                print_usage(argv[0]);
                printf("HashCracker: error: too many arguments (argument -a/--alphabet repeated)\n");
                return 1;
            }

            if (k + 1 >= argc) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -a/--alphabet: expected one argument ALGO\n");
                return 1;
            }

            for (int i = 0 ; i < ALF_NB ; ++i) {
                if (strcmp(argv[k + 1], alf_keys[i]) == 0) {
                    strcpy(alf, alf_arr[i]);
                    alf_is_def = true;
                    break;
                }
            }

            if (! alf_is_def)
                strcpy(alf, argv[k + 1]);

            k++; // Jump the next value (it is algo).

            alf_is_def = true;
        }

        else if (strcmp(argv[k], "-t") == 0 || strcmp(argv[k], "--nb-threads") == 0) { // Thread number
            if (thread_nb_is_def) {
                print_usage(argv[0]);
                printf("HashCracker: error: too many arguments (argument -t/--nb-threads repeated)\n");
                return 1;
            }
            if (k + 1 >= argc) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -t/--nb-threads: expected one argument NB_THREADS\n");
                return 1;
            }

            int tmp = atoi(argv[k + 1]);

            if (tmp <= 0) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -t/--nb-threads: value should be a strictly positive integer, but '%s' was found\n", argv[k + 1]);
                return 1;
            }

            nb_threads = (unsigned) tmp;

            k++; // Jump the next value (it is NB_THREADS).

            thread_nb_is_def = true;
        }
        else if (strcmp(argv[k], "-m") == 0 || strcmp(argv[k], "--min") == 0) { // Min
            if (min_is_def) {
                print_usage(argv[0]);
                printf("HashCracker: error: too many arguments (argument -m/--min repeated)\n");
                return 1;
            }
            if (k + 1 >= argc) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -m/--min: expected one argument MIN\n");
                return 1;
            }

            int tmp = atoi(argv[k + 1]);

            if (tmp <= 0) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -m/--min: value should be a strictly positive integer, but '%s' was found\n", argv[k + 1]);
                return 1;
            }

            min = (unsigned) tmp;

            k++; // Jump the next value (it is NB_THREADS).

            min_is_def = true;
        }
        else if (strcmp(argv[k], "-l") == 0 || strcmp(argv[k], "--limit") == 0) { // Limit
            if (limit_is_def) {
                print_usage(argv[0]);
                printf("HashCracker: error: too many arguments (argument -l/--limit repeated)\n");
                return 1;
            }
            if (k + 1 >= argc) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -l/--limit: expected one argument LIMIT\n");
                return 1;
            }

            int tmp = atoi(argv[k + 1]);

            if (tmp <= 0) {
                print_usage(argv[0]);
                printf("HashCracker: error: argument -l/--limit: value should be a strictly positive integer, but '%s' was found\n", argv[k + 1]);
                return 1;
            }

            limit = (unsigned) tmp;

            k++; // Jump the next value (it is NB_THREADS).

            limit_is_def = true;
        }

        else if (argv[k][0] == '-') { // Wrong argument
            print_usage(argv[0]);
            printf("HashCracker: error: unrecognized argument : '%s'\n", argv[k]);
            return 1;
        }

        else { // Hash digest
            if (hash_digest_is_def) {
                print_usage(argv[0]);
                printf("HashCracker: error: too many arguments\n");
                return 1;
            }
            
            strcpy(hash_digest, argv[k]);

            hash_digest_is_def = true;
        }
    }

    if (!hash_digest_is_def) {
        print_usage(argv[0]);
        printf("HashCracker: error: the following argument is requied: HASH\n");
        return 1;
    }
    
    //---Use arguments

    // printf("hash:       %s\n", hash_digest);
    // printf("algo:       %s\n", algo);
    // printf("alf:        %s\n", alf);
    // printf("nb_threads: %d\n", nb_threads);
    // printf("min:        %d\n", min);
    // printf("limit:      %d\n", limit);

    launch_multithreads(hash_digest, alf, h_func, min, limit, silent_is_def, nb_threads);

    return 0;
}
