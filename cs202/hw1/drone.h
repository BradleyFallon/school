/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This is contains the class definitions for Drones and also classes
used to manage the drone contestants and their interaction in the
race event.
================================================================================
*/

#include "course.h"


class Drone: public Location{
    /*
    This class is the base class for all drone related objects.
    This doesnt really add much to the location class, other than
    having different terms and displays more info.
    Really, the drive method is just calling the copy location method which is
    part of the Location class.
    If this program was to be enhanced, there would be more drone data here
    such as speed, but I don't have time for that. All obstacle requirements are
    currently based solely on location.
    */
    public:
        Drone();
        Drone(const char[]);
        Drone(const Drone &);
        void display();
        void drive(const Location &);
    private:
    protected:
};

class Controller: public Drone{
    /*
    This class extends the drone to be able to maneuver an obstacle.
    The drone class has a drive method, but this tells the drone where
    to drive in order to satisfy the course.
    */
    public:
        Controller();
        Controller(const char[]);
        void set_target(const Location &);
        void navigate_route();
        void take_off();
        void land();
    private:
    protected:
        Location target_location;
};

class DroneNode: public Drone{
    /*
    This is not for creating drone objects which are interacting with the race,
    this is for the event to keep record of the drones in the race.
    A DroneNode is a LLL node which copies initial data of a drone
    when it enters the race, then the contestant's id is used to update
    the status of the drone in the race event.
    */
    public:
        DroneNode(int id_in);
        DroneNode(const Drone &, int id_in);
        void go_right();
        // This is meant for adding new contestants data as copy
        void append(const Drone &, int id_in);
        // This takes an existing drone node and appends it to this list
        void append(DroneNode * other_ptr);
        void display_all();
        DroneNode * pop_id(int drone_id, DroneNode * & head);
        DroneNode * pop(DroneNode * & head);
        void display_rank(int rank);
        // Id is used to track drone contestant race stats
        const int id;
    private:
        DroneNode * next;
    protected:
        
};

class Race: public Course{
    /*
    This is the race event management class, which is a course and keeps track of
    the competitors. This class will dictate wether a drone has successfully
    completed the course. This also will record rankings of the contestants.
    */
    public:
        Race();
        // This takes a reference to a drone, copies it into a new node,
        // and appends to active list.
        // returns contestant id on success else NULL.
        int enter_drone(const Drone &);
        void begin();
        bool check_if_active();
        Waypoint * progress_drone(int id, Location & drone_loca, Waypoint * current_wp, int route_opt);
        void disqualify_drone(int drone_id);
        bool is_location_illegal(Location &);
        void record_finisher(int drone_id);
        void display_results();
        ~Race();
    private:
        DroneNode * head_finishers;
        DroneNode * head_active;

        int contestants;
        bool is_complete;
        bool is_started;
};


class Contestant: public Controller{
    /*
    This represents the person who makes decisions for the drone and 
    is registered fr the race.
    */
    public:
        Contestant();
        Contestant(const char[]);
        void enter_race(Race & race_dest);
        void display_route_options();
        int pick_route(int route_opt);
    private:
        int id;
        Waypoint * target_waypoint_ptr;
        Race * race_ptr;
};



