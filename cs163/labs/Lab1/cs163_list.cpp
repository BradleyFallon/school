#include "cs163_list.h"
using namespace std;

//Sum  all of the data together in a LLL
int list::sum_total()
{
 	//FIRST do this iteratively here. Then recursively
        //COMMENT out the iterative version when  rewriting
        //the solution recursively

        //To solve this recursively write another
        //function:   int sum_total(node * head);
        //and call it from this function
    /*
    int total = 0;
    node * current = head;

    while (current){
        total += current->data;
        current = current->next;
    }

    return total;
    */
    
    if (head){
        return sum_total(head);
    }
    return 0;
}


//Now implement the function recursively!
int list::sum_total(node * head)
{
    if (!head->next){
        return head->data;
    }
    return head->data + sum_total(head->next);
}

// *************************************************
//Remove the last node in a LLL. Return false if the
//list is empty and nothing is removed
bool list::remove_last()
{
        //Write your code here
 	//FIRST do this iteratively here. Then recursively
        //COMMENT out the iterative version when  rewriting
/*
    node * current = head;

    if (!current) return false;
    if (!current->next){
        delete tail;
        tail = NULL;
        head = NULL;
        return true;
    }
    while (current->next->next){
        current = current->next;
    } 
    delete tail;
    tail = current->next;
    tail->next = NULL;
    return true;
    */
}

//Now implement the function recursively!
bool list::remove_last(node * & head, node * & tail)
{
    if (!head->next){
       delete head;
       head = NULL;
       return true;
    }
    
    if (remove_last(head->next, tail)){
        tail = head;
    }
    return false;
            

}

// ************************************************
//Remove all nodes in a LLL. Remove false if there is
//nothing to remove
bool list::remove_all()
{
        //Remove all nodes in a LLL
 	//FIRST do this iteratively here. Then recursively
        //COMMENT out the iterative version when  rewriting

}

//Now implement the function recursively!
bool list::remove_all(node * & head)
{


}


// ************************************************
//Return true if the requested item (sent in as an argument)
//is in the list, otherwise return false
bool list::find_item(int item_to_find)
{
        //Write your code here

}

//Now implement the function recursively!
bool list::find_item(node * head, int item_to_find)
{


}


// ************************************************
//Make a complete copy of a LLL
bool list::copy(list & from)
{
        //Write your code here

}

//Now implement the function recursively
bool list::copy(node * & dest_head, node * & dest_tail, node * source)
{


}
