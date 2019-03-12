#include "header.h"

int append_node(edge_node * & root, edge_node * to_add){
    if (!root){
        root = to_add;
        return 1;
    }
    append_node(root->next, to_add);
    return 0; // Shouldn't happen in normal situations
}