// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 11/25/2018
// ====================================================================

// This file contains the struct definitions and prototypes of all classes.
// Note that "all classes" means all classes that I am creating for this homework assignment
// just in case you thought I meant all classes of some other context...
// Why would you even question that?

// WHAT THE HECK IS THIS PROGRAM
/*
The data structure is to store information about open employment position (i.e. job) postings.
The behavior is as if we have notecards for each job posting, and those cards are put into bins based on
the job site location. The bins are sorted alphabetically.

An application should allow the user to enter info for many jobs and be able to save this to a file.
The user should be able to open an existing file to load previously entered job data. We do not know
or care how the application will present the data to the user, but just in case, we have made display methods.
*/

// PROGRAM I/O
//INPUT: "./job_list.txt"
//OUTPUT: "./job_list.txt"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// This size is used for arrays that are recycled many times
// There should be very few existing arrays of this size
// For that reason it is large, becuase why not
const int SIZE=512;
const char FILENAME[15] = "./job_list.txt"; // The path where jobs list info should be saved

class Job {
    public:
        Job(void);
        ~Job(void);

        // Setters. These each take a char array arg and copy that to the member value.
        int set_company(const char text[]);
        int set_descrp(const char text[]);
        int set_qualfs(const char text[]);
        int set_degree(const char text[]);
        int set_loca(const char text[]);
        int set_spec(const char text[]);
        int set_pay(const char text[]);
        int set_rating(const float value);
        int set_review(const char text[]);

        // Setters. These each take the member value and copy that to the a ref char array arg
        int get_company(char text[]);
        int get_descrp(char text[]);
        int get_qualfs(char text[]);
        int get_degree(char text[]);
        int get_loca(char text[]);
        int get_spec(char text[]);
        int get_pay(char text[]);
        int get_rating();
        int get_review(char text[]);

        void display();

        int clone(const Job & ref_job);

    private:
        char * company;   // Name of the company (e.g., Apcon)
        char * descrp;    // A description  of  what  they  do (you know, _them_)
        char * qualfs;    // Qualifications (e.g., C, C++, Java, Has a pulse)
        char * degree;    // Degree Requirements (e.g., PhD in Gender Studies)
        char * loca;      // Location (e.g., Wilsonville)
        char * spec;      // Job Specification (e.g., Internship, boss-man)
        char * pay;       // Pay rate (e.g., $129,000 to $143,000)
        float  rating;    // Rating from 0.0 to 5.0(e.g, 2.499)
        char * review;    // Review (e.g., Keeps the local therapists busy.)
};

struct JobNode {
    Job job;
    JobNode * next = NULL;
};

struct LocaNode {
    char * loca_name;
    LocaNode * next = NULL;
    JobNode * head_job = NULL;
};

class JobList
{
    public:
        JobList(void);
        ~JobList(void);

        // Member functions (methods) to be used by client
	    int add_location(char * location);
        int add_job(const Job & ref_job, int loc_id);
        int remove_job(int loc_id, int job_id);
        int edit_review(int loc_id, int job_id, char * review);
        int display_loca_jobs(int loc_id);
        void display_locas();

    private:
        LocaNode * head;
        const char LOC_HEADER[10] = "location:"; // For marking a location in output file
        const char JOB_HEADER[5] = "job:"; // For marking a job in output file

        // Private helper methods not to be used directly by client.
        LocaNode * _new_location(char * location);
        LocaNode * _get_loca_ptr(int loc_id);
        JobNode * _get_job_ptr(JobNode * head_job, int job_id);
        void _write_file();
        void _read_file();
};