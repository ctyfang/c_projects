#include <stdlib.h>

/*
struct stack {
	int topInd;
	int capacity;
	int* arr;
};

struct stack* createStack(int capacity) {
	struct stack *storage = (struct stack*)malloc(sizeof(struct stack));
	storage->capacity = capacity;

	return storage;
}
struct stack* initStack(struct stack* storage) {
	storage->topInd = -1;
	storage->arr = (int*)malloc(storage->capacity * sizeof(int));

	return storage;
}

int isEmpty(struct stack* storage) {
	if (storage->topInd == -1)
		return 1;
	else
		return 0;
}

int isFull(struct stack* storage) {
	if (storage->topInd == (storage->capacity - 1))
		return 1;
	else
		return 0;
}

int push(struct stack* storage, int val) {
	if (isFull(storage))
		return 0;
	else {
		storage->topInd = storage->topInd + 1;
		storage->arr[storage->topInd] = val;
		return 1;
	}
}

int pop(struct stack* storage) {
	if (isEmpty(storage))
		return 0;
	else {
		int retVal = storage->arr[storage->topInd];
		storage->arr[storage->topInd] = 0;
		storage->topInd--;
		return retVal;
	}
}


void main() {
	//struct stack* storage = (struct stack*)malloc(sizeof(struct stack));
	struct stack* storage = createStack(5);
	storage = initStack(storage);
	push(storage, 2);
	push(storage, 5);
	pop(storage);
	pop(storage);
}
*/