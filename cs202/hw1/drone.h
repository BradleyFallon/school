// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 4/16/2019
// 
// ====================================================================

#include "course.h"


class Drone: public Location{
    public:
        Drone();
        Drone(const Drone &);
        void display();
    private:
    protected:
};

class DroneNode: public Drone{
    public:
        DroneNode();
        DroneNode(const Drone &);
        void go_right();
        void append(const Drone &);
        void display_all();
    private:
        DroneNode * next;
    protected:
        
};

class Controller: public Drone{
    public:
        Controller();
    private:
    protected:
    
};

class Contestant: public Controller{

    public:
        Contestant();
        void attach_id(int);

    private:
        int contestant_id;

};


class Race: public Course{

    public:
        Race();

        // This takes a reference to a drone, copies it into a new node, and appends to active list
        // returns contestant id on success else NULL
        int enter_drone(Drone &);
        
    private:
        DroneNode * head_finishers;
        DroneNode * head_active;

        int contestants;
        bool is_complete;
        bool is_started;
};
