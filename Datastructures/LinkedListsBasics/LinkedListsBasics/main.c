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

int subList(node *l1, node *l2) {
	node *curr = l2;
	//node *curr2 = l2;
	
	if (l1 == NULL)
		return 1;
	else if (l2 == NULL)
		return 0;
	else {
		int found = 0;
		while (curr != NULL) {
			if (curr->val == l1->val) {
				found = 1;
				break;
			}
			curr = curr->next;
		}

		return found && subList(l1->next, l2);
	}
}
void main(void) {
	node *n1 = createNode(5);
	node *n2 = createNode(4);
	node *n3 = createNode(3);
	node *n4 = createNode(5);
	node *n5 = createNode(4);
	node *n6 = createNode(2);

	node *list = createList();
	list = insertNode(n1, list);
	list = insertNode(n2, list);
	list = insertNode(n3, list);
	//list = removeNode(5, list);

	node *list2 = createList();
	list2 = insertNode(n4, list2);
	list2 = insertNode(n5, list2);
	list2 = insertNode(n6, list2);

	int x = subList(list, list2);
}