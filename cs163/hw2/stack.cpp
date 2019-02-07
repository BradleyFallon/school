#include "header.h"

/*
This class is a stack of message objects. The messages are stored
in dynamically allocated arrays. The arrays are stored in a linear linked list.
The index "top" is the index where the next item should be placed.
The top existing item of the stack is in head's array at index top-1.
*/

Stack::Stack(void){
    top = 0;
    head = NULL;
}


Stack::~Stack(void){

}


int Stack::push(Message & ref_message){
    Message new_message;
    StackNode * new_stack_node;

    // Do a test clone to fail before allocating array
    if (!new_message.clone(ref_message)){
        // Failed to clone the ref_message
        return 0;
    }
    // If the LLL is empty, create the first node and the node's array
    if (!head){
        head = new StackNode;
        head->messages = new Message[SIZE_STACK_ARRAY];
        head->next = NULL;
    } 
    // If the head node is full, create a new head node and the node's array
    else if (top == SIZE_STACK_ARRAY){
        new_stack_node = new StackNode;
        new_stack_node->next = head;
        head = new_stack_node;
        head->messages = new Message[SIZE_STACK_ARRAY];
        top = 0;
    }

    // The temp new message was just for error testing.
    // Clone this into the top of the stack.
    head->messages[top].clone(new_message);
    ++top;
}


int Stack::peek(Message & ref_message){
    if (!head) return 0;

    // top points to where the next message should go,
    // the most recent message is at top-1
    if(!ref_message.clone(head->messages[top-1])) return 0;

    return 1;
}


int Stack::pop(Message & ref_message){
    StackNode * old_head;

    // This stack gives a reference of what was popped
    if(!peek(ref_message)){
        // Use peek to get a ref of the top message
        return 0;
    }

    // If the top array is no longer needed, then deallocate and
    // move head to next node.
    if (top==1){
        top = SIZE_STACK_ARRAY;
        old_head = head;
        head = old_head->next;
        delete [] old_head->messages;
        delete old_head;
    } else {
        --top;
    }
    
    return 1;
}


bool Stack::is_empty(){
    if (!head) return true;
    return false;
}
