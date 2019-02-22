#include "cs163_entry.h"

using namespace std;

//Step #7: Implement this function
//This function takes the argument and copies it into
//the journal's data members
int journal_entry::copy_entry(const journal_entry & copy_from)
{

    // copy the vals from the input reference struct
    
    // If the title or notes are null, then return false
    if (!copy_from.title || !copy_from.notes)
        return 0;

    if (title) delete [] title;
    if (notes) delete [] notes;

    // Return true for success
    title = new char[strlen(copy_from.title)];
    strcpy(title, copy_from.title);

    notes = new char[strlen(copy_from.notes)];
    strcpy(notes, copy_from.notes);
    
    return 1;
}


//Step #8: Implement this function
//This function will return non-zero if the title sent
//in as an argument matches the data member. It supplies
//the matching journal back as an argument
int journal_entry::retrieve(char * matching_title, journal_entry & found)
{

    cout << title << endl;
    cout << matching_title << endl;
    cout << strcmp(title, matching_title);
    if (!strcmp(title, matching_title)){
        found.copy_entry(*this);
        return 1;
    }
    return 0;

}

