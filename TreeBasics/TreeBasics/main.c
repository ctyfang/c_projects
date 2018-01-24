// TREE BASICS
// Every node in this tree will have a max of two children. It will be a binary tree.
#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct node {
	int val;
	struct node *zero;
	struct node *one;
}node;

node* createTree(void);
node* insertNode(node*, int);
node* findNode(node*, int);
int traverse(node);
void dltNode(node*, int);

node *createTree(void) {
	return NULL;
}

node *createNode(int val) {
	node *newNode = malloc(sizeof(node));
	newNode->zero = NULL;
	newNode->one = NULL;
	newNode->val = val;
	return newNode;
}

// Traversal methods visit every node in a tree recursively
// Each traversal method has its own applications, considering that the tree is structured
void visit(node *nd) {
	printf("%i\n", nd->val);
}

// Traverse from left -> right
void inOrder(node *tree) {
	if (tree != NULL) {
		inOrder(tree->zero);
		visit(tree);
		inOrder(tree->one);
	}
}

// Traverse from top -> bottom. First node to be visited is ROOT
void preOrder(node *tree) {
	if (tree != NULL) {
		visit(tree);
		preOrder(tree->zero);
		preOrder(tree->one);
	}
}

// Traverse from bottom -> top. Last node to be visited is ROOT
void postOrder(node *tree) {
	if (tree != NULL) {
		postOrder(tree->zero);
		postOrder(tree->one);
		visit(tree);
	}
}

// As the tree becomes more balanced, insertion, search, removal is in O(logn) time
// Worst case is O(n)
node* recursiveInsert(node *root, int val) {
	node *newNode;
	// If given an empty tree, new node is now the tree
	if (root == NULL) {
		node* newNode = (node*)malloc(sizeof(node));
		newNode->zero = NULL;
		newNode->one = NULL;
		newNode->val = val;
		return newNode;
	}
	// Otherwise, find it's correct position
	else {
		if (val > root->val) {
			if (root->one != NULL)
				recursiveInsert(root->one, val);
			else
				root->one = createNode(val);
		}
		else {
			if (root->zero != NULL)
				recursiveInsert(root->zero, val);
			else
				root->zero = createNode(val);
		}
	}
}

node* insertNode(node *root, int val) {
	// Create new node
	node* currNode = root, *parent = root, **nextPtr = &root;
	node* newNode = (node*)malloc(sizeof(node));
	newNode->zero = NULL;
	newNode->one = NULL;
	newNode->val = val;

	// Find its correct position in the tree
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
	return root;
}

// Searches the ordered binary tree for a value
// Value can either be found, or not found (reached null)
int recursiveFind(node *nd, int val) {
	if (nd == NULL)
		return 0;
	else if (nd->val == val)
		return 1;
	else {
		if (val > nd->val)
			recursiveFind(nd->one, val);
		else
			recursiveFind(nd->zero, val);
	}
}

// Iterative implementation of search
node *findNode(node *root, int val) {
	node* currNode = root;
	
	// Search until we hit null or until the value is found
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

void dltNode(node *root, int val) {
	node *currNode = root, *parent = root, *successor;
	int isLeft;

	if (!findNode(root, val)) {
		printf("Node not found in tree.\n");
		return NULL;
	}

	// Find the position of the node
	// Ignore case of root.
	while (currNode != NULL && currNode->val != val) {
		parent = currNode;
		if (val < currNode->val) {
			currNode = currNode->zero;
			isLeft = TRUE;
		}
		else {
			currNode = currNode->one;
			isLeft = FALSE;
		}
	}

	// Out of the loop
	if (currNode == NULL)
		return;
	else {
		// Only left child
		if (currNode->zero != NULL && currNode->one == NULL) {
			if (isLeft == TRUE) {
				parent->zero = currNode->zero;
			}
			else {
				parent->one = currNode->zero;
			}
			free(currNode);
			return;
		}
		// Only right child
		else if (currNode->zero == NULL && currNode->one != NULL) {
			if (isLeft == TRUE) {
				parent->zero = currNode->one;
			}
			else {
				parent->one = currNode->one;
			}
			free(currNode);
			return;
		}
		// Both
		else if (currNode->zero != NULL && currNode->one != NULL){
			// find predecessor in LEFT subtree
			node *succ = currNode->zero, *succp;

			while (succ != NULL) {
				succp = succ;
				succ = succ->one;
			}

			// fix links at predecessor
			int temp = succ->val;
			// assumes unique values in the tree
			dltNode(root, temp);

			// replace node with predecessor. No need to free currNode because we replaced its value.
			currNode->val = temp;
			return;
		}
		else { // Otherwise no children
			if (isLeft == TRUE) {
				parent->zero = NULL;
			}
			else {
				parent->one = NULL;
			}
			free(currNode);
			return;
		}
	}
}

// Compact recursive implementation of find
int recursiveFind2(node *nd, int val) {
	if (nd == NULL)
		return FALSE;
	else if (nd->val == val)
		return TRUE;
	else
		return recursiveFind2(nd->zero, val) || recursiveFind2(nd->one, val);
}

void main() {
	node *root = createTree();
	root = recursiveInsert(root, 3);
	recursiveInsert(root, 5);
	recursiveInsert(root, 2);
	recursiveInsert(root, 7);
	recursiveInsert(root, 1);
	recursiveInsert(root, 10);
	recursiveInsert(root, 6);
	recursiveFind2(root, 5);
	dltNode(root, 3);
	/*
	root = insertNode(root, 3);
	insertNode(root, 1);
	insertNode(root, 5);
	insertNode(root, 10);
	insertNode(root, 6);
	*/
	inOrder(root);
	//findNode(3);
	//dltNode(3);
}