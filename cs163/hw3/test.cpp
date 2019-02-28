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
    const int SIZE_SEARCH = 100;
    Channel search_array[SIZE_SEARCH];
    int hit_count;
    HashTable my_table;
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate
    char text[SIZE_TEMP_CHARS];

    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // 1: Add a new Channel to stack.
            if (define_channel(ref_chan)){
                if (my_table.enter_channel(ref_chan)){
                    cout << "Channel added successfully!" << endl;
                } else cout << "Channel by this name already exists! Not added to table." << endl;
                ref_chan.display();
            } else cout << "Failed to create channel!" << endl;
        }
        else if (task_no == 2)
        {
            // 2: Search by keyword, display all matches
            cout << "Option 2 selected!" << endl;
            cout << "Enter your search keyword:" << endl;
            cin.get(text, SIZE_TEMP_CHARS, '\n');
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            hit_count = my_table.search_keyword(text, search_array, SIZE_SEARCH);
            if (hit_count){
                for (int i=0; i<hit_count; ++i){
                    search_array[i].display();
                }
                cout << "Found a total of " << hit_count << " matches!" << endl;
            } else cout << "No matches found!" << endl;
            // my_table.display_matches(text);
        }
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            // 3: Remove channel by name
            cout << "Enter the name of the channel to remove:" << endl;
            cin.get(text, SIZE_TEMP_CHARS, '\n');
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            if (my_table.remove_by_name(text)){
                cout << "Channel removed successfully!" << endl;
            } else cout << "No matches found!" << endl;
        }
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // 4: Display all.
            my_table.display_all();
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
    int table_size;

    cout << "How long should the table array be. Enter an integer:" << endl;
    if (!(cin >> table_size)){
        // I was annoyed with input errors, discovered clear() on a forum
        // http://www.cplusplus.com/forum/beginner/26821/
        cin.clear();
        cin.ignore();
        table_size = 0;
    }
    cin.ignore(SIZE_TEMP_CHARS, '\n');

    HashTable my_table(table_size);
    my_table.display_stats();

    return 0;
}

// This is used to prompt user for ref_chan propeties and set them to the ref_chan
int define_channel(Channel & ref_chan){
    char text[SIZE_TEMP_CHARS];
    int int_get = 0;

    // All of the setters for text values are the same idea
    // We get a cstring drom the user, then call the ref_chan's setter method to apply
    // I didn't actually come up wait a failure condition for the setter,
    // so I am not using any return value for text setters.

    cout <<"Enter channel name (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_chan.set_name(text);

    cout <<"Enter channel description (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_chan.set_description(text);

    cout <<"Enter channel notes (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_chan.set_notes(text);

    cout <<"Enter channel rating (integer 1 to 5):" << endl;
    while (!(cin >> int_get)){
        // As long as the user doesn't enter a number, clear and retry
        // I was annoyed with input errors, discovered clear() on a forum
        // http://www.cplusplus.com/forum/beginner/26821/
        cin.clear();
        cin.ignore(SIZE_TEMP_CHARS,'\n');
        int_get = 0;
        cout <<"Enter channel rating (integer 1 to 5):" << endl;
    }
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_chan.set_rating(int_get);

    cout <<"Enter a channel search keyword (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_chan.add_search_key(text);

    return 1;
}

// Read from user which task they want to perform
int read_task_no(){
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
            << "2: Search by keyword, display all matches" << endl
            << "3: Remove channel by name" << endl
            << "4: Display all." << endl
            << "5: Experiment with array length." << endl
            << "6: Exit." << endl
            << "\nEnter a number to enjoy an option." << endl
            << endl;
        if (!(cin >> option)){
            // I was annoyed with input errors, discovered clear() on a forum
            // http://www.cplusplus.com/forum/beginner/26821/
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        // cin.get(garbage, SIZE_TEMP_CHARS, '\n');
        cin.ignore(SIZE_TEMP_CHARS, '\n');
    }
    return option;
}
