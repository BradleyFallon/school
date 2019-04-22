

#include "drone.h"

Race::Race(){
    contestants = 0;
    is_complete = false;
    is_started = false;

    head_finishers = NULL;
    head_active = NULL;
}

int Race::enter_drone(Drone & drone_entry){
    head_active = NULL;

    if (!head_active){
        head_active = new DroneNode(drone_entry);
    } else {
        head_active->append(drone_entry);
    }

    ++contestants;

    return contestants;
}

Drone::Drone(): Location(){

}

Drone::Drone(const Drone & drone_entry){

}

void Drone::display(){
    cout << "Hi I'm a drone!" << endl;
    Location::display();
};

DroneNode::DroneNode(): Drone(){

}

DroneNode::DroneNode(const Drone & drone_entry): Drone(drone_entry){

}

void DroneNode::append(const Drone & drone_entry){
    // If right is null, make new drone node there
    // If node exists to right, recursively call on right node
    if (next) next->append(drone_entry);
    else next = new DroneNode(drone_entry);
    return;
}

void DroneNode::display_all(){
    display();
    if (next) next->display_all();
}

Controller::Controller(): Drone(){

}

Contestant::Contestant(): Controller(){
    contestant_id = 0;
}

void Contestant::attach_id(int id_no){
    contestant_id = id_no;
}