//list.h
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct node
{
    int data;
    node * left;
    node * right;;
};

void build(node * & root);  //supplied
void display(node *  root); //supplied

/* ************** PLACE YOUR PROTOTYPE HERE ***************** */

int copy(node * root_src, node * & root_dst);
 
float get_average(node * root);  
int get_sum(node * root);
int count_nodes(node * root);
