#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// ====================================================================
// Homework 3 for CS162
// Bradley Fallon
// bfallon@pdx.edu
// 11/6/2018
// ====================================================================

/*
* Algorithm:
* 
* Main setup
* The program starts with creating an array of structs to hold the info of the apartments.
* Create an integer to track the number of apartments we havea info for, which defaults to zero.
*
* Main loop:
* The program then enters the main loop. The main loop runs until the user eventually indicates
* that they want to quit. After the main loop quits, a file with all of the apartment info will
* be saved. At the top of othe loop, we need to have the user select what operation they would
* like to perform. The options for the user are:
*     1: Read apartment data from a file.
*     2: Enter info for another apartment.
*     3: Search the apartment info array for one at least a minimum square footage.
*     4: Display all of the apartments info.
*     5: Quit and save apartment data to file.
* Show these options to the user and prompt for a choice.
* 
* Function Read Apartment - Reads Char Array Into Apartment Struct:
* To get an apartments data, read characters until we get to the
* delimiter ':'. The characters before the delimiter are read into the first member of the first
* first struct. Do the same process to read characters into all of the remaining members of the first
* empty struct. 
* 
* Function Display Apartment - Dispays all member names and values of an apartment info struct:
* For each member of the apartment info struct, output a description of the member and the value
* of that member for the struct provided as function argument.
* 
* Operation 1 - Read File:
* Attempt to open a file for reading with the standard hardcoded filename from the current directory.
* Check that the file was read successfully, and if not then inform user and then go back to top of
* main loop. If the file is opened and has data, then read info of each apartment in the file until
* we get to the end of file. Increment the count of apartments. Read for new line break, if it exists,
* and check for end of file. If not end of file, then repeat the process of defining a struct upon the 
* next struct in the array.
*
* Operation 2 - Eneter Apartment Info:
* Explain the format requiured for data input from the user. Prompt the user to enter info for one
* apartment in this format.
* 
* Operation 3 - Search:
* Prompt the user for sq ft minimum to use when searching. Read in user response to an integer. Get
* the first struct from the struct array. Check if the square footage is more than the search value,
* if it is, then display the apartment info. Do this for as many structs as we have defined, according
* to the counter.
* 
* Operation 4 - Display All Apartments Info:
* For each struct in the array, as many as our counter indicates we have defined, run the display
* apartment info struct function.
*
* Operation 5 - Save and Quit:
* Open a file in write mode, at the standard hardcoded path that this program uses.
* For each struct in the array, up to as many as our defined counter, write each member separated by 
* our standard delimiter. Each struct is separated by a line break. Close the file. Set the flag that
* controls the main loop false, so that the main function completes and the program closes.
*
*/

const int MED_LEN = 32; // Generic Medium length char array size
const int MAX_APTS = 10; // Max number of apartments stored
const char FNAME[17] = "./apartment.txt"; // The path where apartments info should be saved

// This is the data container for an apartment's description
struct AptInfo {
    char name[MED_LEN]; // Apt Complex Name
    int sq_ft; // Size of unit
    int beds; // Bedroom count, whole numbers
    float baths; // Bathroom count, fractionable
    int rent; // Rent monthly, nearest dollar
    bool pets; // True if pets allowed
    bool dish; // True if dishwasher machine included
    bool laundry; // True if washer/dryer included
};

// Read from user which task they want to perform
int read_task_no();
// Function Read Apartment - Reads Char Array Into Apartment Struct:
// To get an apartments data, read characters until we get to the
// delimiter ':'. The characters before the delimiter are read into the first member of the first
// first struct. Do the same process to read characters into all of the remaining members of the first
// empty struct.
void read_apt(AptInfo &, char text[]);
// Prompt and get apartment info from the input stream
bool prompt_bool();
// Reads in a file of apartments info into a given array, returns the count new of apts
int read_file(AptInfo apts_array[], int count);
// Write all apartments info to a file.
void write_file(AptInfo apts_array[], int count);
// Prompt and get apartment info from the input stream
void get_new_apt(AptInfo apts_array[], int count);
// Search aparments. Displays apts info with more than a certain sq ft size from user
void search_larger_apts(AptInfo apts_array[], int count);
// Display the info of an apartment
void display_apt(AptInfo &);


