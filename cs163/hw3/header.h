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


// const int SIZE_TBLARY = 16; // Smaller and square (one prime factor: 2)
// const int SIZE_TBLARY = 17; // Smaller and prime
// const int SIZE_TBLARY = 18; // Smaller and even   (two prime factors: 2,3)
// const int SIZE_TBLARY = 64; // Larger and square  (one prime factor: 2)
// const int SIZE_TBLARY = 66; // Larger and even    (three prime factors: 2,3,11)
// const int SIZE_TBLARY = 72; // Larger and even    (two prime factors: 2,3)
const int SIZE_TBLARY = 79; // Larger and prime


struct CharsNode{
	CharsNode * next;
	char * txt;
};

class TextList{
    public:
		TextList(void);
		~TextList(void);

        int insert();

    private:
        CharsNode * head;
};

class Channel{
	public:
		Channel(void);
		~Channel(void);

		int clone(Channel &); // Makes this message copy a reference

        int set_name(const char text[]);
		int add_search_key(const char text[]);
		int set_description(const char text[]);
		int set_notes(const char text[]);
        int set_rating(int rating);

		void display();

	private:
        char * name;
		TextList search_keys_list;
        int num_keys;
		char * description;
		char * notes;
        int rating;
};

class HashTable{
    public:
        HashTable(void);
        ~HashTable(void);

        int copy_channel();
        int add_channel();
        int get_hash(const char text[]);
        int search_keyword();
        int display_matches();
        int display_all();
        int remove_by_name();

    private:
        Channel ** hash_array; // This is the array of the table, the top level
        
};