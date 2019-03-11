// ====================================================================
// Homework 4 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/11/2019
//
// Interactive test client
// ====================================================================

#include "header.h"

const int SIZE = 256;

// Prototypes - See definitions below
int auto_test();
bool prompt_bool();
int read_task_no();
int define_term(Term & ref_term);

// Main loop of the test interface
int main()
{
    Term ref_term;
    int hit_count;
    BST my_bst;
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate
    char text[SIZE_TEMP_CHARS];
    char min_val;
    char max_val;

    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // 1: Add a new Term to the tree.
            if (define_term(ref_term)){
                if (my_bst.insert(ref_term)){
                    cout << "Term added successfully!" << endl;
                } else cout << "Term by this name already exists! Not added to tree." << endl;
                ref_term.display();
            } else cout << "Failed to create Term!" << endl;
        }
        else if (task_no == 2)
        {
            // 2: Search by keyword, display match.
            cout << "Option 2 selected!" << endl;
            cout << "Enter your search keyword:" << endl;
            cin.get(text, SIZE_TEMP_CHARS, '\n');
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            if (my_bst.retrieve(text, &ref_term)){
                cout << "YEEEEEESSSSSSS we found a match!!!!" << endl;
                ref_term.display();
            } else cout << "No matches found!" << endl;
            // my_bst.display_matches(text);
        }
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            // 3: Remove Term by name
            cout << "Enter the name of the Term to remove:" << endl;
            cin.get(text, SIZE_TEMP_CHARS, '\n');
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            if (my_bst.remove(text)){
                cout << "Term removed successfully!" << endl;
            } else cout << "No matches found!" << endl;
        }
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // 4: Display all.
            my_bst.display_all();
            cout << endl << "Tree Height: " << my_bst.get_height() << endl;
            cout << endl << "Node Count: " << my_bst.count_nodes() << endl;
            cout << endl << "Is efficient: " << my_bst.is_efficient() << endl;
        }
        else if (task_no == 5)
        {
            cout << "Option 5 selected!" << endl;
            // 5: Display range
            cout << "Enter a character to be the minimum starting letter:" << endl;
            cin >> min_val;
            cout << "Enter a character to be the maximum starting letter:" << endl;
            cin >> max_val;
            cout << "These are the terms with first letters between " << min_val << " and " << max_val << ": " << endl;
            my_bst.display_range(min_val, max_val);
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

bool prompt_bool(){
	// This repeatedly prompts the user for a yes or no response until valid input is provided.
	int i = 0;
	char response;
	while (i=0, i++, i<5)
	{
		// Prompt user for boolean response.
		cout << "Please respond with 'y' (yes) or 'n' (no)." << endl;
		cin >> response;
		cin.ignore(100, '\n');
		// Process input and return true or false if input was valid.
		if (response=='y')
		{
			return true;
		} else if (response=='n')
		{
			return false;
		} else
		{
			// Invalid response. Inform user and try again.
			cout << "Invalid response..." << endl;
		}
	}
	// Give up because user has exceeded tries limit. Assume the assignment was graded.
	cout << "This is taking too long. I'll answer for you... 'y'." << endl;
	return true;
}

// This is used to prompt user for ref_term propeties and set them to the ref_term
int define_term(Term & ref_term){
    char text[SIZE_TEMP_CHARS];

    // All of the setters for text values are the same idea
    // We get a cstring drom the user, then call the ref_term's setter method to apply
    // I didn't actually come up wait a failure condition for the setter,
    // so I am not using any return value for text setters.

    cout <<"Enter Term word (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_term.set_word(text);

    cout <<"Enter Term definition (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_term.set_description(text);

    cout <<"Enter Term related structure (text for cstring):" << endl;
    cin.get(text, SIZE_TEMP_CHARS, '\n');
    cin.ignore(SIZE_TEMP_CHARS,'\n');
    ref_term.set_category(text);

    return 1;
}

// Read from user which task they want to perform
int read_task_no(){
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option
    char garbage[SIZE]; // In case they dont enter a number

    while (!(option >=1 & option <= 9))
    {
        // After first try, print failed Term
        if (failed)
        {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat do you want?" << endl
            << "1: Add a new Term to the tree." << endl
            << "2: Search by keyword, display match." << endl
            << "3: Remove Term by name." << endl
            << "4: Display tree and info." << endl
            << "5: Display range." << endl
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
