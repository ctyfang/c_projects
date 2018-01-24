#include <stdlib.h>

// Stack has a top index, capacity, and the actual array
struct stack {
	int topInd;
	int capacity;
	int* arr;
};

// Allocate memory for the stack structure
// Set capacity
struct stack* createStack(int capacity) {
	struct stack *storage = (struct stack*)malloc(sizeof(struct stack));
	storage->capacity = capacity;

	return storage;
}

// Initialize top index
// Allocate memory for the actual stack
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

// Re-allocation of memory is not in constant time, but in O(n)
int push(struct stack* storage, int val) {
	if (isFull(storage)) {
		storage->capacity *= 2;
		int *newArr = (int*)malloc(sizeof(int)*storage->capacity);
		int i;

		for (i = 0; i <= storage->topInd; i++) {
			newArr[i] = storage->arr[i];
		}
		free(storage->arr);
		storage->arr = newArr;
	}

	storage->topInd = storage->topInd + 1;
	storage->arr[storage->topInd] = val;
	return 1;
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
	struct stack* storage = createStack(1);
	storage = initStack(storage);
	push(storage, 2);
	push(storage, 5);
	pop(storage);
	pop(storage);
}
