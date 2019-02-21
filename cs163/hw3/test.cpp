#include "header.h"

const int SIZE = 256;

// Prototypes - See definitions below
int auto_test();
int read_task_no();
int define_channel(Channel & ref_chan);

// Main loop of the test interface
int main()
{
    Channel ref_chan;
    HashTable my_table;
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate

    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // 1: Add a new Channel to stack.
        }
        else if (task_no == 2)
        {
            cout << "Option 2 selected!" << endl;
            // 2: Search by keyword, display all matches
        }
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            // 3: Remove channel by name
        }
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // 4: Display all.
        }
        else if (task_no == 5)
        {
            cout << "Option 5 selected!" << endl;
            // 5: Run Autotest.
            auto_test();
        }
        else if (task_no == 6)
        {
            cout << "Option 6 selected!" << endl;
            // 6: Exit.
            cout << "Goodbye!" << endl;
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

int auto_test(){
    cout << "Auto-test not implemented." << endl;
    return 0;
}

// This is used to prompt user for ref_chan propeties and set them to the ref_chan
int define_Channel(Channel & ref_msg){
    char text[SIZE];

    // All of the setters for text values are the same idea
    // We get a cstring drom the user, then call the ref_chan's setter method to apply
    // I didn't actually come up wait a failure condition for the setter,
    // so I am not useing any return value for text setters.

        int set_name(const char text[]);
		int add_search_key(const char text[]);
		int set_description(const char text[]);
		int set_notes(const char text[]);
        int set_rating(int rating);

    cout <<"Enter channel name (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_chan.set_name(text);

    cout <<"Enter channel description (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_chan.set_description(text);

    cout <<"Enter channel notes (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_chan.set_notes(text);

    cout <<"Enter channel rating (integer 1 to 5):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_chan.set_rating(text);

    cout <<"Enter a channel search keyword (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_chan.add_search_key(text);
}

// Read from user which task they want to perform
int read_task_no()
{
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option
    char garbage[SIZE]; // In case they dont enter a number

    while (!(option >=1 & option <= 9))
    {
        // After first try, print failed Channel
        if (failed)
        {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat do you want?" << endl
            << "1: Add a new Channel to stack." << endl
            << "2: Duplicate top Channel of stack." << endl
            << "3: Move top stack to queue." << endl
            << "4: Display top of stack." << endl
            << "5: Display front of queue." << endl
            << "6: Delete top of stack." << endl
            << "7: Delete front of queue." << endl
            << "8: Run Autotest." << endl
            << "9: Exit." << endl
            << "\nEnter a number to enjoy an option." << endl
            << endl;
        if (!(cin >> option)){
            // I was annoyed with input errors, discovered clear() on a forum
            // http://www.cplusplus.com/forum/beginner/26821/
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        // cin.get(garbage, SIZE, '\n');
        cin.ignore(SIZE, '\n');
    }
    return option;
}