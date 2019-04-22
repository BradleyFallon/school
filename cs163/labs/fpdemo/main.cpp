#include "table.h"

int main()
{
    node * root = NULL;
    node * root_2 = NULL;
    build(root);
    display(root);

    /*  PLACE YOUR FUNCTION CALL HERE */
    cout << "Total sum of all nodes: " << copy(root, root_2) << endl;
    cout << "The overall average of the tree is: " << get_average(root) << endl;

    display(root_2);

    return 0;
}

// copy and return the sum of all values
int copy(node * root_src, node * & root_dst){

    if (!root_src){
        root_dst = NULL;
        return 0;
    }
    root_dst = new node;
    root_dst->data = root_src->data;
    return root_src->data + copy(root_src->left, root_dst->left) + copy(root_src->right, root_dst->right);
}


float get_average(node * root){
	float avg = 0.0;
	int count = 0;

	// if no items, cannot get average. Also, can't div by 0.
	count = count_nodes(root);
	if (!count) return avg;

	avg = get_sum(root) / count;
	return avg;
}

int get_sum(node * root){
	if (!root) return 0;
	return root->data + get_sum(root->left) + get_sum(root->right);
}
int count_nodes(node * root){
	if (!root) return 0;
	return 1 + count_nodes(root->left) + count_nodes(root->right);
}

