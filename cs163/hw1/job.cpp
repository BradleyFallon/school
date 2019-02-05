// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/29/2019
// ====================================================================

// This file is for defining the Job class.
// This is the info card that contains the jobs properties.
// Contains the methods for getting and setting these properties.

// SEE HEADER FOR AN EXPLANATION OF THIS PROGRAM
#include "hw1_header.h"

// Initialize all of the member values of a newly created job
Job::Job(void){
    // Set all pointers to null
    // Note: When deleting null pointers, don't
    company = NULL;
    descrp = NULL;
    qualfs = NULL;
    degree = NULL;
    loca = NULL;
    spec = NULL;  
    pay = NULL;   
    rating = 0.0; // This one is a float, not a pointer
    review = NULL;
}

// Deallocate all memory associated with this job when deleting
Job::~Job(void){
    // When scrapping a job card, delete all of the dynamic arrays
    if (company) delete company;
    if (descrp) delete descrp;
    if (qualfs) delete qualfs;
    if (degree) delete degree;
    if (spec) delete spec;
    if (pay) delete pay;
    if (review) delete review;
}

int Job::set_company(const char text[]){
    if (company) delete company;
    company = new char[strlen(text)+1];
    strcpy(company, text);
}

int Job::set_descrp(const char text[]){
    if (descrp) delete descrp;
    descrp = new char[strlen(text)+1];
    strcpy(descrp, text);
}

int Job::set_qualfs(const char text[]){
    if (qualfs) delete qualfs;
    qualfs = new char[strlen(text)+1];
    strcpy(qualfs, text);
}

int Job::set_degree(const char text[]){
    if (degree) delete degree;
    degree = new char[strlen(text)+1];
    strcpy(degree, text);
}

int Job::set_loca(const char text[]){
    if (loca) delete loca;
    loca = new char[strlen(text)+1];
    strcpy(loca, text);
}

int Job::set_spec(const char text[]){
    if (spec) delete spec;
    spec = new char[strlen(text)+1];
    strcpy(spec, text);
}

int Job::set_pay(const char text[]){
    if (pay) delete pay;
    pay = new char[strlen(text)+1];
    strcpy(pay, text);
    return 1;
}

int Job::set_review(const char text[]){
    if (review) delete review;
    review = new char[strlen(text)+1];
    strcpy(review, text);
    return 1;
}

int Job::set_rating(const float value){
    if (value >= 0 && value <= 5.0){
        rating = value;
        return 1;
    }
    // Invalid number for rating
    return 0;
}



int Job::get_company(char text[]){
    strcpy(text, company);
    return 1;
}

int Job::get_descrp(char text[]){
    strcpy(text, descrp);
    return 1;
}

int Job::get_qualfs(char text[]){
    strcpy(text, qualfs);
    return 1;
}

int Job::get_degree(char text[]){
    strcpy(text, degree);
    return 1;
}

int Job::get_loca(char text[]){
    strcpy(text, loca);
    return 1;
}

int Job::get_spec(char text[]){
    strcpy(text, spec);
    return 1;
}

int Job::get_pay(char text[]){
    strcpy(text, pay);
    return 1;
}

int Job::get_review(char text[]){
    strcpy(text, review);
    return 1;
}

int Job::get_rating(){
    return rating;
}




// Take all values from referenced job and set same vals to this job
int Job::clone(const Job & ref_job){
    cout << "in clone" << endl;
    set_company(ref_job.company);
    cout << "in company" << endl;
    set_descrp(ref_job.descrp);
    set_qualfs(ref_job.qualfs);
    set_degree(ref_job.degree);
    set_spec(ref_job.spec);
    set_pay(ref_job.pay);
    set_rating(ref_job.rating);
    set_review(ref_job.review);
    return 1;
}

// Displays all content of this job
void Job::display(){
    cout << "======================================" << endl
        << "Company:" << endl
        << '\t' << company << endl
        << "Company Description:" << endl
        << '\t' << descrp << endl
        << "Qualifications:" << endl
        << '\t' << qualfs << endl
        << "Degree Requirements:" << endl
        << '\t' << degree << endl
        << "Job Specification:" << endl
        << '\t' << spec << endl
        << "Pay rate:" << endl
        << '\t' << pay << endl
        << "Rating:" << endl
        << '\t' << rating << endl
        << "Review:" << endl
        << '\t' << review
        << endl;
        // I want the client to be able to display a job without loaction if loca is a null pointer
        // I am having the location set by selecting which location it is inserted to
        // A job card that exists outside a list will not have a location
        if (loca) {
            cout
            << "Location:" << endl
            << '\t' << loca << endl;
        }
}
