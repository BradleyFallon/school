// ====================================================================
// Homework 3 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/31/2019
//
// Hash Table Class Definition File.
// ====================================================================

#include "header.h"


HashTable::~HashTable(void){
    // Initialize the has table with null pointers
    hash_array = new Channel*[SIZE_TBLARY];
    for (int i=0; i<SIZE_TBLARY; ++i)
        hash_array[i] = NULL;
};

HashTable::HashTable(void){
};

int HashTable::add_channel(){
    return 1;
};

int HashTable::copy_channel(){
    return 1;
};

int HashTable::get_hash(const char text[]){
    int hash_val = 0;
    int text_len;

    text_len = strlen(text);
    // Do not attempt to hash if no text given. Hash will remain 0 if text_len==0
    // To get hash, sum each character's ascii value multiplied by position
    for (int i=0; i<text_len; ++i){
        hash_val = hash_val + (i+1)*text[i];
    }

    return hash_val;
};

int HashTable::search_keyword(){
    return 1;
};

int HashTable::display_matches(){
    return 1;
};

int HashTable::display_all(){
    return 1;
};

int HashTable::remove_by_name(){
    return 1;
};
