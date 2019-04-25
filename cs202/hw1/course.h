
#include "location.h"





class Course{
    // This is a graph
    public:
        Course();
        // ~Course();
        int add_obstacle(const Location &, int type_code);
        // Specifying vertices by index is much easier
        int create_route(int i_from, int i_to);
        void display_course();
        void display_vertices();
        void finish_course();
        Location get_start_location();
    protected:
        void display_course(int i);
        Waypoint ** vertex_array;
        Waypoint * start;
        Waypoint * finish;
};

