/*
================================================================================
Homework 1 for CS202
Bradley Fallon
bfallon@pdx.edu
4/29/2019

This contains the class definitions for the course, which is implemented as a
graph of waypoints connected via weighted edges which are called routes.
A waypoint is a location a drone must pass through in order to proceed to the 
next leg of the course. An obstacle is a waypoint with special requirements
that must be satisfied in order to pass through to the next leg.
================================================================================
*/

#include "location.h"

class Course{
    // This is a graph
    public:
        Course();
        ~Course();
        int add_obstacle(const Location &, int type_code);
        // Specifying vertices by index is much easier
        int create_route(int i_from, int i_to);
        void display_course();
        void display_vertices();
        void finish_course();
        // Copies the location of the start location and return pointer to waypoint
        Waypoint * get_start_location(Location &);
        int connect_start_finish();
    protected:
        void display_course(int i);
        Waypoint ** vertex_array;
        Waypoint * start;
        Waypoint * finish;
};

