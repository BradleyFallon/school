// ====================================================================
// Homework 5 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/15/2019
//
// This is the implementation of my graph class.
// ====================================================================

#include "header.h"

Graph::Graph(){
    vertex_array = new vertex[LIST_SIZE];
    for (int i=0; i<LIST_SIZE; ++i){
        vertex_array[i].description = NULL;
        vertex_array[i].head = NULL;
    }
}

Graph::~Graph(){
    edge_node * current;
    edge_node * prev;

    vertex_array = new vertex[LIST_SIZE];
    for (int i=0; i<LIST_SIZE; ++i){
        if (vertex_array[i].description) delete[] vertex_array[i].description;
        // Deallocate the edge list
        if (vertex_array[i].head){
            current = vertex_array[i].head;
            while (current){
                prev = current;
                current = current->next;
                delete [] prev->description;
                delete prev;
            }
        }
        vertex_array[i].description = NULL;
        vertex_array[i].head = NULL;
    }
}

int Graph::insert_vertex(const char text[]){
    int i;
    i = 0;

    while (vertex_array[i].description && i < LIST_SIZE){
        ++i;
    }
    // Ouchies, the array is full
    if (i == LIST_SIZE) return 0;

    // Copy the text into this element as the descrition
    vertex_array[i].description = new char[strlen(text) + 1];
    strcpy(vertex_array[i].description, text);
    // Lower the word, to keep things consistent
    make_lower(vertex_array[i].description);
    return 1;
}

int Graph::insert_edge(const char from_vertex[], const char to_vertex[], const char text[]){
    int i_from = 0;
    int i_to = 0;
    edge_node * new_edge;
    
    while (strcmp(vertex_array[i_from].description, from_vertex) && i_from < LIST_SIZE){
        ++i_from;
    }
    // OOpesies, the value is not in this array
    if (i_from == LIST_SIZE) return 0;

    while (strcmp(vertex_array[i_to].description, from_vertex) && i_to < LIST_SIZE){
        ++i_to;
    }
    // OOpesies, the value is not in this array
    if (i_to == LIST_SIZE) return 0;

    // I do not want my graph to have zero-length edges / loops
    if (i_from == i_to) return 0;

    // Make the new edge
    new_edge = new edge_node;
    new_edge->next = NULL;
    // Copy the text into this element as the descrition
    new_edge->description = new char[strlen(text) + 1];
    strcpy(new_edge->description, text);
    new_edge->adjacent = i_to;

    // Append the new edge to the list
    append_node(vertex_array[i_from].head, new_edge);

    return 1;
}

int Graph::insert_edge(int i_from, int i_to, const char text[]){
    edge_node * new_edge;

    // I do not want my graph to have zero-length edges / loops
    if (i_from == i_to) return 0;

    // Check if index in valid range
    if (i_to < 0 || i_to >= LIST_SIZE || i_from < 0 || i_from >= LIST_SIZE) return 0;

    // Check if valid vertices
    if (!vertex_array[i_to].description || !vertex_array[i_from].description) return 0;

    // Make the new edge
    new_edge = new edge_node;
    new_edge->next = NULL;
    // Copy the text into this element as the descrition
    new_edge->description = new char[strlen(text) + 1];
    strcpy(new_edge->description, text);
    new_edge->adjacent = i_to;

    // Append the new edge to the list
    append_node(vertex_array[i_from].head, new_edge);

    return 1;
}

bool Graph::is_fully_connected(){
    bool checked[LIST_SIZE];
    bool is_connected;
    int i;

    if (!vertex_array[0].head) return 0; //empty

    // All vertices are assumed not connected until proven otherwise
    for (int i=0; i<LIST_SIZE; ++i){
        checked[i] = false;
    }
    checked[0] = true;

    // Recursively mark all connected vertices true in checked array
    _check_connections(vertex_array[0].head, checked);

    // Begin assuming is connected,
    // if any single node is missing, then change to false.
    is_connected = true;
    i=0;
    while (vertex_array[i].description && i < LIST_SIZE){
        if (!checked[i]) is_connected = false;
        ++i;
    } 

    return is_connected;
}

void Graph::_check_connections(edge_node * root, bool * checked){
    edge_node * current = root;

    while (current){
        // If this vertex has not yeet been visited, then visit
        if (!checked[current->adjacent]){
            checked[current->adjacent] = true;
            _check_connections(vertex_array[current->adjacent].head, checked);
        }
        current = current->next;
    }
    return;
}

int Graph::display_adjacency(){
    int i = 0;
    edge_node * current;

    while (vertex_array[i].description && i < LIST_SIZE){
        cout << "======================================" << endl
            << "Decision:" << endl
            << '\t' << vertex_array[i].description << endl;

        if (vertex_array[i].head){
            cout << "Adjacent to: " << endl;
            current = vertex_array[i].head;
            while (current){
                cout << '\t' << "-- " << vertex_array[current->adjacent].description << endl; 
                cout << '\t' << '\t' << "via: " << current->description << endl;
                current = current->next;
            }
        }
        ++i;
    }

    return 1;
}

int Graph::display_vertices(){
    int i = 0;

    while (vertex_array[i].description && i < LIST_SIZE){
        cout << "======================================" << endl
            << "[" << i << "] Decision: " << endl
            << '\t' << vertex_array[i].description << endl;
        ++i;
    }

    return 1;
}
