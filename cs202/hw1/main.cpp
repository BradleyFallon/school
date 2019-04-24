

#include "drone.h"

int main(){

    Race race;
    Contestant sanic_fast;
    Location obstacle_placement;
    int racer_id;

    obstacle_placement.set_xyz(0, 0, 0);
    obstacle_placement.set_name("Cool Obstacle");
    cout << "Placement: " << endl;
    obstacle_placement.display();

    BlackHole blk(obstacle_placement);
    blk.display();


    cout << "Setting up race." << endl;

    sanic_fast.display();

    racer_id = race.enter_drone(sanic_fast);
    sanic_fast.attach_id(racer_id);


    race.add_obstacle(obstacle_placement, 1);




    race.display_course();

    obstacle_placement.set_xyz(2, 10, 0);
    obstacle_placement.set_name("Cooler Obstacle");
    race.add_obstacle(obstacle_placement, 2);

    obstacle_placement.set_xyz(10, 12, 0);
    obstacle_placement.set_name("Coolest Obstacle");
    race.add_obstacle(obstacle_placement, 3);

    race.create_route(0, 1);
    race.create_route(1, 2);

    race.display_course();

    return 0;
}