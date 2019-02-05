// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/29/2019
// ====================================================================

// This file is for defining the JobList class

// SEE HEADER FOR AN EXPLANATION OF THIS PROGRAM
#include "hw1_header.h"

// This is just a helper to create a new location node, no insert
LocaNode * JobList::_new_location(char * location_name){
    LocaNode * new_loca;

    // Define the new location node
    new_loca = new LocaNode;
    new_loca->loca_name = new char[strlen(location_name)+1];
    strcpy(new_loca->loca_name, location_name);
    new_loca->next = NULL;
    new_loca->head_job = NULL;

    return new_loca;
}

// This will create a new location node and insert it alphabetically
int JobList::add_location(char * location_name){
    LocaNode * new_loca;
    LocaNode * current = head;
    LocaNode * prev = head;
    int comp_val; // return value of alphabetical comparison

    // Define the new location node
    new_loca = _new_location(location_name);

    // Insert the new location node
    if (!head){
        head = new_loca;
        // Great success!
        return 1;
    }

    while (current){
        comp_val = strcmp(new_loca->loca_name, current->loca_name);
        if (!comp_val){
            // The location names of new and current are the same, discard new
            // No duplicate locations allowed
            // Forget that new garbage
            delete new_loca;
            // Inform the client of their failure
            return 0;
        }
        if (comp_val < 0){
            // The new name is alphabetically before the current
            // At this point, current belongs alphabetically after new
            // and prev belongs alphabetically before new.
            // Insert new between prev and current.
            // Insert NOW! then return 1.
            new_loca->next = current;
            // If prev is still head, then we havent really traversed yet and
            // we need to set new_loca to be head.
            // Otherwise, if we are at the middle somewhere, prev points
            // to new as next.
            if (head==current){
                head = new_loca;
            } else {
                prev->next = new_loca;
            }
            return 1;
        }
        // Still searching...
        // If there are more nodes and we havent inserted yet, traverse.
        prev = current;
        current = current->next;
    }

    // Looks like we got to the end of the list and didn't need to insert yet.
    // This means that our new goes at the end of the list.
    prev->next = new_loca;
    return 1;
}

// This will display all location nodes along with user friendly indexes
void JobList::display_locas(){
    LocaNode * current = head;
    int loc_id = 1; // Starts at 1, not 0. This is so 0 can be used to cancel in client.

    cout << "=============== Locations ==============="  << endl;
    while (current){
        cout << loc_id << ") " << current->loca_name << endl;
        current = current->next;
        ++loc_id;
    }
}

// Returns the pointer to a location node at a given index
// This is private because we don't want the client using our precious pointers
LocaNode * JobList::_get_loca_ptr(int loc_id){
    // Gets the node ptr at a given index
    // Index counts from 1 not 0

    LocaNode * current_loca = head;
    int current_id = 1;

    if (!head){
        return 0;
    }

    // traverse to the designated location bin
    while (current_loca->next && current_id<loc_id){
        ++current_id;
        current_loca = current_loca->next;
    }

    if (current_id==loc_id){
        return current_loca;
    }

    return 0;
}

// This adds a job card to a location specified by index
int JobList::add_job(const Job & ref_job, int loc_id){
    JobNode * new_job_node;
    LocaNode * current_loca;

    // Retreive the pointer of location node at loc_id index
    current_loca = _get_loca_ptr(loc_id);

    if (current_loca){
        new_job_node = new JobNode;
        // copy the reference job to a new job
        new_job_node->job.clone(ref_job);
        // Set the location of the job to the name of the current loca
        new_job_node->job.set_loca(current_loca->loca_name);
        // Insert at fron of location's job list
        new_job_node->next = current_loca->head_job;
        current_loca->head_job = new_job_node;
        return 1;
    }

    // If we didnt return earlier,
    // then we failed to find the target location.
    return 0;
}

// Returns the pointer to a job node at a given index
// This is private because we don't want the client using our precious pointers
JobNode * JobList::_get_job_ptr(JobNode * head_job, int job_id){
    if (!head_job | !job_id) return NULL;
    if (job_id == 1) return head_job;
    return _get_job_ptr(head_job->next, --job_id);
}

// This remmoves and deletes a job at a given index pair
int JobList::remove_job(int loc_id, int job_id){
    JobNode * current_job_node;
    JobNode * previous_job_node;
    LocaNode * current_loca;

    // Retreive the pointer of location node at loc_id index
    current_loca = _get_loca_ptr(loc_id);

    if (current_loca){
        // Retreive the job at the job_id index
        
        current_job_node = current_loca->head_job;

        if (!current_job_node) return 0;
        if (job_id == 1){
            current_loca->head_job = current_job_node->next;
            delete current_job_node;
            return 1;
        }
        while (current_job_node->next){
            previous_job_node = current_job_node;
            current_job_node = current_job_node->next;
            --job_id;
            if (job_id == 1){
                previous_job_node->next = current_job_node->next;
                delete current_job_node;
                return 1;
            }
        }
    }
    // If we didnt return earlier,
    // then we failed to find the target location.
    return 0;
}

