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
    set_author(ref_msg.author);
    set_subject(ref_msg.subject);
    set_date(ref_msg.date);
    set_body(ref_msg.body);
    return 1;
}

// Displays all content of this job
void Message::display(){
    cout << "======================================" << endl
        << "Author:" << endl
        << '\t' << author << endl
        << "Subject:" << endl
        << '\t' << author << endl
        << "Date:" << endl
        << '\t' << author << endl
        << "Message:" << endl
        << '\t' << body << endl
        << endl;
}