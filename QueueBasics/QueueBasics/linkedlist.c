// Implement a queue with a linked list


// LIBRARIES
#include <stdlib.h>

// STRUCT DEF
typedef struct queueItem {
	int val;
	struct queueItem *next;
} queueItem;

// FUNCTION DEF
// Create new queue
// Input: None
// Side-Effects: None
// Output: Pointer to empty queue
queueItem* createQueue() {
	return NULL;
}

int isEmpty(queueItem* q) {
	if (!q) return 1;
	else return 0;
}
// Add item to the queue
// Input: Pointer to the queue, value to be added
// Side-Effect: Allocate memory for new item, point old tail to new item, initialize item.
// Output: Pointer to front of the list if success. Null otherwise (no more memory)
queueItem *enqueue(queueItem *q, int val) {
	queueItem *newItem = (queueItem*)malloc(sizeof(queueItem));
	if (!newItem)
		return NULL;

	newItem->next = NULL;
	newItem->val = val;

	if (isEmpty(q)) return newItem;

	else {
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = newItem;
	}
	return q;
}

// Remove item from the queue
// Input: Pointer to the queue
// Side-Effect: Free current front item
// Output: Pointer to new front of the queue
queueItem *dequeue(queueItem *q) {
	queueItem *newQ = q->next;
	free(q);
	return newQ;
}

// Return value at the front
// Input: Pointer to the queue
// Side-Effect: None
// Output: Value at the front of the queue
int peek(queueItem *q) {
	return q->val;
}

// TEST FUNCTIONS
void main() {
	queueItem *q = createQueue();
	q = enqueue(q, 5);
	q = enqueue(q, 3);
	q = dequeue(q);
	peek(q);
}
