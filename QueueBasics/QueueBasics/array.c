#include <stdlib.h>
/*
typedef struct queue{
	int capacity;
	int front;
	int num;
	int *arr;
} queue;

queue *initQueue(int size){
	queue* newQ = (queue*)malloc(sizeof(queue));
	newQ->capacity = size;
	newQ->arr = (int*)malloc(sizeof(int)*size);
	newQ->front = 0;
	newQ->num = 0;
	return newQ;
}

int isFull(queue *q){
	if (q->num == q->capacity)
		return 1;
	else
		return 0;
}

int isEmpty(queue *q){
	if (q->num == 0)
		return 1;
	else return 0;
}

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

int deQueue(queue *q){
	if (isEmpty(q))
		return 0;
	else {
		q->front++;
		q->num--;
		return 1;
	}
}

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
