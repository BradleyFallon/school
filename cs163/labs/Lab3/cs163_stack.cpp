#include "cs163_stack.h"


//These are the functions you will be implementing
//for this lab, using a linear linked list of arrays
//as the data structure

//Add a new item to the top of stack
int stack::push(const journal_entry & to_add)
{
    node * temp;

    // If head is null, create the first node and array
    if (!head){
        head = new node;
        head->next = NULL;
        head->entries = new journal_entry[MAX];
        top_index = 0;
    }

    // If the index is maxed out, then you gotta make a new array
    else if (top_index==MAX){
        temp = new node;
        temp->next = head;
        head = temp;
        top_index = 0;
        head->entries = new journal_entry[MAX];
    }

    // Otherwise, just put data in current array
    head->entries[top_index].copy_entry(to_add);

    // always gotta increment
    ++top_index;
    
    return 1;
}


//Remove the top of stack
int stack::pop (void)
{
    node * temp;

    if (!head) return 0;

    if (!top_index){
        top_index = MAX;
        temp = head;
        head = temp->next;
        delete temp->entries;
        delete temp;
    }
    --top_index;

    return 1;
}

//Supply the journal at the top of stack back to the client
//Return 0 if there are no items
//top_index is one beyond where the top of stack is...
//with no items, top_index is zero
int stack::peek(journal_entry & found_at_top) const
{
            //Implement the function here
}

