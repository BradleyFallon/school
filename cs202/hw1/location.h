/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This contains the class definitions for Locations and also classes
which are derived to create race waypoints and obstacle waypoints along
with the list derivations for managing them.
================================================================================
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int SIZE_TEMP_CHARS = 256;
const int LIST_SIZE = 20;

class Location{
    public:
        Location();
        Location(const char[]);
        Location(const Location &);
        void display();
        void set_name(const char[]);
        void set_xyz(int, int, int);
        int get_z();
        void copy_location(const Location &);
        ~Location();
    private:
    protected:
        char* name;
        int x;
        int y;
        int z;
};

// Pre-declare Waypoint so we can have a ptr in RouteNode
class Waypoint;

class Route{
    // This is a graph edge data
    public:
        Route();
        void set_destination(Waypoint * wp_ptr, int wp_id);
        void display();
        // No destructor because the only dynamic memory
        // is the destination pointer, but that memory is managed by
        // the Course class.
    private:
    protected:
        int dest_id;
        Waypoint * dest_wp_ptr;
};

class RouteNode: public Route{
    // This is a graph edge node
    public:
        RouteNode();
        void append_node(RouteNode * to_add);
        void display_all();
        // This recursively tics down route_opt as it traverses,
        // then returns id of when opt==0.
        Waypoint * get_dest(int route_opt);
        RouteNode * pop(RouteNode * & head);
    private:
    protected:
        RouteNode * next;
};

class Waypoint: public Location{
    public:
        Waypoint();
        Waypoint(const Location & placement);
        void add_route(RouteNode * to_add);
        void display_routes();
        Waypoint * get_next_wp(int route_opt);
        virtual ~Waypoint();
    private:
    // This is a graph vertex
    protected:
        RouteNode * head;
};


class Obstacle: public Waypoint{
    public:
        Obstacle();
        // Constructor that copies location props from a location ref
        Obstacle(const Location & placement);
        // Race uses this to check if drone has satisfied obstacle
        virtual bool is_completed(const Location &) = 0;
        // Race uses this to check if drone gets removed from race
        virtual bool is_failed(const Location &) = 0;
    private:
    protected:
};

class BlackHole: public Obstacle{
    // Drone must pass x,y == obstacle x,y
    // If too close in z, drone is consumed
    public:
        BlackHole();
        BlackHole(const Location & placement);
        // Race uses this to check if drone has satisfied obstacle
        bool is_completed(const Location &);
        // Race uses this to check if drone gets removed from race
        bool is_failed(const Location &);
    private:
    protected:
};

class TouchAndGo: public Obstacle{
    // Drone must pass x,y == obstacle x,y
    // drone must have z == 0 to pass
    // This obstacle is always at z=0
    public:
        TouchAndGo();
        TouchAndGo(const Location & placement);
        // Race uses this to check if drone has satisfied obstacle
        bool is_completed(const Location &);
        // Race uses this to check if drone gets removed from race
        bool is_failed(const Location &);
    private:
    protected:
};

class WindMill: public Obstacle{
    // Drone must pass x,y,z == obstacle x,y,z
    // there is a random chance of being destroyed
    public:
        WindMill();
        WindMill(const Location & placement);
        // Race uses this to check if drone has satisfied obstacle
        bool is_completed(const Location &);
        // Race uses this to check if drone gets removed from race
        bool is_failed(const Location &);
    private:
    protected:
};


