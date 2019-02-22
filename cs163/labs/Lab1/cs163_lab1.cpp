#include "cs163_list.h"
using namespace std;

int main()
{
    int total = 0;
    bool ret_bool = 0;
    
    //First try this out as is. Then start adding in your function calls!
    list my_list;
    
    total = my_list.sum_total();
    cout << "Total before build is " << total << endl;

    my_list.build();
    my_list.display_all();

    //PLACE YOUR FUNCTION CALL HERE!
    total = my_list.sum_total();
    cout << "Total is " << total << endl;
    
    my_list.display_all();
    
    ret_bool = my_list.remove_last();
    my_list.display_all();

    return 0;    
}