// This will get the job at  agiven index pair and set its review value
int JobList::edit_review(int loc_id, int job_id, char * review){
    JobNode * target_job;
    LocaNode * current_loca;

    // Retreive the pointer of location node at loc_id index
    current_loca = _get_loca_ptr(loc_id);

    if (current_loca){
        // Retreive the job at the job_id index
        target_job = _get_job_ptr(current_loca->head_job, job_id);
        target_job->job.set_review(review);
        return 1;
    }

    // If we didnt return earlier,
    // then we failed to find the target location.
    return 0;
}

// Displays jobs at a location specified by location index
int JobList::display_loca_jobs(int loc_id){
    LocaNode * current_loca;
    int current_job_id = 1; // Starts at 1, not 0. This is so 0 can be used to cancel in client.
    JobNode * current_job = NULL;

    // Retreive the pointer of location node at loc_id index
    current_loca = _get_loca_ptr(loc_id);

    if (current_loca){
        current_job = current_loca->head_job;
    } else {
        // Could not find the location node
        return 0;
    }

    cout << "================= Jobs ================="  << endl;
    while (current_job){
        cout << current_job_id << ") " << endl;
        current_job->job.display();
        current_job = current_job->next;
        ++current_job_id;
    }

}

// Read all apartments info from a file.
void JobList::_read_file(){
    ifstream infile;
    LocaNode * current_loca = head;
    LocaNode * new_loca = head;
    JobNode * new_job = NULL;
    JobNode * current_job = NULL;
    float dec_num;

    char text[SIZE];

    char line_chars[SIZE];
    
    infile.open(FILENAME);


    // Make sure this existed and was not empty before attempting to read
    if (infile)
    {
        // Read the file header to prep the .eof() functionality
        infile.get(text, SIZE, '\n');
        infile.ignore(SIZE,'\n');

        while (infile && !infile.eof())
        {
            // Read the current line of file, this should be an objet header
            infile.get(text, SIZE, '\n');
            infile.ignore(SIZE,'\n');

            // Check if this is a location header
            if (!strcmp(text, LOC_HEADER)){
                // Make a new location with this title
                // Read the location name
                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                new_loca = _new_location(text);
                if (!head){
                    head = new_loca;
                } else {
                    current_loca->next = new_loca;
                }
                current_loca = new_loca;
            } // End read loc

            // Check if this is a job header
            if (!strcmp(text, JOB_HEADER)){
                // Make a new job read from file and append to current loca
                new_job = new JobNode;
                if (!current_loca->head_job){
                    current_loca->head_job = new_job;
                } else {
                    current_job -> next = new_job;
                }
                current_job = new_job;

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_company(text);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_descrp(text);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_qualfs(text);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_degree(text);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_loca(text);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_spec(text);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_pay(text);

                infile >> dec_num;
                infile.ignore(SIZE,'\n');
                current_job->job.set_rating(dec_num);

                infile.get(text, SIZE, '\n');
                infile.ignore(SIZE,'\n');
                current_job->job.set_review(text);
            } // End read job
        }// end file work
        infile.close();
        infile.clear();
    }
}

// Write all apartments info to a file.
void JobList::_write_file(){
    ofstream outfile;
    LocaNode * current_loca = head;
    JobNode * current_job = NULL;
    char text[SIZE];

    char line_chars[SIZE];
    
    outfile.open(FILENAME);

    if (outfile)
    {
        outfile << "HEADING" << endl;
        while (current_loca)
        {
            // Write the location to file
            outfile << LOC_HEADER << endl;
            outfile << current_loca->loca_name << endl;

            // Write all apartments of this location to file

            current_job = current_loca->head_job;

            while (current_job){

                outfile << JOB_HEADER << endl;
                current_job->job.get_company(text);
                outfile << text << endl;
                current_job->job.get_descrp(text);
                outfile << text << endl;
                current_job->job.get_qualfs(text);
                outfile << text << endl;
                current_job->job.get_degree(text);
                outfile << text << endl;
                current_job->job.get_loca(text);
                outfile << text << endl;
                current_job->job.get_spec(text);
                outfile << text << endl;
                current_job->job.get_pay(text);
                outfile << text << endl;
                outfile << current_job->job.get_rating() << endl;
                current_job->job.get_review(text);
                outfile << text << endl;

                current_job = current_job->next;
            }

            current_loca = current_loca->next;
        }
        outfile.close();
        outfile.clear();
    }
}

// Reads the job list from file
JobList::JobList(void){
    head = NULL;
    _read_file();
}

// writes the job list to file and deallocates memoy
JobList::~JobList(void){
    JobNode * current_job;
    LocaNode * current_loc;

    _write_file();

    // After the data has been saved to file, delete everything
    while (head)
    {
        while (head->head_job){
            current_job = head->head_job;
            head->head_job = current_job->next;
            // Job class has its own destructor
            // The job data object is not a pointer,
            // so I think it will be deleted with the node
            delete current_job->next;
        }
        current_loc = head;
        head = current_loc->next;
        delete current_loc;
    }
}


