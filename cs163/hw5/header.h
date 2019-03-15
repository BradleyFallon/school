// ====================================================================
// Homework 5 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/15/2019
//
// Main header file. Used for all classes and ADT prototypes.
// ====================================================================

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int SIZE_TEMP_CHARS = 256;
const int LIST_SIZE = 20;

struct edge_node
{
    int adjacent;
    char * description;
    edge_node * next;
};

struct vertex
{
    char * description;
    // Edge list
    edge_node * head;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        int insert_vertex(const char text[]);
        // I made a method to insert by vertex naes, but didn't use it because it is too much effort to type
        int insert_edge(const char from_vertex[], const char to_vertex[], const char text[]);
        // Specifying vertices by index is much easier
        int insert_edge(int i_from, int i_to, const char text[]);
        bool is_fully_connected();
        int display_adjacency();
        int display_vertices();
    private:
        void _check_connections(edge_node * root, bool * checked);
        vertex * vertex_array;
};

int make_lower(char text[]);
int append_node(edge_node * & root, edge_node * to_add);
