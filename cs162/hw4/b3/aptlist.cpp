#include "hw4_header.h"

// Constructor sets head to null then reads file to build list
AptList::AptList(char save_as[])
{
    head = NULL;
    filename = new char[strlen(save_as)+1];
    strcpy(filename, save_as);
    _read_file();
}

// Insert a node sorted into the linear linked list, by cost asceneding.
void AptList::insort(AptNode* new_node_ptr)
{
    AptNode* current = head;  // Pointer used to traverse

    // If no items in list this item becomes head
    if (!head)
    {
        head = new_node_ptr;
        return;
    }
    // There is at least one item in list, determine where this one goes then insert
    while (current->next)
    {
        // If the rent of this is less than the rent of next, insert before next
        if (current->get_rent() < (current->next)->get_rent())
        {
            // Insert before next
            // New node needs to point to next
            new_node_ptr->next = current->next;
            // current node needs to point to new node
            current->next = new_node_ptr;
            return;
        }
    }
    // If we made it this far, then we add this node to the end of list
    current->next = new_node_ptr;
    return;
}
 // Create a new apartment and insert sorted by price into list
void AptList::add_new()
{
    AptNode* new_apt = new AptNode;
    new_apt->user_def();
    insort(new_apt);
}

// Append a node to the end of a linear linked list
// If the node provided can link to a node or null, either way, it is appended to end.
void AptList::append(AptNode* node_ptr)
{
    AptNode * current = head; // Pointer used to traverse

    // If the list is empty then new item becomes head
    if (!head)
    {
        head = node_ptr;
        return;
    }
    // If items are in the list already, then append new to end
    while (current -> next)
    {
        current = current -> next;
    }
    // Link last item to new node and link new node to null
    current->next = node_ptr;
    return;
}

// Remove the last node from the list
// If the index provided is greater than lelngth of list, then the last item of list will be removed.
// Deallocate memory of the removed node
void AptList::delete_at(int i_remove)
{
    int i_current = 0;
    AptNode* current = head;
    AptNode* prev = head;

    // We can't do much if head is null, so just quit
    if (!head) return;
    // If the remove index is 0, or if there is only one item in list, then remove head
    if (!(head -> next) | (i_remove==0))
    {
        delete head;
        head = NULL;
        return;
    }
    // If we have more than one item in list and non null remove index, then try to 
    // go to index and remove there
    while (current -> next && (i_current < i_remove))
    {
        // Move current to next and point prev to old current
        prev = current;
        current = current -> next;
        ++i_current;
    }
    // Make prev link to current's next, then delete current
    // If current was last item, then prev should inherit the null next from current (good)
    prev -> next = current -> next;
    delete current;
}

// Remove the last node from the list
// If the index provided is greater than length of list, then the last item of list will be removed.
// Do NOT deallocate memory, return pointer so node can be used externally
AptNode* AptList::pop_at(int i_remove)
{
    int i_current = 0;
    AptNode* current = head; // For traversing
    AptNode* prev; // For keeping track of previous in traversal

    // We can't do much if head is null, so just quit
    if (!head) return NULL;
    // If the remove index is 0, or if there is only one item in list, then remove head
    if (!(head -> next) | (i_remove==0))
    {
        current = head;
        head = NULL;
        return current; // Return pointer for external use
    }
    // If we have more than one item in list and non null remove index, then try to 
    // go to index and remove there
    while (current -> next && (i_current < i_remove))
    {
        // Move current to next and point prev to old current
        prev = current;
        current = current -> next;
        ++i_current;
    }
    // Make prev link to current's next, then delete current
    // If current was last item, then prev should inherit the null next from current (good)
    prev -> next = current -> next;
    return current; // Return pointer for external use
}

// Search aparments. Displays apts info with more than a certain sq ft size from user
void AptList::search_larger_apts()
{
    int min_size = 0;
    AptNode* current = head;

    cout << "What is the minumum size (sq-ft)(whole number)." << endl;
    cin >> min_size;
    cout << "\nHere's what we've got over " << min_size << " sq-ft:" << endl;

    while (current)
    {
        if (current->get_size() > min_size)
        {
            current->display_apt();
        }
        current = current->next;
    }
}

// Search aparments. Displays apts info with more than a certain sq ft size from user
void AptList::display_all()
{
    AptNode* current = head;
    int i = 0; // Index is used as id for user rejecting. Display above each apt.

    if (!head)
    {
        cout << "No apartments to display." << endl;
    }

    while (current)
    {
        cout << "\nID: " << i << endl;
        current->display_apt();
        current = current->next;
        ++i;
    }
}

// Write all apartments info to a file.
void AptList::_write_file()
{
    ofstream* outfile = new ofstream;
    AptNode* current = head;
    char apt_line[250];
    
    outfile->open(filename);

    if (*outfile)
    {
        *outfile << "Apartments:";
        while (current)
        {
            current->to_file(outfile);
            current = current -> next;
        }
        outfile->close();
        outfile->clear();
    }
    delete outfile;
}

void AptList::_read_file()
{
    char header_text[16];
    ifstream* in_file = new ifstream;
    AptNode* new_node;

    cout << "in read" << endl;
    cout << filename << endl;

    in_file->open(filename);
    // Check if file had anything to read, before parsing
    if (*in_file)
    {
        cout << "in file" << endl;
        // Prime the pump by reading header
        in_file->get(header_text, 15, '\n');
        in_file->ignore(10, '\n');
        cout << "got header" << endl;
        cout << header_text << endl;
        // Read the apartments
        cout << "eof: " << in_file->eof() << endl;
        while (*in_file && !(in_file->eof()))
        {
            cout << "in loop" << endl;
            new_node = new AptNode;
            new_node->from_file(in_file);
            in_file->ignore(100, '\n');
            cout << "got node" << endl;
            insort(new_node);
            cout << "insorted" << endl;
            cout << "eof: " << in_file->eof() << endl;
        }
        in_file->close();
        in_file->clear();
    }
    delete in_file;
}

//Deallocate all nodes (Destructor)
AptList::~AptList()
{
    _write_file();
    while (head)
    {
        delete_at(0);
    }
    delete filename;
}

