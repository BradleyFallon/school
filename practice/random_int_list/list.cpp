#include <stdlib.h>
#include<iostream>

using namespace std;

struct node{
	node * next;
	int data;
};

void build_list(node * & head){
	node * new_node;
	node * current;
	int i;
	
	head = new node;
	head->next = NULL;
	head->data = rand() % 100;
	cout << head->data << endl;
	
	current = head;

	for (i=0; i<rand() % 10 + 10; ++i){
		new_node = new node;
		new_node->next = NULL;
		current->next = new_node;
		current = new_node;
		current->data = rand() %100;
	}
}

void display_list(node * head){
	
	if (!head){
		cout << endl;	
		return;
	}	
	cout << head->data << "  ";
	display_list(head->next);
}

int main(){

	node * head;

	cout << head << endl;
	build_list(head);
	display_list(head);

	return 0;
}
