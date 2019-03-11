// ====================================================================
// Homework 4 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/11/2019
//
// Binary Search Tree Class file.
// ====================================================================

#include "header.h"
#include <math.h>   // for log2  http://www.cplusplus.com/reference/cmath/log2/ or pow

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

    if (!root){
        // define the new node
        new_node = new node;
        new_node->term.clone(ref_term);
        new_node->left = NULL;
        new_node->right = NULL;
        root = new_node;
        return 1;
    }
    if (root->term.is_less(ref_term)){
        // This word is equal/greater than root word --> go right.
        return _insert(root->right, ref_term);
    } else {
        // This word is less than root word --> go left.
        return _insert(root->left, ref_term);
    }
    return 0; // Shouldnt occur
}

// Remove all with matching name
// Return number of objects removed
int BST::remove(const char word[]){
    int ret;
    char * lower_word;
    lower_word = new char[strlen(word)+1];
    strcpy(lower_word, word);
    make_lower(lower_word);
    ret = _remove(root_bst, lower_word);
    delete [] lower_word;
    return ret;
}

int BST::_remove(node * & root, const char word[]){
    char this_word[SIZE_TEMP_CHARS];
    int count = 0;
    bool do_delete = false;
    node * temp;
    node * ios;
    node * ios_prev;

    if (!root) return 0;

    root->term.get_word(this_word);
    if (!strcmp(word, this_word)){
        ++count;
        do_delete = true;
    }

    if (root->term.is_less(word)){
        // This word is equal/greater than root word --> go right.
        if (root->right){
            count = count + _remove(root->right, word);
        }
    // There will only be a possible hit to the left if the search val is less than root
    } else {
        // This word is less than root word --> go left.
        if (root->left) {
            count = count + _remove(root->left, word);
        }
    }

    if (do_delete){
        // delete root;
        temp = root;

        // get the in order successor (IOS)
        if (root->right){
            ios = root->right;
            if (ios->left){
                while (ios->left){
                    ios_prev = ios;
                    ios = ios->left;
                }
                // pop out the ios, so it can replace root
                // if there are children to right, bring them up to hole from ios.
                // (note, there are never children to left, because this is ios)
                // If Null right, then prev's left becomes null
                ios_prev->left = ios->right;
                ios->right = root->right;
            }
            ios->left = root->left;
            root = ios;
        } else {
            // root becomes left, even if left is null, because there was not right
            root = root->left;
        }
        delete temp;

    }
    
    return count;
}

// Retrieve all with matching name
// Return number of objects found, whice are copied into "found" array
int BST::retrieve(const char word[], Term * found){
    int ret;
    char * lower_word;
    lower_word = new char[strlen(word)+1];
    strcpy(lower_word, word);
    make_lower(lower_word);
    ret = _retrieve(root_bst, word, found);
    delete [] lower_word;
    return ret;
}

int BST::_retrieve(node * & root, const char word[], Term * found){
    char this_word[SIZE_TEMP_CHARS];
    int count = 0;
    bool is_match = false;

    if (!root) return 0;

    root->term.get_word(this_word);

    if (!strcmp(word, this_word)){
        found->clone(root->term);
        return 1;
    }

    if (root->term.is_less(word)){
        // This word is equal/greater than root word --> go right.
        if (root->right){
            return _retrieve(root->right, word, found);
        }
    // There will only be a possible hit to the left if the search val is less than root
    } else {
        // This word is less than root word --> go left.
        if (root->left) {
            return _retrieve(root->left, word, found);
        }
    }

    return 0;
}

// Get the height of the longest branch of the tree
// Return the int height
int BST::get_height(){
    return _get_height(root_bst);

}

int BST::_get_height(node * & root){

    int h_left;
    int h_right;

    if (!root) return 0;

    h_left = _get_height(root->left);
    h_right = _get_height(root->right);

    if (h_left > h_right)
        return h_left + 1;
    else return h_right + 1;
}

// Get node count, return in t count
int BST::count_nodes(){
    return _count_nodes(root_bst);
}

int BST::_count_nodes(node * & root){
    if (!root) return 0;
    return 1 +_count_nodes(root->left) + _count_nodes(root->right);
}


bool BST::is_efficient(){
    // Min Height = log_2(N) + 1
    // max_nodes = 2^h - 1
    // if nodes count > 2^(h-1) then tree is efficient, 
    // because the number of nodes is more than can fit with a lesser height,
    // therefore the tree is already the minimum height
    if (!root_bst) return true;
    int nodes_count = count_nodes();
    int height = get_height();
    return (nodes_count >= pow(2, height-1));
    // return (height == log2(nodes_count) + 1);
}

void BST::display_all(){
    _display_all(root_bst, 1);
}

void BST::_display_all(node * root, int level){
    if (!root) return;
    cout << "level " << level << endl;
    root->term.display();
    _display_all(root->left, level + 1);
    _display_all(root->right, level + 1);
}

// Display all with names starting with characters within a given range
int BST::display_range(char min_val, char max_val){
    return _display_range(root_bst, min_val, max_val);
}

int BST::_display_range(node * root, char min_val, char max_val){
    if (!root) return 0;
    if (root->term.word[0] >= min_val){
        if (root->term.word[0] <= max_val){
            root->term.display();
        } _display_range(root->left, min_val, max_val);
    } _display_range(root->right, min_val, max_val);
    return 1;
}
