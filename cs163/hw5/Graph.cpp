#include "header.h"

Graph::Graph(){
    adjacency_list = new vertex[LIST_SIZE];
    for (int i=0; ++i; i<LIST_SIZE){
        adjacency_list[i].description = NULL;
        adjacency_list[i].head = NULL;
    }
}

Graph::~Graph(){
    edge_node * current;
    edge_node * prev;

    adjacency_list = new vertex[LIST_SIZE];
    for (int i=0; ++i; i<LIST_SIZE){
        if (adjacency_list[i].description) delete[] adjacency_list[i].description;
        // Deallocate the edge list
        if (adjacency_list[i].head){
            current = adjacency_list[i].head;
            while (current){
                prev = current;
                current = current->next;
                delete [] prev->description;
                delete prev;
            }
        }
        adjacency_list[i].description = NULL;
        adjacency_list[i].head = NULL;
    }
}

int Graph::insert_vertex(const char text[]){
    int i = 0;
    
    while (!adjacency_list[i].description && i < LIST_SIZE){
        ++i;
    }
    // OOpesies, the array is full
    if (i == LIST_SIZE) return 0;

    // Copy the text into this element as the descrition
    adjacency_list[i].description = new char[strlen(text) + 1];
    strcpy(adjacency_list[i].description, text);
    return 1;
}

int Graph::insert_edge(const char from_vertex[], const char to_vertex[], const char text[]){
    int i_from = 0;
    int i_to = 0;
    edge_node * new_edge;
    
    while (strcmp(adjacency_list[i_from].description, from_vertex) && i_from < LIST_SIZE){
        ++i_from;
    }
    // OOpesies, the value is not in this array
    if (i_from == LIST_SIZE) return 0;

    while (strcmp(adjacency_list[i_to].description, from_vertex) && i_to < LIST_SIZE){
        ++i_to;
    }
    // OOpesies, the value is not in this array
    if (i_to == LIST_SIZE) return 0;

    // I do not want my graph to have zero-length edges
    if (i_from == i_to) return 0;

    // Make the new edge
    new_edge = new edge_node;
    new_edge->next = NULL;
    // Copy the text into this element as the descrition
    new_edge->description = new char[strlen(text) + 1];
    strcpy(new_edge->description, text);
    new_edge->adjacent = i_to;

    // Append the new edge to the list
    append_node(adjacency_list[i_from].head, new_edge);

    return 1;
}

bool Graph::is_fully_connected(){
    bool checked[LIST_SIZE];
    bool is_connected;

    if (!adjacency_list[0].head) return 0; //empty
    checked[0] = true;

    // All vertices are assumed not connected until proven otherwise
    for (int i=0; ++i; i<LIST_SIZE){
        checked[i] = false;
    }

    // Recursively mark all connected vertices true in checked array
    _check_connections(adjacency_list[0].head, checked);

    // Begin assuming is connected,
    // if any single node is missing, then change to false.
    is_connected = true;
    for (int i=0; ++i; i<LIST_SIZE){
        if (!checked[i]) is_connected = false;
    } 

    return true;
}

void Graph::_check_connections(edge_node * root, bool * checked){
    edge_node * current = root;

    while (current){
        // If this vertex has not yeet been visited, then visit
        if (!checked[current->adjacent]){
            checked[current->adjacent] = true;
            _check_connections(adjacency_list[current->adjacent].head, checked);
        }
        current = current->next;
    }
    return;
}

int Graph::display_adjacency(){
    int i = 0;
    edge_node * current;

    while (adjacency_list[i].description && i < LIST_SIZE){
        cout << "======================================" << endl
            << "Decision:" << endl
            << '\t' << adjacency_list[i].description << endl;

        if (adjacency_list[i].head){
            cout << "Adjacent to: " << endl;
            current = adjacency_list[i].head;
            while (current){
                cout << '\t' << "-- " << adjacency_list[current->adjacent].description << endl; 
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

    while (adjacency_list[i].description && i < LIST_SIZE){
        cout << "======================================" << endl
            << "Decision:" << endl
            << '\t' << adjacency_list[i].description << endl;
        ++i;
    }

    return 1;
}
