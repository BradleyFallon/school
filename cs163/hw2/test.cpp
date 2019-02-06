#include "header.h"


int main(){


    Message ref_msg;
    Message peek_msg;
    Stack msg_stack;
    char text[100] = "This is my test text. Isn't it nice?";

    ref_msg.set_body(text);
    ref_msg.set_author("Mr tester");

    ref_msg.display();

    msg_stack.push(ref_msg);

    msg_stack.peek(peek_msg);

    cout << "peek msg 1" << endl;
    peek_msg.display();



    ref_msg.set_body("This is message 2 body text");
    ref_msg.set_author("Mr tester");
    cout << "pushing msg 2" << endl;
    msg_stack.push(ref_msg);
    cout << "pushed msg 2" << endl;

    ref_msg.set_body("This is a duplicating message text");
    ref_msg.set_author("Mr tester");
    msg_stack.push(ref_msg);
    cout << "pushing msg 3" << endl;
    msg_stack.push(ref_msg);
    cout << "pushing msg 4" << endl;
    msg_stack.push(ref_msg);
    cout << "pushing msg 5" << endl;
    msg_stack.push(ref_msg);
    cout << "pushing msg 6" << endl;
    msg_stack.push(ref_msg);
    cout << "pushing msg 7" << endl;

    for (int i=0; i<10; ++i){
        msg_stack.pop(peek_msg);
        cout << "popped msg" << endl;
        peek_msg.display();
    }
    
    return 0;
}