// Implementing a queue with arrays

/*
#include <stdlib.h>

typedef struct queue{
	int capacity;
	int front;
	int num;
	int *arr;
} queue;


// Initialize queue with its capacity
// Input: Size of the queue
// Side-Effects: Allocates memory for the new queue struct and the array
// Output: Pointer to the new queue
queue *initQueue(int size){
	queue* newQ = (queue*)malloc(sizeof(queue));
	newQ->capacity = size;
	newQ->arr = (int*)malloc(sizeof(int)*size);
	newQ->front = 0;
	newQ->num = 0;
	return newQ;
}

// Check if queue is full
// Input: Pointer to queue
// Side-Effects: none
// Output: 1 if queue is full. 0 if not full.
int isFull(queue *q){
	if (q->num == q->capacity)
		return 1;
	else
		return 0;
}

// Check if queue is empty
// Input: Pointer to queue
// Side-Effects: none
// Output: 1 if queue is empty. 0 if not empty.
int isEmpty(queue *q){
	if (q->num == 0)
		return 1;
	else return 0;
}

// Add a value to the queue
// Input: Pointer to queue, value to add
// Side-Effects: Value is added to the queue
// Output: 1 if successful, 0 if failed (queue full)
int enQueue(queue *q, int val){
	// if full return 0
	if (isFull(q))
		return 0;
	else { // else queue up val
		q->arr[(q->front + q->num) % q->capacity] = val;
		q->num++;
		return 1;
	}
}

// Remove a value from the queue
// Input: Pointer to queue
// Side-Effects: Front position of the queue is adjusted. Num queue elements decremented
// Output: 1 if successfully removed. 0 if failed (queue empty)
int deQueue(queue *q){
	if (isEmpty(q))
		return 0;
	else {
		q->front++;
		q->num--;
		return 1;
	}
}

// Return front value from the queue
// Input: Pointer to queue
// Side-Effects: None
// Output: Value at the front of the queue
int peek(queue *q){
	if (isEmpty(q))
		return 0; // throw an error actually
	else {
		return q->arr[q->front];
	}
}

void main(){
	/* TEST CODE
	queue *q = initQueue(5);
	enQueue(q, 5);
	enQueue(q, 4);
	enQueue(q, 3);
	deQueue(q);
	deQueue(q);
	peek(q);
	enQueue(q, 2);
	deQueue(q);
	peek(q);
	
}
*/
