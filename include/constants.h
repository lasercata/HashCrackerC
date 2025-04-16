#ifndef __CONSTANTS_H
#define __CONSTANTS_H

//---Version
#define version "v1.0.0"

//---Hash
#define DIGEST_SIZE 256

//---Alphabets
#define ALF_MAX_SIZE 512
#define ALF_NB 6

extern const char alf_arr[ALF_NB][ALF_MAX_SIZE];
//     "0123456789",
//     "abcdefghijklmnopqrstuvwxyz",
//     "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
//     "abcdefghijklmnopqrstuvwxyz0123456789",
//     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
//     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
// };

extern const char alf_keys[ALF_NB][ALF_MAX_SIZE];
//     "09",
//     "az",
//     "AZ",
//     "az09",
//     "azAZ",
//     "azAZ09"
// };

#endif

