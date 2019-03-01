// ====================================================================
// Homework 3 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/31/2019
//
// Main header file. Used for all classes and ADT prototypes.
// ====================================================================

#include <iostream>
#include <fstream>
#include<cstring>
using namespace std;

const int SIZE_TEMP_CHARS = 256;

const char DATA_PATH[13] = "channels.txt";
const char FILE_HEADER[15] = "#CHANNELS-DUMP";
const char CHANNEL_HEADER[15] = "#CHANNEL";
const char CHANNEL_FOOTER[13] = "#CHANNEL-END";
const char DELIM = '\n';

// Make all characters of a char array lowered
int make_lower(char text[]);

struct node{
    Term term;
    node * left;
    node * right;;
};

class Term{
	public:
		Term(void);
		~Term(void);

		int clone(Term & ref_term); // Copy all properties from a reference

        int set_word(const char text[]);
		int set_description(const char text[]);
		int set_category(const char text[]);

        int get_word(char text[]);

        bool is_less(const char text[]);
        bool is_less(const Term & other);

		void display();

        
	private:
        char * word; // This is public so it can be read without copying
		char * description;
		char * category;
};

class BST{
    public:
        BST(void);
        ~BST(void);

        // Insert a copy of a referenced term object, sorted by name
        // Return 1 for success else 0
        int insert(Term & ref_term);
        // Remove all with matching name
        // Return number of objects removed
        int remove(const char word[]);
        // Retrieve all with matching name
        // Return number of objects found, whice are copied into "found" array
        int retrieve(const char word[], Term found[], int max_hits);
        // Get the height of the longest branch of the tree
        // Return the int height
        int get_height();
        bool is_efficient();
        void display_all();
        // Display all with names starting with characters within a given range
        int display_range(char min_val, char max_val);

    private:
        void _read_file();
        void _deallocate_all(node * & root);
        int _insert(node * & root, Term & ref_term);
        int _remove(node * & root, const char word[]);
        int _retrieve(node * & root, const char word[], Term found[], int max_hits);
        int _get_height(node * & root);
        void _display_all(node * & root);
        int _display_range(node * & root, char min_val, char max_val);

        node * root_bst;
};