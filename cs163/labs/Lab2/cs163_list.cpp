#include "cs163_list.h"
using namespace std;




//Implement these three functions
//Add to the end of the LLL as efficiently as possible
int list::add(journal_entry & to_add)
{
           //Implement this function using the
           //journal entry functions we just wrote!
    node * temp;
    node * current;
    temp = new node;
    temp->data.copy_entry(to_add);
    
    if (!head){
        head = temp; 
        tail = temp;
        return 1;
    }

    current = head;
    while (current->next){
        current = current->next;
    }
    
    current->next = temp;
    tail = temp;
    return 1;
}


//Display all journal entries
//Return false if there are no entries
int list::display(void)
{
         //Your code goes here!


}

//Determine if there is a match with the title passed in
//and if so provide the matching journal entry back to the
//client program through the second argument.
//Return a zero if no match is found
int list::find(char matching_title[], journal_entry & found)
{
	//Your code goes here!           

   return 0;
}


//Copy the list passed in as an argument
//and add the nodes to the end of the current list
int list::append(list & source)
{

        //Your code goes here!

}
