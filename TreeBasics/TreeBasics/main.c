// TREE BASICS
// Every node in this tree will have a max of two children. It will be a binary tree.
#include <stdlib.h>
#include <stdio.h>
typedef struct node {
	int val;
	struct node *zero;
	struct node *one;
}node;

node* insertNode(int);
node* findNode(int);
node* dltNode(int);

node *root = NULL;

node* insertNode(int val) {
	node* currNode = root, *parent = root, **nextPtr = &root;
	node* newNode = (node*)malloc(sizeof(node));
	newNode->zero = NULL;
	newNode->one = NULL;
	newNode->val = val;

	while (currNode != NULL) {
		//parent = currNode;
		if (val > currNode->val) {
			nextPtr = &(currNode->one);
			currNode = currNode->one;
		}
		else {
			nextPtr = &(currNode->zero);
			currNode = currNode->zero;
		}
	}
	
	*nextPtr = newNode;
}

node* findNode(int val) {
	node* currNode = root;
	
	while (currNode != NULL) {
		if (currNode->val == val)
			return currNode;
		else {
			if (val > currNode->val)
				currNode = currNode->one;
			else
				currNode = currNode->zero;
		}
	}
	
	return NULL;
}

node* dltNode(int val) {
	node *currNode = root, *parent = root;

	if (!findNode(val)) {
		printf("Node not found in tree.\n");
		return NULL;
	}

	while (currNode != NULL) {
		if (currNode->val == val) {
			free(currNode);
			currNode = NULL;
			break;
		}
		else {
			parent = currNode;
			if (val > currNode->val)
				currNode = currNode->one;
			else
				currNode = currNode->zero;
		}
	}
	return parent;
}

void main() {
	insertNode(5);
	insertNode(10);
	insertNode(3);

	findNode(3);
	dltNode(3);
}