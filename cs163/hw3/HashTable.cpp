// ====================================================================
// Homework 3 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/31/2019
//
// Hash Table Class Definition File.
// ====================================================================

#include "header.h"


HashTable::HashTable(void){
    // Initialize the has table with null pointers
    hash_array = new TableNode*[SIZE_TBLARY];
    for (int i=0; i<SIZE_TBLARY; ++i)
        hash_array[i] = NULL;
};

HashTable::~HashTable(void){
};

int HashTable::insert_at_index(int index, const char text[], Channel * chan_ptr){
    TableNode * new_node;
    // Create the new node and copy text
    new_node = new TableNode;
    new_node->keyword = new char[strlen(text)+1];
    strcpy(new_node->keyword, text);
    new_node->chan_ptr = chan_ptr;
    // Insert at head, unsorted
    new_node->next = hash_array[index];
    hash_array[index] = new_node;
};

int HashTable::add_channel(Channel & ref_chan){
    int index; // index from hash where to insert a node
    char text[SIZE_TEMP_CHARS];
    CharsNode * current_key;

    
    ref_chan.get_name(text);
    index = get_hash(text) % SIZE_TBLARY;

    insert_at_index(index, text, & ref_chan);

    
    ref_chan.search_keys_list()


    return 1;
};

int HashTable::copy_channel(){
    return 1;
};

int HashTable::get_hash(const char text[]){
    int hash_val = 0;
    int text_len;

    text_len = strlen(text);
    // Do not attempt to hash if no text given. Hash will remain 0 if text_len==0
    // To get hash, sum each character's ascii value multiplied by position
    for (int i=0; i<text_len; ++i){
        hash_val = hash_val + (i+1)*text[i];
    }

    return hash_val;
};

int HashTable::search_keyword(){
    return 1;
};

int HashTable::display_matches(){
    return 1;
};

int HashTable::display_all(){
    return 1;
};

int HashTable::remove_by_name(){
    return 1;
};

/*
        const char OUTPUT_PATH[13] = "channels.txt";
        const char FILE_HEADER[15] = "#CHANNELS-DUMP";
        const char CHANNEL_HEADER[16] = "#CHANNEL-OBJECT";
        const char KEYS_START[12] = "#START-KEYS";
        const char KEYS_END[10] = "#END-KEYS";
        const char DELIM = '\n';
*/

// Read all channnels info from a file.
void HashTable::_read_file(){
    ifstream infile;
    Channel * new_channel;
    int int_num;
    char text[SIZE_TEMP_CHARS];
    
    infile.open(DATA_PATH);


    // Make sure this existed and was not empty before attempting to read
    if (infile)
    {
        // Read the file header to prep the .eof() functionality
        infile.get(text, SIZE_TEMP_CHARS, '\n');
        infile.ignore(SIZE_TEMP_CHARS,'\n');

        while (infile && !infile.eof())
        {
            // Read the current line of file, if it is not a header, continue
            infile.get(text, SIZE_TEMP_CHARS, '\n');
            infile.ignore(SIZE_TEMP_CHARS,'\n');


            // Check if this is a job header
            if (!strcmp(text, CHANNEL_HEADER)){
                // Make a new job read from file and append to current loca
                new_channel = new Channel;

                infile.get(text, SIZE_TEMP_CHARS, '\n');
                infile.ignore(SIZE_TEMP_CHARS,'\n');
                new_channel->set_name(text);

                infile.get(text, SIZE_TEMP_CHARS, '\n');
                infile.ignore(SIZE_TEMP_CHARS,'\n');
                new_channel->set_description(text);

                infile.get(text, SIZE_TEMP_CHARS, '\n');
                infile.ignore(SIZE_TEMP_CHARS,'\n');
                new_channel->set_notes(text);

                infile >> int_num;
                infile.ignore(SIZE_TEMP_CHARS,'\n');
                new_channel->set_rating(int_num);

                while (strcmp(text, CHANNEL_FOOTER)){
                    infile.get(text, SIZE_TEMP_CHARS, '\n');
                    infile.ignore(SIZE_TEMP_CHARS,'\n');
                    new_channel->add_search_key(text);
                }

            // Add the channel to the table per name and per each search key
            add_channel(new_channel);



            } // End read job

        }// end file work
        infile.close();
        infile.clear();
    }
}