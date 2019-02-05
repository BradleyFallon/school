#include "header.h"


// Initialize all of the member values of a newly created message
Message::Message(void){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
    author = NULL;
    body = NULL;
}

Message::~Message(void){

}

int Message::set_body(const char text[]){
    if (body) delete body;
    body = new char[strlen(text)+1];
    strcpy(body, text);
    return 0;
}

int Message::set_author(const char text[]){
    if (author) delete author;
    author = new char[strlen(text)+1];
    strcpy(author, text);
    return 0;
}


int Message::clone(Message & ref_msg){
    set_body(ref_msg.body);
    return 0;
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