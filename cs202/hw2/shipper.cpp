/*
================================================================================
Homework 2 for CS202
Bradley Fallon
bfallon@pdx.edu
5/8/2019

This contains the implementation of the shipper class and all derived classes.
================================================================================
*/

// This is the shippy class. It is for storing, retreiving and displaying shippy data.
#include "header.h"


// Initialize all of the member values of a newly created shippy
Shipper::Shipper(): contact_to(NULL), contact_from(NULL), contents(NULL){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
}

// The copy constructor needs to set the dynamic memory pointers to null because
// I am making use of the clone function which deletes non-null pointers before
// setting values.
Shipper::Shipper(const Shipper & ref_shippy): contact_to(NULL), contact_from(NULL), contents(NULL){
    clone(ref_shippy);
}

void Shipper::clone(const Shipper & ref_shippy){
    set_contact_to(ref_shippy.contact_to);
    set_contact_from(ref_shippy.contact_from);
    set_contents(ref_shippy.contents);
}

Shipper::~Shipper(){
    if (contact_to) delete [] contact_to;
    if (contact_from) delete [] contact_from;
    if (contents) delete [] contents;
}

int Shipper::set_contact_to(const char text[]){
    if (contact_to) delete [] contact_to;
    contact_to = new char[strlen(text)+1];
    strcpy(contact_to, text);
    return 1;
}

int Shipper::set_contact_from(const char text[]){
    if (contact_from) delete [] contact_from;
    contact_from = new char[strlen(text)+1];
    strcpy(contact_from, text);
    return 1;
}

int Shipper::set_contents(const char text[]){
    if (contents) delete [] contents;
    contents = new char[strlen(text)+1];
    strcpy(contents, text);
    return 1;
}

// Displays all content of this job
void Shipper::display(){
    if (contact_to && contact_from && contents){
        cout << "======================================" << endl
            << "Recipient:" << endl
            << '\t' << contact_to << endl
            << "Sender:" << endl
            << '\t' << contact_from << endl
            << "Content:" << endl
            << '\t' << contents << endl
            << endl;
    } else {
        cout << "Shipper not fully defined!" << endl;
    }
}


////////////////////////////////////////////////////////////////////////////////
SignedShipper::SignedShipper(void): Shipper(), is_signed(false){
}

SignedShipper::SignedShipper(const Shipper & ref_shippy): Shipper(ref_shippy), is_signed(false){
}

SignedShipper::SignedShipper(const SignedShipper & ref_shippy): Shipper(ref_shippy){
    is_signed = ref_shippy.is_signed;
}

void SignedShipper::display(){
    Shipper::display();
    cout << "Signed package info:" << endl;
    if (is_signed)
        cout << '\t' << "The recipient has signed." << endl;
    else cout << '\t' << "The recipient has NOT signed." << endl;
}

int SignedShipper::sign() {is_signed = true; return 1;}

////////////////////////////////////////////////////////////////////////////////
InstalledShipper::InstalledShipper(void): SignedShipper(), is_installed(false){
}

InstalledShipper::InstalledShipper(const Shipper & ref_shippy): SignedShipper(ref_shippy), is_installed(false){
}

InstalledShipper::InstalledShipper(const SignedShipper & ref_shippy): SignedShipper(ref_shippy), is_installed(false){
}

InstalledShipper::InstalledShipper(const InstalledShipper & ref_shippy): SignedShipper(ref_shippy){
    is_installed = ref_shippy.is_installed;
}

void InstalledShipper::display(){
    SignedShipper::display();
    cout << "Installation info:" << endl;
    if (is_signed)
        cout << '\t' << "The installation is complete." << endl;
    else cout << '\t' << "Not installed." << endl;
}

int InstalledShipper::install() {is_installed = true; return 1;}

////////////////////////////////////////////////////////////////////////////////
GiftShipper::GiftShipper(void): Shipper(), exchange_policy(NULL){
    exchange_policy = new char[42];
    strcpy(exchange_policy, "Throw item in trash and send us an email.");
}

GiftShipper::GiftShipper(const Shipper & ref_shippy): Shipper(ref_shippy){
    exchange_policy = new char[42];
    strcpy(exchange_policy, "Throw item in trash and send us an email.");
}

GiftShipper::GiftShipper(const GiftShipper & ref_shippy): Shipper(ref_shippy){
    exchange_policy = new char[42];
    strcpy(exchange_policy, "Throw item in trash and send us an email.");
}

GiftShipper::~GiftShipper(){
    if (exchange_policy) delete [] exchange_policy;
}

void GiftShipper::display(){
    Shipper::display();
    cout << "Gift Info:" << endl;
    cout << '\t' << "This is a gift, the exchange policy must be printed for recipient:\n"
    << exchange_policy << endl;
}
