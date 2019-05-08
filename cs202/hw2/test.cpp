/*
================================================================================
Homework 2 for CS202
Bradley Fallon
bfallon@pdx.edu
5/8/2019

This is the test client. It is interactive, but it also calls an autotest that
will detect any basic errors.
================================================================================
*/

#include "header.h"

const int SIZE = 100;

// Prototypes - See definitions below
void autotest();
int read_task_no();
Shipper * define_shippy();


// Main loop of the test interface
int main()
{
    Shipper * shippy_ptr = NULL;
    Queue shippy_queue;
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate

    autotest();

    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // 1: Add a new package to the delivery queue
            shippy_ptr = define_shippy();
            if (shippy_ptr) shippy_queue.enqueue(shippy_ptr);
            else cout << "Something went wrong, not added to queue." << endl;
        }
        else if (task_no == 2)
        {
            cout << "Option 2 selected!" << endl;
            // 2: Display the package at the front of delivery queue.
            shippy_ptr = shippy_queue.peek();
            if (!shippy_ptr) cout << "Nothing in queue!" << endl;
        }
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            // 3: Deliver package at front of delivery queue.
            shippy_ptr = shippy_queue.dequeue();
            if (!shippy_ptr) cout << "Nothing in queue!" << endl;
        }
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // 4: Display entire delivery queue.
            shippy_queue.display_all();        }
        else if (task_no == 5)
        {
            cout << "Option 6 selected!" << endl;
            // 6: Exit.
            cout << "Goodbye!" << endl;
            do_run = false;
        }
        // Invalid option
        else
        {
            // Invalid response
            cout << "That was not a valid option, please try again." << endl;
        }
        if (shippy_ptr){
            cout << "This is the item that was just acted upon:" << endl;
            display_shipper_rtti(shippy_ptr);
            delete shippy_ptr;
            shippy_ptr = NULL;
        }
    }
    return 0;
}


void autotest(){
    Shipper * queue_peek_ptr = NULL;

    Shipper * shippy_ptr;
    SignedShipper * signed_ptr;
    InstalledShipper * installed_ptr;
    GiftShipper * gift_ptr;


    shippy_ptr = new Shipper();
    shippy_ptr->set_contact_from("Mr. Recieve - 42 Highland Drive");
    shippy_ptr->set_contact_to("Mrs. Send - Across the Universe");
    shippy_ptr->set_contents("This is a cool toy car.");

    // shippy_ptr->display();

    signed_ptr = new SignedShipper(*shippy_ptr);
    signed_ptr->set_contents("This is an expensive ring.");
    // signed_ptr->display();

    installed_ptr = new InstalledShipper(*signed_ptr);
    installed_ptr->set_contents("This is a hottub to be installed.");
    // signed_ptr->display();

    gift_ptr = new GiftShipper(*shippy_ptr);
    gift_ptr->set_contents("This is a warm pair of socks.");
    // gift_ptr->display();

    Queue shippy_queue;

    shippy_queue.enqueue(shippy_ptr);
    delete shippy_ptr;
    shippy_queue.enqueue(signed_ptr);
    delete signed_ptr;
    shippy_queue.enqueue(installed_ptr);
    delete installed_ptr;
    shippy_queue.enqueue(gift_ptr);
    delete gift_ptr;
    shippy_queue.display_all();

    cout << "\nPeeking at front for first time:\n" << endl;
    queue_peek_ptr = shippy_queue.peek();
    if (queue_peek_ptr){
        display_shipper_rtti(queue_peek_ptr);
        delete queue_peek_ptr;
        queue_peek_ptr = NULL;
    }

    cout << "\nPeeking at front for second time:\n" << endl;
    queue_peek_ptr = shippy_queue.peek();
    if (queue_peek_ptr){
        display_shipper_rtti(queue_peek_ptr);
        delete queue_peek_ptr;
        queue_peek_ptr = NULL;
    }

    cout << "\nGoing to dequeue and dislay until the queue is empty:\n" << endl;
    while (!shippy_queue.is_empty()){
        queue_peek_ptr = shippy_queue.dequeue();
        if (queue_peek_ptr){
            display_shipper_rtti(queue_peek_ptr);
            delete queue_peek_ptr;
            queue_peek_ptr = NULL;
        }      
    }
}

Shipper * define_shippy(){
    Shipper * return_ptr = NULL;
    char text[SIZE];
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    while (!(option >=1 && option <= 4))
    {
        // After first try, print failed Term
        if (failed)
        {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "What type of shipment is this?\n"
            << "[1] Stnadard" << "\n"
            << "[2] Signed" << "\n"
            << "[3] Installed" << "\n"
            << "[4] Gift" << endl;
        if (!(cin >> option)){
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        cin.ignore(SIZE, '\n');
    }

    if (option==1){
        return_ptr = new Shipper;
    } else if (option==2){
        return_ptr = new SignedShipper;
    } else if (option==3){
        return_ptr = new InstalledShipper;
    } else if (option==4){
        return_ptr = new GiftShipper;
    } else return return_ptr; // This line should be inaccessable

    cout <<"Enter Shipment sender info (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    return_ptr->set_contact_from(text);

    cout <<"Enter Shipment destination info (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    return_ptr->set_contact_to(text);

    cout <<"Enter shipment contents description (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    return_ptr->set_contents(text);

    return return_ptr;
}

// Read from user which task they want to perform
int read_task_no(){
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    while (!(option >=1 && option <= 9))
    {
        // After first try, print failed Term
        if (failed)
        {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat do you want?" << endl
            << "1: Add a new package to the delivery queue." << endl
            << "2: Display the package at the front of delivery queue." << endl
            << "3: Deliver package at front of delivery queue." << endl
            << "4: Display entire delivery queue." << endl
            << "5: Exit." << endl
            << "\nEnter a number to enjoy an option." << endl
            << endl;
        if (!(cin >> option)){
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        cin.ignore(SIZE, '\n');
    }
    return option;
}