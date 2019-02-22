#include "cs162_list.h"


//Implement the following functions for Lab #8

//Insert a node at the beginning of a linear linked list
void list::insert(int to_add)
{
	//Step #5 - Write the code here
    if (!head) return;

    node * temp = head;

    head = new node;
    head -> data = to_add;
    head -> next = temp;

    return;
}

//Count the number of nodes in the LLL, returning the result
//Add a new node to the front of the list
//with the count as the data member
int list::count_and_insert()
{
     	//Step #6 - Write the code here
  
    int i = 0;

    node * current = head;

    while (current)
    {
        ++i;
        current = current -> next;
    }

   insert(i); 
   return i;
}

//Append a node to the end of a linear linked list
void list::append(int to_add)
{
        //Step #7 - Write the code here

    node * current = head;

    if (!head)
    {
        head = new node;
        head -> data = to_add;
        return;
    }

    while (current -> next)
    {
        current = current -> next;
    }

    current -> next = new node;
    (current -> next) -> data = to_add;

}


//Remove the last node from the list
void list::remove_last()
{
   	//Step #7 - Write the code here
    node * current = head;
    node * prev = head;

    cout << "remove" << endl;
    if (!head) return;

    if (!(head -> next))
    {
        delete head;
        head = NULL;
        return;
    }

    while (current -> next)
    {
        prev = current;
        current = current -> next;
    }
    prev -> next = NULL;
    delete current;
}

//Deallocate all nodes (Destructor)
list::~list()
{

    //Step #8 - Write the code here
    while (head)
    {
        remove_last();
    }
}

//Challenge - 
void list::copy_last()
{

    node * current = head;

    if (!head)
    {
        return;
    }

    while (current -> next)
    {
        current = current -> next;
    }
    
    insert(current -> data);
}      

