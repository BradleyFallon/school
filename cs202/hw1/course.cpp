
#include "course.h"

Course::Course(){
    int i=0;
    Location placement;

    vertex_array = new Waypoint*[LIST_SIZE];
    while (i<LIST_SIZE){
        vertex_array[i] = NULL;
        ++i;
    }

    placement.set_xyz(0, 0, 0);
    placement.set_name("Race Start");
    start = new Waypoint(placement);

    placement.set_xyz(100, 100, 100);
    placement.set_name("Race Finish");
    finish = new Waypoint(placement);

};

int Course::add_obstacle(const Location & placement, int type_code){
    int i = 0;

    // Go to next free slot in array or return 0 if full
    while (vertex_array[i] && i < LIST_SIZE){
        ++i;
    }
    // Ouchies, the array is full
    if (i == LIST_SIZE) return 0;

    if (type_code==1){
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
    // This creates a graph edge that represents
    // a route in course between two obstacles

    RouteNode * created_route;

    // I do not want my graph to have zero-length edges / loops
    if (i_from == i_to) return 0;
    // Check if index in valid range
    if (i_to < 0 || i_to >= LIST_SIZE || i_from < 0 || i_from >= LIST_SIZE) return 0;
    // Check if valid vertices
    if (!vertex_array[i_to] || !vertex_array[i_from]) return 0;

    // Make the new edge
    created_route = new RouteNode;
    // Set distance
    
    created_route->set_distance(10);
    created_route->set_destination(i_to);

    // Append the new edge to the list
    vertex_array[i_from]->add_route(created_route);

    return 1;
};

// I think it is really pointless and proabably hurtful to make this recursive
// Only recursive to show it can be
void Course::display_course(int i){
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

    // Make the new edge
    created_route = new RouteNode;
    // Set distance
    created_route->set_distance(10);
    created_route->set_destination(0);

    // Append the new edge to the list
    start->add_route(created_route);

    // Make the new edge
    created_route = new RouteNode;
    // Set distance
    created_route->set_distance(10);
    created_route->set_destination(1);

    finish->add_route(created_route);
    return 1;
}

Location Course::get_start_location(){
    return Location(start);
}
