/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This contains the implementation for the course, which is implemented as a
graph of waypoints connected via weighted edges which are called routes.
A waypoint is a location a drone must pass through in order to proceed to the 
next leg of the course. An obstacle is a waypoint with special requirements
that must be satisfied in order to pass through to the next leg.
================================================================================
*/


#include "course.h"

Course::Course(){
    /*
    This initializes a course graph. It has an array of adjacency lists
    which describes what the route opions are from each waypoint vertex.
    A waypoint may or may not be an obstacle. An obstacle is a waypoint
    with special requirements required to pass.
    There are two special waypoints that are not part of the vertex array,
    these are the start and finish, and they have their own dedicated pointer variables.
    */
    int i=0;
    Location placement;

    // initialize vertex array
    vertex_array = new Waypoint*[LIST_SIZE];
    while (i<LIST_SIZE){
        vertex_array[i] = NULL;
        ++i;
    }

    // create start waypoint
    placement.set_xyz(0, 0, 0);
    placement.set_name("Race Start");
    start = new Waypoint(placement);

    // create finish waypoint
    placement.set_xyz(100, 100, 100);
    placement.set_name("Race Finish");
    finish = new Waypoint(placement);
}

Course::~Course(){
    int i=0;

    // destroy vertex array
    while (i<LIST_SIZE){
        if (vertex_array[i]) delete vertex_array[i];
        vertex_array[i] = NULL;
        ++i;
    }
    delete [] vertex_array;
    if (start) delete start;
    start = NULL;
    if (finish) delete finish;
    finish = NULL;
};

int Course::add_obstacle(const Location & placement, int type_code){
    int i = 0;

    // Go to next free slot in array or return 0 if full
    while (vertex_array[i] && i < LIST_SIZE){
        ++i;
    }
    // Bummer, the array is full, course is at max complexity allowed
    if (i == LIST_SIZE) return 0;

    if (type_code==0){
        // Create a plain waypoint with no obstacle
        vertex_array[i] = new Waypoint(placement);
    } else if (type_code==1){
        // Create a black hole
        vertex_array[i] = new BlackHole(placement);
    } else if (type_code==2) {
        // Create a touch and go
        vertex_array[i] = new TouchAndGo(placement);
    } else if (type_code==3) {
        // Create a windmill
        vertex_array[i] = new WindMill(placement);
    } else {
        return 0;
    }
};

int Course::create_route(int i_from, int i_to){
    /*
    This creates a graph edge that represents
    a route in course between two waypoints
    */

    RouteNode * created_route;

    // I do not want my graph to have zero-length edges / loops
    if (i_from == i_to) return 0;
    // Check if index in valid range
    if (i_to < 0 || i_to >= LIST_SIZE || i_from < 0 || i_from >= LIST_SIZE) return 0;
    // Check if valid vertices
    if (!vertex_array[i_to] || !vertex_array[i_from]) return 0;

    // Make the new edge
    created_route = new RouteNode;
    created_route->set_destination(vertex_array[i_to], i_to);

    // Append the new edge to the list
    vertex_array[i_from]->add_route(created_route);

    return 1;
};


void Course::display_course(int i){
    /*
    I think it is proabably hurtful to make this recursive.
    This is recursive just to demonstrate how it could be done.
    */
    if (vertex_array[i] && i < LIST_SIZE){
        cout << "======================================" << endl
            << "Obstacle [" << i << "]:" << endl;
            vertex_array[i]->display_routes();
        display_course(i+1);
    }
}
void Course::display_course(){
    display_course(0);
}

int Course::connect_start_finish(){
    RouteNode * created_route;
    int i = 0;

    // Make the new edge as route from start to waypoint 0
    // I would intend to make this pick all inaccessable waypoints,
    // but not a priority for assignment
    created_route = new RouteNode;
    created_route->set_destination(vertex_array[0], 0);

    // Append the new edge to the list
    start->add_route(created_route);

    // Make the new edge to get from dead ends to finish
    created_route = new RouteNode;
    created_route->set_destination(finish, 0);

    while (vertex_array[i] && i < LIST_SIZE){
        // If any wp is a dead end, make rout to finish
        if (!vertex_array[i]->get_next_wp(0)){
            vertex_array[i]->add_route(created_route);
        }
        ++i;
    }

    return 1;
}

Waypoint * Course::get_start_location(Location & loca_dest){
    loca_dest.copy_location(*start);
    return start;
}
