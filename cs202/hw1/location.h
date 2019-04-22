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
        void display();
    private:
    protected:
        char* name;
        int x;
        int y;
        int z;

};

class Obstacle: public Location{
    public:
        Obstacle();
        // Constructor that copies location props from a location ref
        Obstacle(const Location & placement);
    private:
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
