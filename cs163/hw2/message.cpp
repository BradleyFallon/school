#include "header.h"


// Initialize all of the member values of a newly created message
Message::Message(void){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
    author = NULL;
    body = NULL;
}

Message::~Message(void){
    if (body) delete body;
    if (author) delete author;
}

int Message::set_body(const char text[]){
    if (body) delete body;
    body = new char[strlen(text)+1];
    strcpy(body, text);
    return 1;
}

int Message::set_author(const char text[]){
    if (author) delete author;
    author = new char[strlen(text)+1];
    strcpy(author, text);
    return 1;
}


int Message::clone(Message & ref_msg){
    set_body(ref_msg.body);
    set_author(ref_msg.author);
    return 1;
}

// Displays all content of this job
void Message::display(){
    cout << "======================================" << endl
        << "Author:" << endl
        << '\t' << author << endl
        << "Message:" << endl
        << '\t' << body << endl
        << endl;
}