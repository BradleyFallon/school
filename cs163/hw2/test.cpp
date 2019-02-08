#include "header.h"

const int SIZE = 256;

// Prototypes - See definitions below
int read_task_no();
int define_message(Message & ref_msg);

// Main loop of the test interface
int main()
{
    Message ref_msg;
    Stack msg_stack;
    Queue msg_queue;
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate

    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // 1: Add a new message to stack.
            define_message(ref_msg);
            if (msg_stack.push(ref_msg)){
                cout << "Message added!" << endl;
            } else cout << "Push failed!" << endl;
        }
        else if (task_no == 2)
        {
            cout << "Option 2 selected!" << endl;
            // 2: Duplicate top message of stack.
            if (msg_stack.peek(ref_msg)){
                if (msg_stack.push(ref_msg)){
                    cout << "Message duplicated!" << endl;
                } else cout << "Push failed!" << endl;
            } else cout << "Nothing to duplicate!" << endl;
        }
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            // 3: Move top stack to queue.
            if (msg_stack.pop(ref_msg)){
                if (msg_queue.enqueue(ref_msg)){
                    cout << "Message moved to queue!" << endl;
                } else cout << "Enqueue failed!" << endl;
            } else cout << "Nothing to pop!" << endl;
        }
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // 4: Display top of stack.
            if (msg_stack.peek(ref_msg)){
                ref_msg.display();
            } else cout << "Nothing to display!" << endl;
        }
        else if (task_no == 5)
        {
            cout << "Option 5 selected!" << endl;
            // 5: Display front of queue.
        }
        else if (task_no == 6)
        {
            cout << "Option 6 selected!" << endl;
            // 6: Delete top of stack.
        }
        else if (task_no == 7)
        {
            cout << "Option 7 selected!" << endl;
            // 7: Delete front of queue.
        }
        else if (task_no == 8)
        {
            cout << "Option 8 selected!" << endl;
            // 8: Run Autotest.
        }
        else if (task_no == 9)
        {
            cout << "Option 9 selected!" << endl;
            // 9: Exit.
            do_run = false;
        }
        // Invalid option
        else
        {
            // Invalid response
            cout << "That was not a valid option, please try again." << endl;
        }
    }
    return 0;
}

int auto_test(){
    Message ref_msg;
    Message peek_msg;
    Stack msg_stack;
    Queue msg_queue;
    // char text[100] = "This is the first message. This is my test text. Isn't it nice?";
    int loops = 0; // For testing, this is a counter for limiting for while loop iterations

    ref_msg.set_body("This is the first message. This is my test text. Isn't it nice?");
    ref_msg.set_author("Mr tester");
    ref_msg.display();

    cout << "Pushing the first message" << endl;
    msg_stack.push(ref_msg);

    cout << "peek msg 1" << endl;
    msg_stack.peek(peek_msg);
    peek_msg.display();

    ref_msg.set_body("This is a duplicating message text");
    ref_msg.set_author("Mr super tester");

    for (int i=2; i<13; ++i){
        cout << "pushing msg " << i << endl;
         msg_stack.push(ref_msg);
    }

    cout << "Is stack empty?" << endl;
    cout << msg_stack.is_empty() << endl;

    cout << "Is queue empty?" << endl;
    cout << msg_queue.is_empty() << endl;

    cout << "Moving all items from stack to queue" << endl;


    loops = 0;
    // Move all messages from the stack to the queue
    while (!msg_stack.is_empty() && loops < 100){
        ++loops;
        cout << "Popping" << endl;
        msg_stack.pop(peek_msg);
        cout << "Enqueuing" << endl;
        msg_queue.enqueue(peek_msg);
    }

    cout << "Is stack empty?" << endl;
    cout << msg_stack.is_empty() << endl;

    cout << "Is queue empty?" << endl;
    cout << msg_queue.is_empty() << endl;

    cout << "This is the front item of the queue: " << endl;
    msg_queue.peek(peek_msg);
    peek_msg.display();

    while (!msg_queue.is_empty() && loops < 100){
        ++loops;
        cout << "Dequeuing" << endl;
        msg_queue.dequeue(peek_msg);
    }

    cout << "Is queue empty?" << endl;
    cout << msg_queue.is_empty() << endl;

    cout << "This was the last item from the queue: " << endl;
    peek_msg.display();
    
    return 0;
}

// This is used to prompt user for ref_msg propeties and set them to the ref_msg
int define_message(Message & ref_msg){
    char text[SIZE];

    // All of the setters for text values are the same idea
    // We get a cstring drom the user, then call the ref_msg's setter method to apply
    // I didn't actually come up wait a failure condition for the setter,
    // so I am not useing any return value for text setters.
    cout <<"Enter Author (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_msg.set_author(text);

    cout <<"Enter Subject (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_msg.set_subject(text);

    cout <<"Enter Date (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_msg.set_date(text);

    cout <<"Enter Message Body (text for cstring):" << endl;
    cin.get(text, SIZE, '\n');
    cin.ignore(SIZE,'\n');
    ref_msg.set_body(text);
}

// Read from user which task they want to perform
int read_task_no()
{
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    while (!(option >=1 & option <= 6))
    {
        // After first try, print failed message
        if (failed)
        {
            cout << "Invalid response. Please try again." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat you wanna do?" << endl
            << "1: Add a new message to stack." << endl
            << "2: Duplicate top message of stack." << endl
            << "3: Move top stack to queue." << endl
            << "4: Display top of stack." << endl
            << "5: Display front of queue." << endl
            << "6: Delete top of stack." << endl
            << "7: Delete front of queue." << endl
            << "8: Run Autotest." << endl
            << "9: Exit." << endl
            << "\nEnter a number to enjoy an option." << endl
            << endl;
        cin >> option;
        cin.ignore(SIZE, '\n');
    }
    return option;
}