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
    
    return 0;
}