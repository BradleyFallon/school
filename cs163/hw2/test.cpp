#include "header.h"


int main(){


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