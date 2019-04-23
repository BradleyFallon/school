
#include "location.h"

Route::Route(){

};

void Route::set_destination(const int target){
    destination = target;
};

void Route::set_distance(const float value){
    distance = value;
};

RouteNode::RouteNode(): Route(){
    next = NULL;
};

void RouteNode::connect(RouteNode * other){
    next = other;
};

Course::Course(){
    vertex_array = new Obstacle*[LIST_SIZE];
    for (int i=0; i<LIST_SIZE; ++i){
        vertex_array[i] = NULL;
    }
};


int Course::add_obstacle(const Location & placement, int type_code){
    Obstacle * obstacle_ptr;
    int i = 0;

    // Go to next free slot in array or return 0 if full
    while (vertex_array[i] && i < LIST_SIZE){
        ++i;
    }
    // Ouchies, the array is full
    if (i == LIST_SIZE) return 0;

    if (type_code==1){
        // Create a black hole
        BlackHole bh(placement);
        vertex_array[i] = &bh;
    } else if (type_code==2) {
        // Create a touch and go
        TouchAndGo tg(placement);
        vertex_array[i] = &tg;
    } else if (type_code==3) {
        // Create a windmill
        WindMill wm(placement);
        vertex_array[i] = &wm;
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
    created_route.set_distance(10);

    new_edge->adjacent = i_to;

    // Append the new edge to the list
    append_node(vertex_array[i_from].head, new_edge);

    return 1;
};
