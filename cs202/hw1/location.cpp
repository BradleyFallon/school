#include "location.h"

Location::Location(): x(0), y(0), z(0){
    name = new char[10];
    strcpy(name, "Anonymous");
}

Location::Location(const Location & ref){
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
    cout << "Name: " << name << endl;
    cout << "Location: (" << x << "," << y << "," << z << ")" << endl;
};

Route::Route(): destination(0), distance(0.0) {}

void Route::set_destination(const int target){
    destination = target;
};

void Route::set_distance(const float value){
    distance = value;
};

void Route::display(){
    cout << "Route to obstacle #" << destination << " distance: " << distance << " meters." << endl;
};

RouteNode::RouteNode(): Route(), next(NULL) {}

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

Obstacle::Obstacle(): Waypoint(){}
Obstacle::Obstacle(const Location & placement): Waypoint(placement) {}


BlackHole::BlackHole(): Obstacle(){}
BlackHole::BlackHole(const Location & placement): Obstacle(placement) {}

TouchAndGo::TouchAndGo(): Obstacle(){}
TouchAndGo::TouchAndGo(const Location & placement): Obstacle(placement) {}

WindMill::WindMill(): Obstacle(){}
WindMill::WindMill(const Location & placement): Obstacle(placement) {}

