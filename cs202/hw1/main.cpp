

#include "drone.h"

int main(){

    Race race;
    Contestant sanic_fast;
    int racer_id;

    Obstacle * obstacle_temp;


    cout << "Setting up race." << endl;

    sanic_fast.display();

    racer_id = race.enter_drone(sanic_fast);
    sanic_fast.attach_id(racer_id);



    return 0;
}