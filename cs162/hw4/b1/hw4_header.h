#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char APTS_FNAME[17] = "./apartment.txt"; // The path where apartments info should be saved
const char REJECTS_FNAME[13] = "./reject.txt"; // The path where rejected apartments info should be saved

// Apartment node class with pointer for building a list
class AptNode
{
    public:
        AptNode();
        void display_apt(); // Displays the members and their values to user
        float get_rent(); // Returns the cost of the apartment
        int get_size(); // Returns the size of the apartment
        void to_file(ofstream* outfile); // Write apt info to open file
        void from_file(ifstream* infile); // Read apt info from open file
        AptNode* next; // Public so that list can do its thing without getter/setter
        ~AptNode();
    private:
        // The list class should not be directly handling this data, in my opinion
        char* name; // Apt Complex Name
        char* comment; // A comment from the user
        int sq_ft; // Size of unit
        int beds; // Bedroom count, whole numbers
        float baths; // Bathroom count, fractionable
        int rent; // Rent monthly, nearest dollar
        bool pets; // True if pets allowed
        bool dish; // True if dishwasher machine included
        bool laundry; // True if washer/dryer included
        bool _prompt_bool(); // Helper to get bool from user
        void _bool_to_chars(bool val, char msg[]); // Helper to display bool to user
};

// Apartment data is managed with a liner linked list, LLL
class AptList
{
    public:
        AptList(char save_as[]);
        void insort(AptNode* new_node_ptr); // Clever name huh ;) because it is a sorted insert, i.e. "insort".
        void add_new(); // Creates a new node and inserts it with the insort method
        void delete_at(int index); // Removes apartment from list at given index, and deletes it
        AptNode* pop_at(int index); // Removes apartment at index, does not delete, returns pointer
        void display_all(); // display all items
        void append(AptNode* node_ptr); // Appends a node to the end of list
        void search_larger_apts(); // Displays apartments larger than prompted arg size
        ~AptList();
    private:
        void AptList::_read_file();
        void AptList::_write_file();
        AptNode* head; //The head of a linear linked list
        char* filename; // The filename to read/write with
};
