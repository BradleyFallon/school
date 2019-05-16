
#include "header.h"

int main() {

    Character minion("Gronk", 5);
    MainCharacter hero("Danny", 20);
    
    minion.display();
    hero.display();
    cout << (minion == hero) << endl;

    hero.update_commanding_power();
    minion.display();
    hero.display();
    cout << (minion == hero) << endl;


    minion = hero;
    minion.update_commanding_power();
    minion.display();
    hero.display();
    cout << (minion == hero) << endl;

    cout << (hero > 1) << endl;
    cout << (hero > 2) << endl;
    cout << (hero < 0) << endl;
    cout << (hero < 4) << endl;

    


    return 0;
}