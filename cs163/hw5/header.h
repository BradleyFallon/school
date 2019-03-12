// ====================================================================
// Homework 5 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/11/2019
//
// Main header file. Used for all classes and ADT prototypes.
// ====================================================================

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int SIZE_TEMP_CHARS = 256;
const int LIST_SIZE = 20;

struct vertex
{
    char * description;
    // Edge list
    edge_node * head;
};

struct edge_node
{
       int adjacent;
       char * description;
       edge_node * next;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        int insert_vertex(const char text[]);
        int insert_edge(const char from_vertex[], const char to_vertex[], const char text[]);
        bool is_fully_connected();
        int display_adjacency();
        int display_vertices();
    private:
        void _check_connections(edge_node * root, bool * checked);
        vertex * adjacency_list;
};

int append_node(edge_node * & root, edge_node * to_add){};

