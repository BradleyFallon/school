// ====================================================================
// Homework 4 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/11/2019
//
// Miscellaneous shared functions file.
// ====================================================================

#include "header.h"

// Make all characters of a char array lowered
int make_lower(char text[]){
    int i = 0;
    while (text[i])
    {
        text[i] = tolower(text[i]);
        ++i;
    }
    return 1;
}