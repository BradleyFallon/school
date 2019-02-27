// ====================================================================
// Homework 3 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 1/31/2019
//
// Hash Table Class Definition File.
// ====================================================================

#include "header.h"


HashTable::HashTable(){
    // Initialize the has table with null pointers
    HashTable(SIZE_TBLARY);
};

HashTable::HashTable(int array_size){
    size_table = array_size;
    // Initialize the has table with null pointers
    hash_array = new TableNode*[size_table];
    for (int i=0; i<size_table; ++i)
        hash_array[i] = NULL;
    _read_file();
};

HashTable::~HashTable(void){
};

int HashTable::_insert_at_index(int index, const char text[], Channel * chan_ptr){
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

int HashTable::_add_channel(Channel * ref_chan){
    int index; // index from hash where to insert a node
    char text[SIZE_TEMP_CHARS];
    CharsNode * current_key;

    
    ref_chan->get_name(text);
    index = get_hash(text) % size_table;

    _insert_at_index(index, text, ref_chan);

    current_key = ref_chan->get_head_search_key();
    while (current_key){
        index = get_hash(current_key->txt) % size_table;
        _insert_at_index(index, current_key->txt, ref_chan);
        current_key = current_key->next;
    }

    return 1;
};

int HashTable::copy_channel(Channel & ref_chan){
    Channel * new_channel;
    new_channel = new Channel;
    if (new_channel->clone(ref_chan)){
        if (_add_channel(new_channel)) return 1;
    }
    // If we either could not copy or add, then return 0
    return 0;
};

int HashTable::get_hash(const char text[]){
    int hash_val = 0;
    int text_len;

    text_len = strlen(text);
    // Do not attempt to hash if no text given. Hash will remain 0 if text_len==0
    // To get hash, sum each character's ascii value multiplied by position

    // Actually, I abandoned that. I iteratively modified this until I was happy with results,
    // There was not much of a plan
    for (int i=0; i<text_len; ++i){
        hash_val = hash_val + (i*(i+1)+i)*(text[i]-'B')*(text[i]-'D');
    }

    return hash_val;
};

int HashTable::search_keyword(const char searched[], Channel found[], int max_hits){
    int index;
    TableNode * current;
    int hit_count = 0;

    index = get_hash(searched) % size_table;
    current = hash_array[index];

    while (current && hit_count < max_hits){
        if (!strcmp(current->keyword, searched)){
            current->chan_ptr->display();
            found[hit_count].clone(*current->chan_ptr);
            ++hit_count;
        }
        current = current->next;
    }

    return hit_count;
};


// This could have used the search_keyword, but that would have more overhead,
// because we would need to do the whole create an array and clone matches thing.
// This is more efficient, since it just displays the hit and then moves on.
int HashTable::display_matches(const char searched[]){
    int index;
    TableNode * current;
    int any_hits = false;

    index = get_hash(searched) % size_table;
    current = hash_array[index];

    while (current){
        if (!strcmp(current->keyword, searched)){
            current->chan_ptr->display();
            any_hits = true;
        }
        current = current->next;
    }

    if (!any_hits){
        cout << "No results found!" << endl;
        return 0;
    }
    return 1;
};

int HashTable::display_all(){
    TableNode * current;

    cout << "This is your table:" << endl;
    for (int i=0; i<size_table; ++i){
        cout << "In column " << i << endl;
        current = hash_array[i];
        while (current){
            current->chan_ptr->display();
            current = current->next;
        }
    }
    return 1;
};


int HashTable::remove_by_name(const char searched_name[]){
    bool channel_found = false;
    int index;
    char current_name[SIZE_TEMP_CHARS];
    TableNode * current;
    TableNode * prev;
    Channel * the_channel;
    CharsNode * current_key;

    index = get_hash(searched_name) % size_table;
    current = hash_array[index];

    while (current && !channel_found){
        if (!strcmp(current->keyword, searched_name)){
            current->chan_ptr->get_name(current_name);
            if (!strcmp(current->keyword, current_name)){
                channel_found = true;
            }
        }
        if (!channel_found){
            prev = current;
            current = current->next;
        }
    }
    if (channel_found){
        prev->next = current->next;
        the_channel = current->chan_ptr; // Delete after iterating keywords
        delete current->keyword;
        delete current;


        current_key = the_channel->get_head_search_key();
        while (current_key){
            index = get_hash(current_key->txt) % size_table;
            current = hash_array[index];
            prev = NULL;
            while(current){
                if (!strcmp(current->keyword, searched_name)){
                    current->chan_ptr->get_name(current_name);
                    if (!strcmp(current->keyword, current_name)){
                        if (prev){
                            prev->next = current->next;
                        } else hash_array[index] = current;
                        delete current->keyword;
                        delete current;    
                    }
                }
                prev = current;
                current = current->next;
            }
            current_key = current_key->next;
        }
        delete the_channel;
        return 1;
    }
    // No channel found
    return 0;
};

int HashTable::display_stats(){
    TableNode * current;
    int col_count = 0;

    cout << "This is your table:" << endl;

    for (int i=0; i<size_table; ++i){
        col_count = 0;
        current = hash_array[i];
        while (current){
            ++col_count;
            current = current->next;
        }
        cout << "Items in column " << i << ": " << col_count << endl;
    }
}

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
                _add_channel(new_channel);

            } // End read channel

        }// end file work
        infile.close();
        infile.clear();
    }
}