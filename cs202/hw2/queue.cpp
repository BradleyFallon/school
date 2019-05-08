/*
================================================================================
Homework 2 for CS202
Bradley Fallon
bfallon@pdx.edu
5/8/2019

This is the queue class. Stores new shippys at rear, and fetches shippys from front.
================================================================================
*/

#include "header.h"

Queue::Queue(void){
    rear = NULL;
}

Queue::~Queue(void){
    if (rear)
        delete_all(rear->next);
}

void Queue::delete_all(ShipperNode * current){
    if (current!=rear)
        delete_all(current->next);
    delete current->shippy;
    delete current;
}

Shipper * copy_shipper_rtti(Shipper * ref_shippy){
    // Copy the shipper info and add to rear of queue
    // Use RTTI via dynamic cast to use the correct copy constructor
    Shipper * copy_dest = NULL;
    GiftShipper * temp_gift_ptr = NULL;
    InstalledShipper * temp_install_ptr = NULL;
    SignedShipper * temp_sign_ptr = NULL;

    temp_gift_ptr = dynamic_cast<GiftShipper*>(ref_shippy);
    if (temp_gift_ptr){
        // This is an GiftShipper, downcasat and copy
        copy_dest = new GiftShipper(*temp_gift_ptr);
    } else {
        temp_install_ptr = dynamic_cast<InstalledShipper*>(ref_shippy);
        if (temp_install_ptr){
            // This is an InstalledShipper, downcasat and copy
            copy_dest = new InstalledShipper(*temp_install_ptr);
        } else {
            temp_sign_ptr = dynamic_cast<SignedShipper*>(ref_shippy);
            if (temp_sign_ptr){
                // This is a SignedShipper, downcasat and copy
                copy_dest = new SignedShipper(*temp_sign_ptr);
            } else {
            // This is a basic Shipper, no downcasting needed
            copy_dest = new Shipper(*ref_shippy);
            }
        }
    }
    return copy_dest;
}

void display_shipper_rtti(Shipper * ref_shippy){
    // Copy the shipper info and add to rear of queue
    // Use RTTI via dynamic cast to use the correct copy constructor
    GiftShipper * temp_gift_ptr = NULL;
    InstalledShipper * temp_install_ptr = NULL;
    SignedShipper * temp_sign_ptr = NULL;

    temp_gift_ptr = dynamic_cast<GiftShipper*>(ref_shippy);
    if (temp_gift_ptr){
        // This is an GiftShipper, downcasat and display
        temp_gift_ptr->display();
    } else {
        temp_install_ptr = dynamic_cast<InstalledShipper*>(ref_shippy);
        if (temp_install_ptr){
            // This is an InstalledShipper, downcasat and display
            temp_install_ptr->display();
        } else {
            temp_sign_ptr = dynamic_cast<SignedShipper*>(ref_shippy);
            if (temp_sign_ptr){
                // This is a SignedShipper, downcasat and display
                temp_sign_ptr->display();
            } else {
            // This is a basic Shipper, no downcasting needed
            ref_shippy->display();
            }
        }
    }
}


int Queue::enqueue(Shipper * ref_shippy){
    ShipperNode * node_ptr;

    node_ptr = new ShipperNode;
    node_ptr->shippy = copy_shipper_rtti(ref_shippy);
    node_ptr->next = NULL;

    if (!rear){
        rear = node_ptr;
        rear->next = rear;
    } else {
        // new rear will need to point to front
        node_ptr->next = rear->next;
        // Put temp after rear
        rear->next = node_ptr;
        // Make temp the new rear
        rear = node_ptr;
    }
    return 1;
}

Shipper * Queue::peek(){
    // Get a copy of the item at rear->next (front)
    if (!rear) return NULL;
    return copy_shipper_rtti(rear->next->shippy);
}

Shipper * Queue::dequeue(){
    // Remove the item at rear->next (front)
    ShipperNode * temp;
    Shipper * return_ptr = NULL;

    if (!rear) return return_ptr;

    if (rear->next == rear){
        return_ptr = copy_shipper_rtti(rear->shippy);
        delete rear->shippy;
        delete rear;
        rear = NULL;
        return return_ptr;
    }

    temp = rear->next;
    return_ptr = copy_shipper_rtti(temp->shippy);
    // rear->next now needs to point to what was rear->next->next
    rear->next = rear->next->next;
    // delete old front/temp
    delete temp->shippy;
    delete temp;
    return return_ptr;
}

bool Queue::is_empty(){
    // Check if the queue is empty - rear is NULL
    if (!rear) return true;
    return false;
}

void Queue::display_all(){
    if (!rear){
        cout << "Nothing to see here!" << endl;
    } else {
        // Start printing from front, recursively, untir rear reached
        cout << "\n================================================================" << endl;
        cout << "FRONT OF QUEUE" << endl;
        cout << "================================================================" << endl;
        display_all(rear->next);
    }
}

void Queue::display_all(ShipperNode * current){
    current->shippy->display();
    if (current==rear){
        cout << "================================================================" << endl;
        cout << "END OF QUEUE" << endl;
        cout << "================================================================\n" << endl;
        return;
        }
    display_all(current->next);
}
