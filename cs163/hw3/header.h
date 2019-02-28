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
// const int SIZE_TBLARY = 79; // Larger and prime
const int SIZE_TBLARY = 79;
const int SIZE_TEMP_CHARS = 256;

const char DATA_PATH[13] = "channels.txt";
const char FILE_HEADER[15] = "#CHANNELS-DUMP";
const char CHANNEL_HEADER[15] = "#CHANNEL";
const char CHANNEL_FOOTER[13] = "#CHANNEL-END";
const char DELIM = '\n';


struct CharsNode{
	CharsNode * next;
	char * txt;
};

class TextList{
    public:
		TextList(void);
		~TextList(void);

        int insert(const char text[]);
        int copy(TextList & other);
        int delete_all();
        int delete_all_rec(CharsNode * & current);
        CharsNode * get_head();

    private:
        CharsNode * head;

        int copy_rec(CharsNode * & head, CharsNode * & other_head);
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
        int set_rating(int value);
        int get_name(char text[]);
        CharsNode * get_head_search_key();

		void display();

	private:
        char * name;
		char * description;
		char * notes;
        int rating;
        TextList search_keys_list;
};

struct TableNode{
	TableNode * next;
	char * keyword;
    Channel * chan_ptr;
};

class HashTable{
    public:
        HashTable(void);
        HashTable(int array_size);
        ~HashTable(void);

        // This is the public add_channel method, which makes a copy of the channel and adds to table
        int enter_channel(Channel & ref_chan); 
        int get_hash(const char text[]);
        int search_keyword(const char text[], Channel found[], int max_hits);
        int display_matches(const char searched[]);
        int display_all();
        int remove_by_name(const char searched_name[]);
        int display_stats();

    private:

        int _insert_at_index(int index, const char text[], Channel * chan_ptr, TableNode ** & target_array);
        int _add_channel(Channel * ref_chan); // This is the private add_channel method, which does not make a copy of the channel
        int _delete_list(TableNode * & head);
        int _delete_channels(TableNode * & head);

        void _read_file();
        
        TableNode ** key_table_array; // This is the array of the table, the top level
        TableNode ** name_table_array; // This is the array of the table, the top level
        int size_table; // This is the size of the array
        
};
