// ====================================================================
// Homework 4 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/11/2019
//
// ====================================================================

// This is the Term class. It is for storing, retreiving and displaying Term data.

#include "header.h"

// Initialize all of the member values of a newly created Term
Term::Term(void){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
    word = NULL;
    description = NULL;
    category = NULL;
}

Term::~Term(void){
    if (word) delete[] word;
    if (description) delete[] description;
    if (category) delete[] category;
}

int Term::set_word(const char text[]){
    if (word) delete[] word;
    word = new char[strlen(text)+1];
    strcpy(word, text);
    make_lower(word);
    return 1;
}

int Term::get_word(char text[]){
    strcpy(text, word);
    return 1;
}

int Term::set_description(const char text[]){
    if (description) delete[] description;
    description = new char[strlen(text)+1];
    strcpy(description, text);
    make_lower(description);
    return 1;
}

int Term::set_category(const char text[]){
    if (category) delete[] category;
    category = new char[strlen(text)+1];
    strcpy(category, text);
    make_lower(category);
    return 1;
}

bool Term::is_less(const char text[]){
    if (strcmp(word, text) < 0) return true;
    return false;
}

bool Term::is_less(const Term & other){
    if (strcmp(word, other.word) < 0) return true;
    return false;
}

int Term::clone(Term & ref_chan){
    // If the ref Term was poorly defined, return 0
    if (ref_chan.word){
        set_word(ref_chan.word);
    } else return 0;
    if (ref_chan.description){
        set_description(ref_chan.description);
    } else return 0;
    if (ref_chan.category){
        set_category(ref_chan.category);
    } else return 0;
    return 1;
}

// Displays all content of this Term
void Term::display(){
    if (word && description && category){
        cout << "======================================" << endl
            << "word:" << endl
            << '\t' << word << endl
            << "description:" << endl
            << '\t' << description << endl
            << "category:" << endl
            << '\t' << category << endl
            << endl;
    } else {
        cout << "Term not fully defined!" << endl;
    }
}
