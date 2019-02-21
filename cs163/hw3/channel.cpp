//====================================================================
// Homework 2 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 2/8/2019
// ====================================================================

// This is the Channel class. It is for storing, retreiving and displaying Channel data.

#include "header.h"


// Initialize all of the member values of a newly created Channel
Channel::Channel(void){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
    name = NULL;
    num_keys = 0;
    description = NULL;
    notes = NULL;
    rating = 0;
    // The TextList of search keys should be innitialized by the TextList class
}

Channel::~Channel(void){
    if (name) delete name;
    if (description) delete description;
    if (notes) delete notes;
}

int Channel::set_name(const char text[]){
    if (name) delete name;
    name = new char[strlen(text)+1];
    strcpy(name, text);
    return 1;
}

int Channel::set_description(const char text[]){
    if (description) delete description;
    description = new char[strlen(text)+1];
    strcpy(description, text);
    return 1;
}

int Channel::set_notes(const char text[]){
    if (notes) delete notes;
    notes = new char[strlen(text)+1];
    strcpy(notes, text);
    return 1;
}


int Channel::clone(Channel & ref_msg){
    // If the ref Channel was poorly defined, return 0
    if (ref_msg.name){
        set_name(ref_msg.name);
    } else return 0;
    if (ref_msg.description){
        set_description(ref_msg.description);
    } else return 0;
    if (ref_msg.notes){
        set_notes(ref_msg.notes);
    } else return 0;
    if (ref_msg.body){
        set_body(ref_msg.body);
    } else return 0;
    return 1;
}

// Displays all content of this job
void Channel::display(){
    if (name && description && notes && body){
        cout << "======================================" << endl
            << "name:" << endl
            << '\t' << name << endl
            << "description:" << endl
            << '\t' << description << endl
            << "notes:" << endl
            << '\t' << notes << endl
            << "Channel:" << endl
            << '\t' << body << endl
            << endl;
    } else {
        cout << "Channel not fully defined!" << endl;
    }
}