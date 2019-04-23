

#include "location.h"

Location::Location(){
    name = NULL;
    x = 0;
    y = 0;
    z = 0;
};

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
    cout << "I'm a location" << endl;
    cout << "Location: (" << x << "," << y << "," << z << ")" << endl;
};

Obstacle::Obstacle(): Location(){

};

Obstacle::Obstacle(const Location & placement): Location(placement){

};

BlackHole::BlackHole(): Obstacle(){

};

BlackHole::BlackHole(const Location & placement): Obstacle(placement) {

};

TouchAndGo::TouchAndGo(): Obstacle(){

};

TouchAndGo::TouchAndGo(const Location & placement): Obstacle(placement) {

};

WindMill::WindMill(): Obstacle(){

};

WindMill::WindMill(const Location & placement): Obstacle(placement) {

};

