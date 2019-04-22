
#include "drone.h"

Course::Course(){
    vertex_array = NULL;
};

int Course::add_obstacle(const Location & placement, int type_code){
    Obstacle * obstacle_ptr;
    
    if (type_code==1){
        // Create a black hole
        BlackHole bh(placement);
        obstacle_ptr = &bh;
    } else if (type_code==2) {
        // Create a touch and go
        TouchAndGo tg(placement);
        obstacle_ptr = &tg;
    } else if (type_code==3) {
        // Create a windmill
        WindMill wm(placement);
        obstacle_ptr = &wm;
    } else {
        return 0;
    }
};

int Course::create_route(int i_from, int i_to){
    // This creates a graph edge that represents
    // a route in course between two obstacles

};
