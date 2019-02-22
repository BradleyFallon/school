// ====================================================================
// Homework 4 for CS162
// Bradley Fallon
// bfallon@pdx.edu
// 11/25/2018
// ====================================================================

/*
 * Algorithm:
 * 
 * Main setup:
 * The program starts by creating two apartment lists. One list for apartments and one for rejected apartments.
 * The constructor takes a filename, and each of these lists reads past content from a file if it exists.
 * The program then moves on to the main loop for user interaction.
 *
 * Main loop:
 * The program then enters the main loop. The main loop runs until the user eventually indicates
 * that they want to quit. After the main loop quits, a file with all of the apartment info will
 * be saved. At the top of othe loop, we need to have the user select what operation they would
 * like to perform. The options for the user are:
 * 	1: Enter info for another apartment.
 * 	1: Reject an apartment from the apartment list, sending it to a reject list.
 * 	3: Search the apartment info LLL for one at least a minimum square footage.
 * 	4: Display all of the apartments info.
 * 	5: Quit and save apartment data to file.
 * Show these options to the user and prompt for a choice.
 * 
 * AptNode Constructor - Reads Char Array Into Apartment Struct:
 * If a char array was provided, read from file, then init the values by parsing the text. Otherwise,
 * Prompts the user for a value for each member. Creates new dynamic char arrays for text value members.
 * 
 * AptNode Destructor - 
 * Release memory for all of the text members. Release memory for this.
 * 
 * AptNode.display() - Dispays all member names and values of an apartment info struct:
 * For each member of the apartment info struct, output a description of the member and the value
 * of that member for the struct provided as function argument.
 * 
 * AptList Constructor -
 * Set the head pointer to Null. Open the filepath provided in write mode. If it has content,
 * then for each line, create a new node. Run the node constructor with the line as input. Insert each
 * node with the insert method.
 * 
 * AptList Destructor - 
 * Open a file in write mode, at the standard hardcoded path that this program uses.
 * For each node, write each member separated by 
 * our standard delimiter. Each apartment is separated by a line break. Close the file.
 * Iterate all of the nodes and run the node data's destructor method.
 * 
 * AptList.insert() - Inserts an apartment node in a location sorted by price
 * If no apartments in list, insrt over head. Iterate through the apartment list. At each existing apartment,
 * if the price of the next apartment is more than this apartment, insert this apartment here. Set the current item
 * next pointer to point at this item. Set this item to point to what was the old next item.
 * 
 * AptList.search() - Displays apartments abaove a given size.
 * Prompt the user for sq ft minimum to use when searching. Read in user response to an integer. Get
 * the first node from the LLL. Check if the square footage is more than the search value,
 * if it is, then display the apartment info with the aptNode display method. Do this for as many structs as we have defined, according
 * to the counter.
 * 
 * AptList.display() - Display all apartments.
 * Iterate through the list and call the display method of each node.
 *
 * Operation 1 - Eneter Apartment Info:
 * Call the AptNode constructor and then add this node to the apartments list LLL using the LLL sorted insert method.
 * 
 * Operation 2 - Reject Apartment:
 * Get an index from the user. For the main apartment list, iterate through as many nodes as the one less thab index from the user.
 * The next item is the node to remove. Change the current next to point to the remove node's next, then set the remove node's next
 * to null. Copy this pointer address and append it at the end of the reject list.
 * 
 * Operation 3 - Search:
 * Run AptList.search() of the main apartment list.
 * 
 * Operation 4 - Display All Apartments Info:
 * Run AptList.display() of the main apartment list.
 *
 * Operation 5 - Save and Quit:
 * Run the list constructor.
 * Set the flag that controls the main loop false, so that the main function completes and the program closes.
 *
 */


#include "hw4_header.h"


// Read from user which task they want to perform
int read_task_no();


int main()
{
    /*
    * Main setup:
    * The program starts by creating two apartment lists. One list for apartments and one for rejected apartments.
    * The constructor takes a filename, and each of these lists reads past content from a file if it exists.
    * The program then moves on to the main loop for user interaction.
    *
    * Main loop:
    * The program then enters the main loop. The main loop runs until the user eventually indicates
    * that they want to quit. After the main loop quits, a file with all of the apartment info will
    * be saved. At the top of othe loop, we need to have the user select what operation they would
    * like to perform. The options for the user are:
    * 	1: Enter info for another apartment.
    * 	2: Reject an apartment from the apartment list, sending it to a reject list.
    * 	3: Search the apartment info LLL for one at least a minimum square footage.
    * 	4: Display all of the apartments info.
    * 	5: Quit and save apartment data to file.
    * Show these options to the user and prompt for a choice.
    */

    // Declare the list of potential apartments
    // Needs filename
    char* filename_temp; // I couldn't give my const filename as arg (const char* not same as char*??)... so I am copying first
    filename_temp = new char[strlen(APTS_FNAME)+1];
    strcpy(filename_temp, APTS_FNAME);
    AptList apt_list(filename_temp); // This is the list of potential apartments
    delete filename_temp;

    // Declare the list of apartments that are rejected
    // Needs filename
    filename_temp = new char[strlen(REJECTS_FNAME)+1];
    strcpy(filename_temp, REJECTS_FNAME);
    AptList nope_list(filename_temp); // This is the list of apartments that are rejected
    delete filename_temp;

    bool interacting = true; // Flag to control if the user is still interacting with the program
    int task_no = 0; // Stores the user's option for which ask to operate
    int reject_id = 0; // ID of apartment used for if user wants to move an apartment to reject list
    AptNode* popped_node = NULL; // Used to move apartment between lists

    // This is the main interactive loop
    while (interacting)
    {
        task_no = read_task_no();
        // Option 1: Enter info for another apartment.
        if (task_no == 1)
        {
            apt_list.add_new();
        }
        // Option 2: Reject an apartment from the apartment list, sending it to a reject list.
        else if (task_no == 2)
        {
            cout << "Enter the ID of the apartment to reject:" << endl;
            cin >> reject_id;
            popped_node = apt_list.pop_at(reject_id);
            popped_node->next = NULL; // We just want one node, not the remainder of list
            nope_list.append(popped_node);
            // Null the transfer pointer now that we are done with it,
            // ...prevents possible funny business
            // ...I don't like funny business.
            popped_node = NULL;
        }
        // Option 3: Search the apartment info LLL for one at least a minimum square footage.
        else if (task_no == 3)
        {
            apt_list.search_larger_apts();
        }
        // Option 4: Display all of the apartments info.
        else if (task_no == 4)
        {
            // Display all of the apartments info.
            apt_list.display_all();
        }
        // Option 5: Quit and save apartment data to file.
        else if (task_no == 5)
        {
            // Save apartment data to file.
            // When the object goes out of scope, the destructor will run and save the file!
            // Quit
            interacting = false;
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

// Read from user which task they want to perform
int read_task_no()
{
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    while (!(option >=1 & option <= 5))
    {
        // After first try, print failed message
        if (failed)
        {
            cout << "Invalid response. Please try again." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nSup dude. What you wanna do man?" << '\n'
            << "1: Enter info for another apartment." << '\n'
            << "2: Reject an apartment." << '\n'
            << "3: Search and display apartments larger than a size." << '\n'
            << "4: Display all of the apartments info." << '\n'
            << "5: Quit and save apartment data to file." << '\n'
            << "\nEnter a number to choose an option.\n"
            << endl;
        cin >> option;
        cin.ignore(100, '\n');
    }
    return option;
}





