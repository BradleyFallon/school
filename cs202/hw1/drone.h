// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 4/16/2019
// 
// ====================================================================

#include "location.h"


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

class Route{
    // This is a graph edge data
    public:
        Route();
    private:
    protected:
};

class RouteNode: public Route{
    // This is a graph edge node
    public:
        RouteNode();
    private:
    protected:
};

class Vertex: public Obstacle{
    // This is a graph vertex
    private:
        RouteNode * head;
};

class Course{
    // This is a graph
    public:
        Course();
        // ~Course();
        int add_obstacle(const Location &, int type_code);
        // Specifying vertices by index is much easier
        int create_route(int i_from, int i_to);
        void display_adjacency();
        void display_vertices();
    protected:
        Vertex * vertex_array;
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
