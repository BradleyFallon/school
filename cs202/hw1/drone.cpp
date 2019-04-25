

#include "drone.h"

Drone::Drone(): Location(){}
Drone::Drone(const char to_name[]): Location(to_name){}
Drone::Drone(const Drone & drone_entry): Location(drone_entry){}

void Drone::display(){
    cout << "Hi I'm a drone!" << endl;
    Location::display();
};

DroneNode::DroneNode(): Drone(), next(NULL){}
DroneNode::DroneNode(const Drone & drone_entry): Drone(drone_entry), next(NULL){}

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

Controller::Controller(): Drone() {}
Controller::Controller(const char to_name[]): Drone(to_name) {}

Contestant::Contestant(): Controller(), id(0) {}
Contestant::Contestant(const char to_name[]): Controller(to_name), id(0) {}

void Contestant::enter_race(Race * race_ref){
    race_ptr = race_ref;
    id = race_ptr->enter_drone(this);
    drive(race_ptr->get_start_location());
}

Race::Race(): Course(), contestants(0), is_complete(false), is_started(false), head_finishers(NULL), head_active(NULL) {}

int Race::enter_drone(Drone & drone_entry){
    if (!head_active){
        head_active = new DroneNode(drone_entry);
    } else {
        head_active->append(drone_entry);
    }
    ++contestants;
    return contestants;
}