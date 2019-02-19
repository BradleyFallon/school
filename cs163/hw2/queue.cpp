//====================================================================
// Homework 2 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 2/8/2019
// ====================================================================

// This is the queue class. Stores new messages at rear, and fetches messages from front.

#include "header.h"

Queue::Queue(void){
    rear = NULL;
}

Queue::~Queue(void){

}


int Queue::enqueue(Message & ref_message){
    // set this item to be the new item at rear
    MsgNode * temp;

    // Make a new message node and copy the ref
    temp = new MsgNode;
    if (!temp->msg.clone(ref_message)){
        delete temp;
        return 0;
    }

    if (!rear){
        rear = temp;
        rear->next = rear;
    } else {
        // new rear will need to point to front
        temp->next = rear->next;
        // Put temp after rear
        rear->next = temp;
        // Make temp the new rear
        rear = temp;
    }
    return 1;
}

int Queue::peek(Message & ref_message){
    // Get a copy of the item at rear->next (front)
    if (!rear) return 0;
    ref_message.clone(rear->next->msg);
    return 1;
}

int Queue::dequeue(Message & ref_message){
    // Remove the item at rear->next (front)
    MsgNode * temp;

    if (!rear) return 0;

    if (rear->next == rear){
        ref_message.clone(rear->msg);
        delete rear;
        rear = NULL;
        return 1;
    }

    temp = rear->next;
    ref_message.clone(temp->msg);
    // rear->next now needs to point to what was rear->next->next
    rear->next = rear->next->next;
    // delete old front/temp
    delete temp;
    return 1;
}

bool Queue::is_empty(){
    // Check if the queue is empty - rear is NULL
    if (!rear) return true;
    return false;
}
