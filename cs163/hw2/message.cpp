//====================================================================
// Homework 2 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 2/8/2019
// ====================================================================

// This is the message class. It is for storing, retreiving and displaying message data.

#include "header.h"


// Initialize all of the member values of a newly created message
Message::Message(void){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
    author = NULL;
    subject=NULL;
    date=NULL;
    body = NULL;
}

Message::~Message(void){
    if (author) delete author;
    if (subject) delete subject;
    if (date) delete date;
    if (body) delete body;
}

int Message::set_author(const char text[]){
    if (author) delete author;
    author = new char[strlen(text)+1];
    strcpy(author, text);
    return 1;
}

int Message::set_subject(const char text[]){
    if (subject) delete subject;
    subject = new char[strlen(text)+1];
    strcpy(subject, text);
    return 1;
}

int Message::set_date(const char text[]){
    if (date) delete date;
    date = new char[strlen(text)+1];
    strcpy(date, text);
    return 1;
}

int Message::set_body(const char text[]){
    if (body) delete body;
    body = new char[strlen(text)+1];
    strcpy(body, text);
    return 1;
}

int Message::clone(Message & ref_msg){
    // If the ref message was poorly defined, return 0
    if (ref_msg.author){
        set_author(ref_msg.author);
    } else return 0;
    if (ref_msg.subject){
        set_subject(ref_msg.subject);
    } else return 0;
    if (ref_msg.date){
        set_date(ref_msg.date);
    } else return 0;
    if (ref_msg.body){
        set_body(ref_msg.body);
    } else return 0;
    return 1;
}

// Displays all content of this job
void Message::display(){
    if (author && subject && date && body){
        cout << "======================================" << endl
            << "Author:" << endl
            << '\t' << author << endl
            << "Subject:" << endl
            << '\t' << subject << endl
            << "Date:" << endl
            << '\t' << date << endl
            << "Message:" << endl
            << '\t' << body << endl
            << endl;
    } else {
        cout << "Message not fully defined!" << endl;
    }
}