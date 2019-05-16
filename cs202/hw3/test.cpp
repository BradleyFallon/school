
#include "header.h"

int main() {

    Character minion("Gronk", 5);
    MainCharacter danny("Danny", 20);
    DragonEgg mysterious_gift;
    // mysterious_gift = new Character();

    if (danny.adopt(mysterious_gift))
        cout << "Danny has acquired a mysterious gift." << endl;




    
    minion.display();
    danny.display();
    cout << (minion == danny) << endl;

    danny.update_commanding_power();
    minion.display();
    danny.display();
    cout << (minion == danny) << endl;


    minion = danny;
    minion.update_commanding_power();
    minion.display();
    danny.display();
    cout << (minion == danny) << endl;

    cout << (danny > 1) << endl;
    cout << (danny > 2) << endl;
    cout << (danny < 0) << endl;
    cout << (danny < 4) << endl;

    

    return 0;
}