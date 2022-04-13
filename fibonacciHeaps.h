#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include "graphs.h"
using namespace std;

//structure to represent a node in the heap
struct node {
	node* parent; // parent pointer
	node* child; // pointer to the child
	node* left; // left pointer
	node* right; // right pointer
	int key; // vertex value/name
	int degree; // degree of the node
	char mark; // Black or white mark of the node, unmarked->white marked->black
	char c; 
    int dist;//the minimum distance of node from src
};
//capacity of the heap
int capacity;
// min pointer as "mini"
struct node* mini = NULL;

//number of nodes in the heap
int no_of_nodes = 0;

//  insert a node in heap
node* insertion(int val,int dist)
{
	struct node* new_node = new node();
	new_node->key = val;
    new_node->dist = dist;
	new_node->degree = 0;
	new_node->mark = 'W';
	new_node->c = 'N';
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->left = new_node;
	new_node->right = new_node;
	if (mini != NULL) {
		(mini->left)->right = new_node;
		new_node->right = mini;
		new_node->left = mini->left;
		mini->left = new_node;
		if (new_node->dist < mini->dist)
			mini = new_node;
	}
	else {
		mini = new_node;
	}
	no_of_nodes++;
    return new_node;
}
// link heap nodes in parent child relationship,make the child as one which has larger distance value
void Fibonnaci_link(struct node* ptr2, struct node* ptr1)
{
	(ptr2->left)->right = ptr2->right;
	(ptr2->right)->left = ptr2->left;
	if (ptr1->right == ptr1)
		mini = ptr1;
	ptr2->left = ptr2;
	ptr2->right = ptr2;
	ptr2->parent = ptr1;
	if (ptr1->child == NULL)
		ptr1->child = ptr2;
	ptr2->right = ptr1->child;
	ptr2->left = (ptr1->child)->left;
	((ptr1->child)->left)->right = ptr2;
	(ptr1->child)->left = ptr2;
	if (ptr2->dist < (ptr1->child)->dist)
		ptr1->child = ptr2;
	ptr1->degree++;
}
// merges heap after extraction or deletion
void mergeHeapsAfterExtraction()
{
	int temp1;
	float temp2 = (log(no_of_nodes)) / (log(2));
	int temp3 = temp2;
	struct node* arr[temp3+1];
	for (int i = 0; i <= temp3; i++)
		arr[i] = NULL;
	node* ptr1 = mini;
	node* ptr2;
	node* ptr3;
	node* ptr4 = ptr1;
	do {
		ptr4 = ptr4->right;
		temp1 = ptr1->degree;
		while (arr[temp1] != NULL) {
			ptr2 = arr[temp1];
			if (ptr1->dist > ptr2->dist) {
				ptr3 = ptr1;
				ptr1 = ptr2;
				ptr2 = ptr3;
			}
			if (ptr2 == mini)
				mini = ptr1;
			Fibonnaci_link(ptr2, ptr1);
			if (ptr1->right == ptr1)
				mini = ptr1;
			arr[temp1] = NULL;
			temp1++;
		}
		arr[temp1] = ptr1;
		ptr1 = ptr1->right;
	} while (ptr1 != mini);
	mini = NULL;
	for (int j = 0; j <= temp3; j++) {
		if (arr[j] != NULL) {
			arr[j]->left = arr[j];
			arr[j]->right = arr[j];
			if (mini != NULL) {
				(mini->left)->right = arr[j];
				arr[j]->right = mini;
				arr[j]->left = mini->left;
				mini->left = arr[j];
				if (arr[j]->dist < mini->dist)
					mini = arr[j];
			}
			else {
				mini = arr[j];
			}
			if (mini == NULL)
				mini = arr[j];
			else if (arr[j]->dist < mini->dist)
				mini = arr[j];
		}
	}
}

//  extract minimum node in the heap
void Extract_min()
{ 
	if (mini == NULL)
		cout << "The heap is empty" << endl;
	else {
		node* temp = mini;
		node* pntr;
		pntr = temp;
		node* x = NULL;
		if (temp->child != NULL) {

			x = temp->child;
			do {
				pntr = x->right;
				(mini->left)->right = x;
				x->right = mini;
				x->left = mini->left;
				mini->left = x;
				if (x->dist < mini->dist)
					mini = x;
				x->parent = NULL;
				x = pntr;
			} while (pntr != temp->child);
		}
		(temp->left)->right = temp->right;
		(temp->right)->left = temp->left;
		mini = temp->right;
		if (temp == temp->right && temp->child == NULL)
			mini = NULL;
		else {
			mini = temp->right;
			mergeHeapsAfterExtraction();
		}
		no_of_nodes--;
	}
}

// place the node from tree to the root list
void Cut(struct node* found, struct node* temp)
{
	if (found == found->right)
		temp->child = NULL;

	(found->left)->right = found->right;
	(found->right)->left = found->left;
	if (found == temp->child)
		temp->child = found->right;

	temp->degree = temp->degree - 1;
	found->right = found;
	found->left = found;
	(mini->left)->right = found;
	found->right = mini;
	found->left = mini->left;
	mini->left = found;
	found->parent = NULL;
	found->mark = 'B';
}

// marking after a node is removed from its place
void mark_cut(struct node* temp)
{
	node* ptr5 = temp->parent;
	if (ptr5 != NULL) {
		if (temp->mark == 'W') {
			temp->mark = 'B';
		}
		else {
			Cut(temp, ptr5);
			mark_cut(ptr5);
		}
	}
}

//  decrease the value of a node in the heap
void Decrease_key(struct node* found, int val)
{
	if (mini == NULL)
		cout << "The Heap is Empty!!!" << endl;

	if (found == NULL)
		cout << "Node not found in the Heap" << endl;

	found->dist = val;

	struct node* temp = found->parent;
	if (temp != NULL && found->dist < temp->dist) {
		Cut(found, temp);
		mark_cut(temp);
	}
	if (found->dist < mini->dist)
		mini = found;
}

// findAndDecreaseNode the given node and decrease if founf
void findAndDecreaseNode(struct node* mini, int old_val, int val)
{
	struct node* found = NULL;
	node* temp5 = mini;
	temp5->c = 'Y';
	node* found_ptr = NULL;
	if (temp5->dist == old_val) {
		found_ptr = temp5;
		temp5->c = 'N';
		found = found_ptr;
		Decrease_key(found, val);
	}
	if (found_ptr == NULL) {
		if (temp5->child != NULL)
			findAndDecreaseNode(temp5->child, old_val, val);
		if ((temp5->right)->c != 'Y')
			findAndDecreaseNode(temp5->right, old_val, val);
	}
	temp5->c = 'N';
	found = found_ptr;
}


