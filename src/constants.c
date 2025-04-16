#include "../include/constants.h"

const char alf_arr[ALF_NB][ALF_MAX_SIZE] = {
    "0123456789",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyz0123456789",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
};

const char alf_keys[ALF_NB][ALF_MAX_SIZE] = {
    "09",
    "az",
    "AZ",
    "az09",
    "azAZ",
    "azAZ09"
};
