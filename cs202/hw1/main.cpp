/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This is a test client used to verify that the classes work.
================================================================================
*/

#include "drone.h"

int main(){

    Race race;
    Contestant sanic_fast("Sanic Fast");
    Contestant other_guy("Dr. Roflcopter");
    Location obstacle_placement;
    int racer_id;


    cout << "Adding Obstacle" << endl;
    obstacle_placement.set_xyz(1, 2, 3);
    obstacle_placement.set_name("Cool Obstacle");
    race.add_obstacle(obstacle_placement, 1);

    obstacle_placement.set_xyz(9, 11, 1);
    obstacle_placement.set_name("Cooler Obstacle");
    race.add_obstacle(obstacle_placement, 2);

    obstacle_placement.set_xyz(420, 69, 7);
    obstacle_placement.set_name("Coolest Obstacle");
    race.add_obstacle(obstacle_placement, 3);

    race.create_route(0, 1);
    race.create_route(1, 2);

    race.display_course();


    if (!race.connect_start_finish()){
        cout << "Could not create start and finish for this course." 
        << endl << "Make sure there are some obstacles that lead nowhere, for finish"
        << endl << "Make sure there are some obstacles that have no incoming leads, for start."
        << endl;
        return 0;
    }

    cout << "Adding Contestants" << endl;
    sanic_fast.display();

    sanic_fast.enter_race(race);
    other_guy.enter_race(race);

    race.begin();

    while (race.check_if_active()){
        // Should have user get to go up/down here but I dont want to implement that.
        // This is the game-like interactve part where user needs to satisfy the obstacle.
        // Implementing that is not important to the learning purpose of this assignment,
        // so for now it just lands and takes route 0.
        sanic_fast.land();
        sanic_fast.display_route_options();
        sanic_fast.pick_route(0);
        sanic_fast.take_off();
        sanic_fast.navigate_route();
    
        other_guy.land();
        other_guy.display_route_options();
        other_guy.pick_route(0);
        other_guy.take_off();
        other_guy.navigate_route();

        cout << "Press enter to continue." << endl;
        cin.get();
    }

    race.display_results();
    cout << "Main is Done" << endl;

    return 0;
}