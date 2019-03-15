// ====================================================================
// Homework 5 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/15/2019
//
// This is a file for miscelaneous functions that are to be shared.
// ====================================================================

#include "header.h"

int append_node(edge_node * & root, edge_node * to_add){
    if (!root){
        root = to_add;
        return 1;
    }
    append_node(root->next, to_add);
    return 0; // Shouldn't happen in normal situations
}

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
