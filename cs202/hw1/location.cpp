

#include "location.h"

Location::Location(){
    name = NULL;
    x = 0;
    y = 0;
    z = 0;
};

Location::Location(const Location & ref){
    cout << "In Location placaement constructor" << endl;
    
    name = new char[strlen(ref.name)+1];
    strcpy(name, ref.name);
    x = ref.x;
    y = ref.y;
    z = ref.z;
};

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

void Location::display(){
    cout << "I'm a location" << endl;
    cout << "Location: (" << x << "," << y << "," << z << ")" << endl;
};

Route::Route(){
    destination = 0;
    distance = 0.0;
};

void Route::set_destination(const int target){
    destination = target;
};

void Route::set_distance(const float value){
    distance = value;
};

void Route::display(){
    cout << destination;
    cout << distance;

    cout << "Route to obstacle #" << destination << " distance: " << distance << " meters." << endl;
};

RouteNode::RouteNode(): Route(), next(NULL){
    next = NULL;
};

void RouteNode::display_all(){
    display();
    if (next) next->display_all();
};

void RouteNode::append_node(RouteNode * to_add){
    cout << "next: " << next << endl;
    if (next)
        next->append_node(to_add);
    else
        next = to_add;
}

Waypoint::Waypoint(): Location(){
    head = NULL;
    cout << "in constructor 1" << endl;
};

Waypoint::Waypoint(const Location & placement): Location(placement){
    head = NULL;
    cout << "In Waypoint placaement constructor" << endl;
};

void Waypoint::add_route(RouteNode * to_add){
    cout << "head: " << head;
    if (head){
        head->append_node(to_add);
    }
    else head = to_add;
};

void Waypoint::display_routes(){

    Location::display();
    cout << "I am a waypoint" << endl;


    if (head) head->display_all();
}

Obstacle::Obstacle(): Waypoint(){

};

Obstacle::Obstacle(const Location & placement): Waypoint(placement){
    cout << "In obstacle placaement constructor" << endl;
};


BlackHole::BlackHole(): Obstacle(){

};

BlackHole::BlackHole(const Location & placement): Obstacle(placement) {
    cout << "created blackhole: " << endl;
    display();
};

TouchAndGo::TouchAndGo(): Obstacle(){

};

TouchAndGo::TouchAndGo(const Location & placement): Obstacle(placement) {

};

WindMill::WindMill(): Obstacle(){

};

WindMill::WindMill(const Location & placement): Obstacle(placement) {

};

