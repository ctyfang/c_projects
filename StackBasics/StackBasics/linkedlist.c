#include <stdlib.h>

typedef struct stnode {
	int val;
	struct stnode* next;
} stnode;

stnode *top = NULL;

void push(int val) {
	stnode *newNode = (stnode*)malloc(sizeof(stnode));

	newNode->val = val;
	newNode->next = top;
	top = newNode;
}

int pop() {
	int retVal = top->val;
	stnode *temp = top;
	top = top->next;
	free(temp);
	temp = NULL;
	return retVal;
}

void main() {
	push(5);
	push(2);
	pop();
	pop();
}