int main()
/* 
* Main loop:
* The program then enters the main loop. The main loop runs until the user eventually indicates
* that they want to quit. After the main loop quits, a file with all of the apartment info will
* be saved. At the top of othe loop, we need to have the user select what operation they would
* like to perform. The options for the user are:
*     1: Read apartment data from a file.
*     2: Enter info for another apartment.
*     3: Search the apartment info array for one at least a minimum square footage.
*     4: Display all of the apartments info.
*     5: Quit and save apartment data to file.
* Show these options to the user and prompt for a choice.
*/
{
    AptInfo my_apts[MAX_APTS]; // Data storage of the apartments info
    int apts_count = 0; // The number of apartments we have data for
    bool interacting = true; // Flag to control if the user is still interacting with the program
    int task_no = 0; // Stores the user's option for which ask to operate

    // This is the main interactive loop
    while (interacting)
    {
        task_no = read_task_no();
        // Option 1 (Requires room in array)
        if (task_no == 1 && apts_count < MAX_APTS)
        {
            // Read apartment data from file
            apts_count = read_file(my_apts, apts_count);
        }
        // Option 2 (Requires room in array)
        else if (task_no == 2 && apts_count < MAX_APTS)
        {
            // Enter info for another apartment
            get_new_apt(my_apts, apts_count);
            apts_count++;
        }
        // Option 3
        else if (task_no == 3)
        {
            // Search the apartment info array for one at least a minimum square footage.
            // Results will be displayed
            search_larger_apts(my_apts, apts_count);
        }
        // Option 4
        else if (task_no == 4)
        {
            // Display all of the apartments info.
            for (int i=0; i<apts_count; ++i)
            {
                cout << "\n\nApartment " << i+1 << ":\n" << endl;
                display_apt(my_apts[i]);
            }
        }
        // Option 5
        else if (task_no == 5)
        {
            // Save apartment data to file.
            write_file(my_apts, apts_count);
            // Quit
            interacting = false;
        }
        // Array Full
        else if (apts_count <= MAX_APTS)
        {
            // Inform user they cannot add more data
            cout << "The apartment data is fully populated. Cannot add any more info." << endl;
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
            << "1: Read apartment data from a file." << '\n'
            << "2: Enter info for another apartment." << '\n'
            << "3: Search the apartments for those above a minimum size." << '\n'
            << "4: Display all of the apartments info." << '\n'
            << "5: Quit and save apartment data to file." << '\n'
            << "\nEnter a number to choose an option.\n"
            << endl;
        cin >> option;
        cin.ignore(100, '\n');
    }
    return option;
}
// Reads in a file of apartments info into a given array, returns the count new of apts
int read_file(AptInfo apts_array[], int count)
{
    char header_text[16];
    ifstream in_file;

    in_file.open(FNAME);
    // Check if file had anything to read, before parsing
    if (in_file)
    {
        // Prime the pump by reading header
        in_file.get(header_text, 15, '\n');
        in_file.ignore(10, '\n');
        // Read the apartments
        while (in_file && !in_file.eof() && count < MAX_APTS)
        {
            in_file.get(apts_array[count].name, MED_LEN, ':'); // Apt Complex Name
            in_file.ignore(100, ':');
            in_file >> apts_array[count].sq_ft; // Size of unit
            in_file.ignore(100, ':');
            in_file >> apts_array[count].beds; // Bedroom count, whole numbers
            in_file.ignore(100, ':');
            in_file >> apts_array[count].baths; // Bathroom count, fractionable
            in_file.ignore(100, ':');
            in_file >> apts_array[count].rent; // Rent monthly, nearest dollar
            in_file.ignore(100, ':');
            in_file >> apts_array[count].pets; // True if pets allowed
            in_file.ignore(100, ':');
            in_file >> apts_array[count].dish; // True if dishwasher machine included
            in_file.ignore(100, ':');
            in_file >> apts_array[count].laundry; // True if washer/dryer included
            in_file.ignore(100, '\n');
            ++count;
        }
    } else {
        // File object was null when opened
        cout << "No data to read." << endl;
    }
    return count;
}
// Write all apartments info to a file.
void write_file(AptInfo apts_array[], int count)
{
    ofstream out;
    
    out.open(FNAME);

    if (out)
    {
        out << "Apartments:";
        for (int i=0; i<count; ++i)
        {
            out
                << endl
                << apts_array[i].name << ':' // Apt Complex Name
                << apts_array[i].sq_ft << ':'  // Size of unit
                << apts_array[i].beds << ':'  // Bedroom count, whole numbers
                << apts_array[i].baths << ':'  // Bathroom count, fractionable
                << apts_array[i].rent << ':'  // Rent monthly, nearest dollar
                << apts_array[i].pets << ':'  // True if pets allowed
                << apts_array[i].dish << ':'  // True if dishwasher machine included
                << apts_array[i].laundry // True if washer/dryer included
                ;
        }
        out.close();
        out.clear();
    }
}
// Prompt and get apartment info from the input stream
bool prompt_bool()
{
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
void get_new_apt(AptInfo apts_array[], int count)
{
    cout << "count: " << count << endl;
    cout << "Apt Name: " << apts_array[count].name << endl;
    cout << "Complex Name:" << endl;
    cin.get(apts_array[count].name, MED_LEN, '\n'); // Apt Complex Name
    cin.ignore(100, '\n');
    cout << "Size of Unit (sq ft)(Whole number.):" << endl;
    cin >> apts_array[count].sq_ft; // Size of unit
    cout << "Number of Bedrooms (Whole number.):" << endl;
    cin >> apts_array[count].beds; // Bedroom count, whole numbers
    cout << "Number of Bathrooms (Can be decimal):" << endl;
    cin >> apts_array[count].baths; // Bathroom count, fractionable
    cout << "Rent Cost (Nearest whole dollar.):" << endl;
    cin >> apts_array[count].rent; // Rent monthly, nearest dollar
    cout << "Are pets allowed?" << endl;
    apts_array[count].pets = prompt_bool(); // True if pets allowed
    cout << "Is a dishwasher included?" << endl;
    apts_array[count].dish = prompt_bool(); // True if dishwasher machine included
    cout << "Are washer/dryer included?" << endl;
    apts_array[count].laundry = prompt_bool(); // True if washer/dryer included
}
// Search aparments. Displays apts info with more than a certain sq ft size from user
void search_larger_apts(AptInfo apts_array[], int count)
{
    int min_size = 0;
    cout << "What is the minumum size (sq-ft)(whole number)." << endl;
    cin >> min_size;
    cout << "\nHere's what we've got over " << min_size << " sq-ft:" << endl;
    for (int i=0; i<count; i++)
    {
        if (apts_array[i].sq_ft > min_size)
        {
            cout << endl;
            display_apt(apts_array[i]);
        }
    }
}
// Return "Yes" or "No" in place of true of false
void bool_to_chars(bool val, char msg[])
{
    char yes[5] = "Yes.";
    char no[5] = "No.";
    if (val)
    {
        strcpy(msg, yes);
    } else { 
        strcpy(msg, no);
    }
}
// Display the info of an apartment
void display_apt(AptInfo & my_apt)
{
    char pets[5];
    char dish[5];
    char laundry[5];

    bool_to_chars(my_apt.pets, pets);
    bool_to_chars(my_apt.dish, dish);
    bool_to_chars(my_apt.laundry, laundry);
    cout 
        << "Complex Name:" << '\n'
        << '\t' << my_apt.name << '\n' // Apt Complex Name
        << "Size of Unit (sq ft):" << '\n'
        << '\t' << my_apt.sq_ft << '\n' // Size of unit
        << "Number of Bedrooms:" << '\n'
        << '\t' << my_apt.beds << '\n' // Bedroom count, whole numbers
        << "Number of Bathrooms:" << '\n'
        << '\t' << my_apt.baths << '\n' // Bathroom count, fractionable
        << "Rent Cost:" << '\n'
        << '\t' << my_apt.rent << '\n' // Rent monthly, nearest dollar
        << "Pets allowed:" << '\n'
        << '\t' << pets << '\n' // True if pets allowed
        << "Dishwasher included:" << '\n'
        << '\t' << dish << '\n' // True if dishwasher machine included
        << "Washer/dryer included:" << '\n'
        << '\t' << laundry // True if washer/dryer included
        << endl;
}