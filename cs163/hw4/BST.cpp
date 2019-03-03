






#include "header.h"








BST::BST(void){
    root_bst = NULL;
}

BST::~BST(void){
    _deallocate_all(root_bst);
}

void BST::_deallocate_all(node * & root){
    if (!root) return;
    _deallocate_all(root->left);
    _deallocate_all(root->right);
    // This should call the destructor of the data Term
    delete root;
    root = NULL;
}

// Insert a copy of a referenced term object, sorted by name
// Return 1 for success else 0
int BST::insert(Term & ref_term){
    return _insert(root_bst, ref_term);
}

int BST::_insert(node * & root, Term & ref_term){
    node * new_node;

    if (!root) return 0;
    if (root->term.is_less(ref_term)){
        // This word is equal/greater than root word --> go right.
        if (root->right) return _insert(root->right, ref_term);
        else {
            root->right = new node;
            new_node = root->right;
        }
    } else {
        // This word is less than root word --> go left.
        if (root->left) return _insert(root->left, ref_term);
        else {
            root->left = new node;
            new_node = root->left;
        }
    }
}

// Remove all with matching name
// Return number of objects removed
int BST::remove(const char word[]){


}

// Retrieve all with matching name
// Return number of objects found, whice are copied into "found" array
int BST::retrieve(const char word[], Term found[], int max_hits){


}

// Get the height of the longest branch of the tree
// Return the int height
int BST::get_height(){


}

bool BST::is_efficient(){


}

void BST::display_all(){


}

// Display all with names starting with characters within a given range
int BST::display_range(char min_val, char max_val){


}