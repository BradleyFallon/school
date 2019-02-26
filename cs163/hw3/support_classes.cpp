//====================================================================
// Homework 2 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 2/8/2019
// ====================================================================

// This file is for defining supporting classes that do not deserve 
// their own file..

#include "header.h"


/*
This class is a linear linked list of character arrays.
*/

TextList::TextList(void){
    head = NULL;
}

TextList::~TextList(void){

}

CharsNode * TextList::get_head(){
    return head;
}

int TextList::insert(const char text[]){
    // Creates a new node and inserts at head, unsorted
    CharsNode * new_node;

    // Create the new node and copy text
    new_node = new CharsNode;
    new_node->txt = new char[strlen(text)+1];
    strcpy(new_node->txt, text);
    
    // Insert at head, unsorted
    new_node->next = head;
    head = new_node;

    return 1;
}

int TextList::copy(TextList & other){
    delete_all();
    return copy_rec(head, other.head);
}

int TextList::copy_rec(CharsNode * & head, CharsNode * & other_head){
    if (!other_head){
        head = NULL;
        return 0;
    }
    head = new CharsNode;
    head->txt = new char[strlen(other_head->txt)+1];
    strcpy(head->txt, other_head->txt);
    copy_rec(head->next, other_head->next);
    return 1;
}

int TextList::delete_all(){
    if (!head) return 0;
    delete_all_rec(head);
    return 1;
}

int TextList::delete_all_rec(CharsNode * head){
    if (!head) return 0;
    delete_all_rec(head->next);
    delete head->txt;
    delete head;
    return 1;
} 