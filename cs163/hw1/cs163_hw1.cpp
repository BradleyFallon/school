// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/29/2019
// ====================================================================

// This file is for testing the ADT.
// This is a simple interface for manually testing if the ADT works as intended.
// main() is in this file.

// SEE HEADER FOR AN EXPLANATION OF THIS PROGRAM
#include "hw1_header.h"

// Prototypes - See definitions below
int read_task_no();
int define_job(Job & job);

// Main loop of the test interface
int main()
{

    JobList job_list;    // The list of jobs
    Job job;             // Temp job for the client to use to get data from user to ADT
    int loc_id = 0;      // For user to select a location
    int job_id = 0;      // For user to select a job
    char text[SIZE];     // Generic cstring to get text from user to copying elsewhere
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate


    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        // Option 1: Display jobs of a location.
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // Display jobs of a location.
            job_list.display_locas();
            cout << "Enter the id of the location to add job to, or '0' to cancel:" << endl;
            cin >> loc_id;
            cin.ignore(SIZE,'\n');
            if (loc_id){
                job_list.display_loca_jobs(loc_id);
            }
        }
        // Option 2: Add a new job to a location.
        else if (task_no == 2)
        {
            cout << "Option 2 selected!" << endl;
            // Add a new job to a location.
            // Show the locations and ask the user which location the job belongs to
            job_list.display_locas();
            cout << "Enter the id of the location to add job to, or '0' to cancel:" << endl;
            cin >> loc_id;
            cin.ignore(SIZE,'\n');
            if (loc_id){
                // Get the definition of the job from the user, then insert at location
                define_job(job);
                if (job_list.add_job(job, loc_id)){
                    cout << "Job addded successfully!" << endl;
                } else {
                    cout << "Failed to add job! :'(  " << endl;
                }
            }
        }
        // Option 3: Add a new location.
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            cout <<"Please enter the location name: (e.g., Wilsonville, Paris-France)" << endl;
            cin.get(text, SIZE, '\n');
            cin.ignore(SIZE,'\n');
            if (!job_list.add_location(text)){
                cout << "That location was already defined." << endl;
            }
            cout << "Location added." << endl;
            job_list.display_locas();
        }
        // Option 4: Rewrite a job's review.
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // Rewrite a job's review.
            job_list.display_locas();
            cout << "Enter the id of the location to add job to, or '0' to cancel:" << endl;
            cin >> loc_id;
            cin.ignore(SIZE,'\n');
            if (loc_id){
                job_list.display_loca_jobs(loc_id);
                cout << "Enter the id of the location to add job to, or '0' to cancel:" << endl;
                cin >> job_id;
                cin.ignore(SIZE,'\n');
                if (job_id){
                    cout <<"Please enter the new review." << endl;
                    cin.get(text, SIZE, '\n');
                    cin.ignore(SIZE,'\n');
                    if (!job_list.edit_review(loc_id, job_id, text)){
                        cout << "Sorry, that didn't work. Pick a valid index next time." << endl;
                    }
                }
            }


        }
        // Option 5: Remove a job.
        else if (task_no == 5)
        {
            cout << "Option 5 selected!" << endl;
            // Remove a job.
            job_list.display_locas();
            cout << "Enter the id of the location to add job to, or '0' to cancel:" << endl;
            cin >> loc_id;
            cin.ignore(SIZE,'\n');
            if (loc_id){
                job_list.display_loca_jobs(loc_id);
                cout << "Enter the id of the location to add job to, or '0' to cancel:" << endl;
                cin >> job_id;
                cin.ignore(SIZE,'\n');
                if (job_id){
                    if (!job_list.remove_job(loc_id, job_id)){
                        cout << "Sorry, that didn't work. Pick a valid index next time." << endl;
                    }
                }
            }
        }
        // Option 6: Quit and save job list to file.
        else if (task_no == 6)
        {
            cout << "Option 6 selected!" << endl;
            // Quit and save job list to file.
            // Just quit the loop and the list's destructor
            // will be called later to handle the rest.
            do_run = false;
        }
        // Invalid option
        else
        {
            // Invalid response
            cout << "That was not a valid option, please try again." << endl;
        }
    }
    return 0;
}


// This is used to prompt user for job propeties and set them to the temp job
int define_job(Job & job){
    char text[SIZE];
    float dec_num;

    // All of the setters for text values are the same idea
    // We get a cstring drom the user, then call the job's setter method to apply
    // I didn't actually come up wait a failure condition for the setter,
    // so I am not useing any return value for text setters.
    cout <<"Please enter the company name: (e.g., Apcon)" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_company(text);

    cout <<"Please enter the company description:" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_descrp(text);

    cout <<"Please enter the job qualifications: (e.g., C, C++, Java, Has a pulse)" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_qualfs(text);

    cout <<"Please enter the degree requirement: (e.g., PhD in Computational Gender Studies)" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_degree(text);

    cout <<"Please enter the job title/spec: (e.g., Internship, big-boss)" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_spec(text);

    cout <<"Please enter the job pay: (e.g., $129,000 to $143,000)" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_pay(text);

    // This setter actually has a condition to return 0 for failure
    // Request a rating until the setter returns a positive value
    do {
        cout <<"Please enter a rating from 0.0 to 5.0: (e.g, 2.499)" << endl;
        cin >> dec_num;
        cin.ignore(SIZE,'\n');
    } while (!job.set_rating(dec_num));

    cout <<"Please enter a review: (e.g., Keeps the local therapists busy.)" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    job.set_review(text);
    
}

// Read from user which task they want to perform
int read_task_no()
{
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    while (!(option >=1 & option <= 6))
    {
        // After first try, print failed message
        if (failed)
        {
            cout << "Invalid response. Please try again." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nSup dude. What you wanna do man?" << endl
            << "1: Display jobs of a location." << endl
            << "2: Add a new job to a location." << endl
            << "3: Add a new location." << endl
            << "4: Rewrite a job's review." << endl
            << "5: Remove a job." << endl
            << "6: Quit and save job list to file." << endl
            << "\nEnter a number to enjoy an option." << endl
            << endl;
        cin >> option;
        cin.ignore(SIZE, '\n');
    }
    return option;
}


/* Reference of how Lab 2 handled setting values to our node data object
   I don't want to have a create_job function that takes 12 arguments, so this approach wont work for me 
   //Let's create some journal entries
    do
    {
       cout <<"Please enter the title of your journal entry\n";
       cin.get(title, SIZE, '\n'); cin.ignore(SIZE,'\n');
       cout <<"Please enter your notes\n";
       cin.get(notes, SIZE, '\n'); cin.ignore(SIZE,'\n');
       
       //Now create the journal entry
       if (entry.create_entry(title, notes)) 
           //if this was successful, let's add it to the list!
            
          if (! my_journal.add(entry))
              cerr << "We were unable to add it to the list...\n";
     } while (again());
*/