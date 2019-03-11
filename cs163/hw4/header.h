// ====================================================================
// Homework 4 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/11/2019
//
// Main header file. Used for all classes and ADT prototypes.
// ====================================================================

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int SIZE_TEMP_CHARS = 256;

int make_lower(char text[]);

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

        char * word; // This is public so it can be read without copying
        
	private:
        
		char * description;
		char * category;
};

struct node{
    Term term;
    node * left;
    node * right;
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
        // Return number of objects found, which are copied into "found"
        int retrieve(const char word[], Term * found);
        // Get the height of the longest branch of the tree
        // Return the int height
        int get_height();
        int count_nodes();
        bool is_efficient();
        void display_all();
        // Display all with names starting with characters within a given range
        int display_range(char min_val, char max_val);

    private:
        void _read_file();
        void _deallocate_all(node * & root);
        int _insert(node * & root, Term & ref_term);
        int _remove(node * & root, const char word[]);
        int _retrieve(node * & root, const char word[], Term * found);
        int _get_height(node * & root);
        int _count_nodes(node * & root);
        void _display_all(node * root, int level);
        int _display_range(node * root, char min_val, char max_val);

        node * root_bst;
};