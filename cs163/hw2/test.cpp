#include "header.h"


int main(){


    Message ref_msg;
    char text[100] = "This is my test text. Isn't it nice?";

    ref_msg.set_body(text);
    ref_msg.set_author("Mr tester");

    ref_msg.display();
    
    
    return 0;
}