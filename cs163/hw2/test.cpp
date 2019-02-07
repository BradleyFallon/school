#include "header.h"


int main(){


    Message ref_msg;
    Message peek_msg;
    Stack msg_stack;
    char text[100] = "This is my test text. Isn't it nice?";
    int loops = 0; // For testing, this is a counter for limiting for while loop iterations

    ref_msg.set_body(text);
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

    cout << "Is empty?" << endl;
    cout << msg_stack.is_empty() << endl;

    loops = 0;
    while (!msg_stack.is_empty() && loops < 100){
        ++loops;
        cout << "Popping" << endl;
        msg_stack.pop(peek_msg);
    }

    cout << "Is empty?" << endl;
    cout << msg_stack.is_empty() << endl;
    
    return 0;
}