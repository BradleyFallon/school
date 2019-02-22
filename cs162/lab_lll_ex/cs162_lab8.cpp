#include "cs162_list.h"


int main()
{
    list my_values;
    
    my_values.build();

    //PUT YOUR FUNCTION CALL HERE!
   
    my_values.insert(5);
    my_values.insert(5);
    my_values.insert(5);
    my_values.insert(5);
    

    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();
    my_values.remove_last();

    my_values.count_and_insert();

    my_values.append(9);
    my_values.append(9);

    my_values.append(9);
    my_values.append(11);
    my_values.copy_last();
    
    my_values.display_all();
     
    return 0;

}
