/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This contains the implementation for Drones and also classes
used to manage the drone contestants and their interaction in the
race event.
================================================================================
*/

#include "drone.h"

Drone::Drone(): Location(){}
Drone::Drone(const char to_name[]): Location(to_name){}
Drone::Drone(const Drone & drone_entry): Location(drone_entry){}

void Drone::display(){
    cout << "Hi I'm a drone!" << endl;
    Location::display();
};

void Drone::drive(const Location & destination){
    copy_location(destination);
}

DroneNode::DroneNode(int id_in): Drone(), next(NULL), id(id_in){}
DroneNode::DroneNode(const Drone & drone_entry, int id_in): Drone(drone_entry), next(NULL), id(id_in){}

void DroneNode::append(const Drone & drone_entry, int id_in){
    // If right is null, make new drone node there
    // If node exists to right, recursively call on right node
    if (next) next->append(drone_entry, id_in);
    else next = new DroneNode(drone_entry, id_in);
    return;
}

void DroneNode::append(DroneNode * other_ptr){
    if (!next){
        next = other_ptr;
    } else next->append(other_ptr);
}

DroneNode * DroneNode::pop_id(int drone_id, DroneNode * & head){
    if (id == drone_id){
        head = next;
        next = NULL;
        return this;
    }
    if (!next){
        // Could not find any node with this id :(
        return NULL;
    }
    return next->pop_id(drone_id, head);
}

DroneNode * DroneNode::pop(DroneNode * & head){
    head = next;
    next = NULL;
    return this;
}

void DroneNode::display_rank(int rank){
    cout << "Rank #" << rank << ") [" << id << "] " << name << endl;
    if (next) next->display_rank(++rank);
}

void DroneNode::display_all(){
    display();
    if (next) next->display_all();
}

Controller::Controller(): Drone() {}
Controller::Controller(const char to_name[]): Drone(to_name) {}

void Controller::set_target(const Location & destination){
    copy_location(destination);
}

void Controller::navigate_route(){
    drive(target_location);
}

void Controller::take_off(){
    z = 1;
}

void Controller::land(){
    z = 0;
}

Contestant::Contestant(): Controller(), id(0), target_waypoint_ptr(NULL){}
Contestant::Contestant(const char to_name[]): Controller(to_name), id(0), target_waypoint_ptr(NULL) {}

void Contestant::enter_race(Race & race_ref){
    race_ptr = &race_ref;
    id = race_ref.enter_drone(*this);
    target_waypoint_ptr = race_ref.get_start_location(target_location);
    drive(target_location);
}

int Contestant::pick_route(int route_opt){
    Waypoint * next_wp_ptr;
    next_wp_ptr = race_ptr->progress_drone(id, *this, target_waypoint_ptr, route_opt);
    if (next_wp_ptr){
        set_target(*next_wp_ptr);
        target_waypoint_ptr = next_wp_ptr;
        return 1;
    }
    return 0;
}

void Contestant::display_route_options(){
    cout << "-----------------------------------------------------" << endl;
    cout << "These are the available routes for  [" << id << "] " << name << ":" << endl;
    target_waypoint_ptr->display_routes();
    cout << "-----------------------------------------------------" << endl;
}

Race::Race(): Course(), contestants(0), is_complete(false), is_started(false), head_finishers(NULL), head_active(NULL) {}

int Race::enter_drone(const Drone & drone_entry){
    ++contestants;
    if (!head_active){
        head_active = new DroneNode(drone_entry, contestants);
    } else {
        head_active->append(drone_entry, contestants);
    }
    return contestants;
}

void Race::begin(){
    is_started = true;
}

bool Race::check_if_active(){
    return (is_started && !is_complete);
}

Waypoint * Race::progress_drone(int drone_id, Location & drone_loca, Waypoint * current_wp, int route_opt){
    Waypoint * next_wp = NULL;
    int next_id;

    // Check if drone already is done with race
    if (!current_wp){
        cout << "No current wp!" << endl;
        return next_wp;
    }
    if (current_wp == finish){
        cout << "Finished!" << endl;
        record_finisher(drone_id);
        return next_wp;
    }

    // Check if the drone's next wp has an obstacle
    Obstacle * current_obstacle_ptr = dynamic_cast<Obstacle*>(current_wp);
    if (current_obstacle_ptr){
        cout << "We have an obstacle!" << endl;
        // There is an obstace, check if it is succeded
        if (is_location_illegal(drone_loca)){
            disqualify_drone(drone_id);
            return next_wp;
        } else if (current_obstacle_ptr->is_failed(drone_loca)){
            disqualify_drone(drone_id);
            return next_wp;
        } else if (!current_obstacle_ptr->is_completed(drone_loca)){
            return current_wp;
        }
    }

    cout << "Drone gets to progress to next route." << endl;

    // Get the next waypoint from current, according to the route option
    next_wp = current_wp->get_next_wp(route_opt);

    cout << "Next waypoint is at: " << endl;
    cout << "pointer: " << next_wp << endl;
    next_wp->display();
    return next_wp;
}

bool Race::is_location_illegal(Location & place){
    // If the location entered is bad, return true to indicate badness
    if (place.get_z() > 68) return true;
    return false;
}

void Race::record_finisher(int drone_id){
    // Remove the drone from the active list and append to end of finishers list
    DroneNode * popped = NULL;
    if (head_active){
        popped = head_active->pop_id(drone_id, head_active);
        if (popped){
            if (head_finishers){
                head_finishers->append(popped);
            } else head_finishers = popped;
        }
    }
    if (!head_active){
        is_complete = true;
    }
};

void Race::disqualify_drone(int drone_id){
    // Remove the drone from active list without adding to finishers list
    DroneNode * popped = NULL;
    if (head_active){
        popped = head_active->pop_id(drone_id, head_active);
        if (popped) delete popped;
    }
};

Race::~Race(){
    DroneNode * popped = NULL;
    while (head_active){
        popped = head_active->pop(head_active);
        if (popped) delete popped;
    }
    // Congratulations to all head finishers
    // It is now time to go home
    while (head_finishers){
        popped = head_finishers->pop(head_finishers);
        if (popped) delete popped;
    }
}

void Race::display_results(){
    if (is_complete){
        cout << "Race complete!" << endl
        << "Contestant Standings:" << endl;
        head_finishers->display_rank(1);
    }
    
}
