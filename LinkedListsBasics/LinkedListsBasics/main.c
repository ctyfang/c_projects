#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node;

node *createList() {
	return NULL;
}

node *createNode(int val) {
	node *newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;
	newNode->val = val;
	return newNode;
}

node *insertNode(node *newNode, node *list) {
	node *curr = list, *next;
	if (curr == NULL)
		return newNode;

	while (curr->next != NULL) {
		curr = curr->next;
	}

	curr->next = newNode;
	return list;
}

node *findNode(int val, node *list) {
	node *curr = list;
	if (curr == NULL)
		return NULL;
	else {
		while (curr != NULL) {
			if (curr->val == val)
				return curr;
		}
		return NULL;
	}
}

node *removeNode(int val, node *list) {
	node *last = list, *curr = list, *next;

	if (findNode(val, list)) {
		while (curr != NULL) {
			if (curr->val == val) {
				if (curr == list)
					list = curr->next;
				else {
					last->next = curr->next;
				}
				free(curr);
				return list;
			}
			last = curr;
			curr = curr->next;
		}
	}
	else
		return list;
}

void main(void) {
	node *n1 = createNode(5);
	node *n2 = createNode(4);
	node *n3 = createNode(3);

	node *list = createList();
	list = insertNode(n1, list);
	list = insertNode(n2, list);
	list = insertNode(n3, list);
	list = removeNode(5, list);
}