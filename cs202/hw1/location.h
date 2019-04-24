// ====================================================================
// Homework 1 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 4/16/2019
// 
// ====================================================================

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int SIZE_TEMP_CHARS = 256;
const int LIST_SIZE = 20;

class Location{
    public:
        Location();
        Location(const Location & ref);
        void display();
        void set_name(const char[]);
        void set_xyz(int, int, int);
    private:
    protected:
        char* name;
        int x;
        int y;
        int z;
};

class Route{
    // This is a graph edge data
    public:
        Route();
        void set_destination(int);
        void set_distance(float);
        void get_distance();
        void display();
    private:
    protected:
        float distance;
        int destination;
};

class RouteNode: public Route{
    // This is a graph edge node
    public:
        RouteNode();
        void append_node(RouteNode * to_add);
        void display_all();
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
    private:
    // This is a graph vertex
    protected:
};

class BlackHole: public Obstacle{
    public:
        BlackHole();
        BlackHole(const Location & placement);
    private:
    protected:
};

class TouchAndGo: public Obstacle{
    public:
        TouchAndGo();
        TouchAndGo(const Location & placement);
    private:
    protected:
};

class WindMill: public Obstacle{
    public:
        WindMill();
        WindMill(const Location & placement);
    private:
    protected:
};


