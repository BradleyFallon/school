/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This contains the class implementations for Locations and also classes
which are derived to create race waypoints and obstacle waypoints along
with the list derivations for managing them.
================================================================================
*/

#include "location.h"

Location::Location(): x(0), y(0), z(0){
    name = new char[10];
    strcpy(name, "Anonymous");
}

Location::Location(const char to_name[]): x(0), y(0), z(0){
    name = NULL;
    set_name(to_name);
}

Location::Location(const Location & loca_ref) {
    name = new char[strlen(loca_ref.name)+1];
    strcpy(name, loca_ref.name);
    x = loca_ref.x;
    y = loca_ref.y;
    z = loca_ref.z;
}

void Location::set_name(const char text[]){
    if (name) delete[] name;
    name = new char[strlen(text)+1];
    strcpy(name, text);
}

void Location::set_xyz(int xin, int yin, int zin){
    x = xin;
    y = yin;
    z = zin;
};

int Location::get_z(){
    return z;
}

void Location::display(){
    cout << "Name: " << name << endl;
    cout << "Location: (" << x << "," << y << "," << z << ")" << endl;
};

void Location::copy_location(const Location & loca_ref) {
    x = loca_ref.x;
    y = loca_ref.y;
    z = loca_ref.z;
}

Location::~Location(){
    delete[] name;
}

Route::Route(): dest_id(0), dest_wp_ptr(NULL){}

void Route::set_destination(Waypoint * wp_ptr, int wp_id){
    dest_wp_ptr = wp_ptr;
    dest_id = wp_id;
};

void Route::display(){
    cout << "Route to obstacle #" << dest_id << endl;
};

RouteNode::RouteNode(): Route(), next(NULL){
    cout << "Created RouteNode and dest_id initially is: " << dest_id << endl;
}

void RouteNode::display_all(){
    display();
    if (next) next->display_all();
};

void RouteNode::append_node(RouteNode * to_add){
    if (next)
        next->append_node(to_add);
    else
        next = to_add;
}

RouteNode * RouteNode::pop(RouteNode * & head){
    head = next;
    next = NULL;
    return this;
}

Waypoint * RouteNode::get_dest(int route_opt){
    /*
    This recursively tics down route_opt as it traverses,
    then returns id of when opt==0.
    */
    if (route_opt){
        // If we picked too high a number, just return the last node id
        // It's just a game...
        if (next){
            return next->get_dest(--route_opt);
        }
    }
    return dest_wp_ptr;
}

Waypoint::Waypoint(): Location(), head(NULL) {}
Waypoint::Waypoint(const Location & placement): Location(placement), head(NULL) {}

void Waypoint::add_route(RouteNode * to_add){
    if (head){
        head->append_node(to_add);
    }
    else head = to_add;
};

void Waypoint::display_routes(){
    Location::display();
    if (head) head->display_all();
    else cout << "Dead end!" << endl;
}

Waypoint * Waypoint::get_next_wp(int route_opt){
    if (!head) return 0;
    return head->get_dest(route_opt);
}

Waypoint::~Waypoint(){
    RouteNode * popped = NULL;
    while (head){
        popped = head->pop(head);
        if (popped) delete popped;
    }
}

Obstacle::Obstacle(): Waypoint(){}
Obstacle::Obstacle(const Location & placement): Waypoint(placement) {}

BlackHole::BlackHole(): Obstacle(){}
BlackHole::BlackHole(const Location & placement): Obstacle(placement) {}
bool BlackHole::is_completed(const Location &) {return true;}
bool BlackHole::is_failed(const Location &) {return false;}

TouchAndGo::TouchAndGo(): Obstacle(){}
TouchAndGo::TouchAndGo(const Location & placement): Obstacle(placement) {}
bool TouchAndGo::is_completed(const Location &) {return true;}
bool TouchAndGo::is_failed(const Location &) {return false;}

WindMill::WindMill(): Obstacle(){}
WindMill::WindMill(const Location & placement): Obstacle(placement) {}
bool WindMill::is_completed(const Location &) {return true;}
bool WindMill::is_failed(const Location &) {return false;}

