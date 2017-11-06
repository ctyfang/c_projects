#include <stdlib.h>
#include <stdio.h>


// STRUCTS ---------------
typedef struct minHeap {
	int capacity;
	int numItems;
	int *arr;
} minHeap;

typedef struct maxHeap {
	int capacity;
	int numItems;
	int *arr;
} maxHeap;

// FUNCTION PROTOTYPES ----------
minHeap *initMinHeap(int);
maxHeap *initMaxHeap(int);
void insertMaxHeap(maxHeap*, int);
void recursiveInsertMax(maxHeap*, int);
void heapifyMax(maxHeap*, int);

void insertMinHeap(minHeap*, int);
void recursiveInsertMin(minHeap*, int);
void heapifyMin(minHeap*, int);

// Input: pointer to heap
// Side-Effect: Double the size of the heap, copy elements over
void resizeMinHeap(minHeap* heap) {
	int newCapacity = heap->capacity * 2;
	int *newArr = (int*)malloc(sizeof(int)*newCapacity);
	int i;

	for (i = 0; i < heap->capacity; i++) {
		newArr[i] = heap->arr[i];
	}
	
	free(heap->arr);
	heap->arr = newArr;
}

// Input: capacity
// Side-Effects: allocate memory for heap parameters and the actual heap (array)
// Output: pointer to allocated heap structure
minHeap *initMinHeap(int capacity) {
	minHeap *heap = (minHeap*)malloc(sizeof(minHeap));
	heap->capacity = capacity;
	heap->numItems = 0;
	heap->arr = (int*)malloc(sizeof(int)*capacity);

	return heap;
}

// Input: pointer to heap, value
// Side-Effects: insert value at the last position, percolate it upwards iteratively
// Output: none
void insertMinHeap(minHeap *heap, int val) {
	int ind = heap->numItems, parentInd = heap->numItems / 2, temp;
	
	if(heap->numItems <= heap->capacity)
		heap->arr[heap->numItems] = val;
	else {
		resizeMinHeap(heap);
		heap->arr[heap->numItems] = val;
	}

	if(ind != 0) {
		while (heap->arr[ind] < heap->arr[parentInd] && parentInd >= 0) {
			temp = heap->arr[ind];
			heap->arr[ind] = heap->arr[parentInd];
			heap->arr[parentInd] = temp;
			
			if (parentInd == 0) {
				parentInd = -1;
			}
			else {
				ind = parentInd;
				parentInd = ind / 2;
			}
		}
	}
	heap->numItems++;
}

// Input: pointer to heap, current index of inserted value
// Side-Effect: percolate one step up, or return
// Notes: This is a helper function. Interface lies in recursiveInsert
void heapifyMin(minHeap *heap, int ind) {
	if (ind == 0)
		return;
	else {
		int parentInd = ind / 2, temp;

		if (heap->arr[ind] < heap->arr[parentInd]) {
			temp = heap->arr[ind];
			heap->arr[ind] = heap->arr[parentInd];
			heap->arr[parentInd] = temp;
			ind = parentInd;

			heapifyMin(heap, ind);
		}
		else 
			return;
		
	}
}

// Input: pointer to heap, value to be inserted
// Side-Effect: insert value at the last position, initiate recursive call to insert
// Notes: requires helper function heapifyMin
void recursiveInsertMin(minHeap *heap, int val) {
	if(heap->numItems <= heap->capacity)
		heap->arr[heap->numItems] = val;
	else {
		resizeMinHeap(heap);
		heap->arr[heap->numItems] = val;
	}

	heapifyMin(heap, heap->numItems);
	heap->numItems++;
}

maxHeap *initMaxHeap(int capacity) {
	maxHeap *heap = (maxHeap*)malloc(sizeof(maxHeap));
	heap->capacity = capacity;
	heap->numItems = 0;
	heap->arr = (int*)malloc(sizeof(int)*capacity);

	return heap;
}

// Input: pointer to heap
// Side-Effect: Double the size of the heap, copy elements over
void resizeMaxHeap(maxHeap* heap) {
	int newCapacity = heap->capacity * 2;
	int *newArr = (int*)malloc(sizeof(int)*newCapacity);
	int i;

	for (i = 0; i < heap->capacity; i++) {
		newArr[i] = heap->arr[i];
	}

	free(heap->arr);
	heap->arr = newArr;
}

void insertMaxHeap(maxHeap *heap, int val) {
	int ind = heap->numItems, parentInd = heap->numItems / 2, temp;
	
	if(heap->numItems <= heap->capacity)
		heap->arr[ind] = val;
	else {
		resizeMaxHeap(heap);
		heap->arr[ind] = val;
	}

	if (ind != 0) {
		while (heap->arr[ind] > heap->arr[parentInd] && parentInd >= 0) {
			temp = heap->arr[ind];
			heap->arr[ind] = heap->arr[parentInd];
			heap->arr[parentInd] = temp;

			if (parentInd == 0) {
				parentInd = -1;
			}
			else {
				ind = parentInd;
				parentInd = ind / 2;
			}
		}
	}
	heap->numItems++;
}

void heapifyMax(maxHeap *heap, int ind) {
	if (ind == 0)
		return;
	else{
		int parentInd = ind / 2, temp;

		if(heap->arr[ind] > heap->arr[parentInd]){
			temp = heap->arr[ind];
			heap->arr[ind] = heap->arr[parentInd];
			heap->arr[parentInd] = temp;
			ind = parentInd;

			heapifyMax(heap, ind);
		}
	}
}

void recursiveInsertMax(maxHeap *heap, int val) {
	if (heap->numItems <= heap->capacity)
		heap->arr[heap->numItems] = val;
	else {
		resizeMaxHeap(heap);
		heap->arr[heap->numItems] = val;
	}

	heapifyMax(heap, heap->numItems);
	heap->numItems++;
}

void main() {
	int nums[] = { 34, 76, 11, 32, 73, 9, 50, 65, 41, 27, 3, 88 };
	int k = 12;

	maxHeap *maxH = initMaxHeap(12);

	minHeap *minH = initMinHeap(12);


	// First insertion is always O(1)
	// Beyond that, worst case is O(logn)
	// Therefore total complexity of n insertions should be O(nlogn-c) -> O(nlogn)
	int i;
	for (i = 0; i < k; i++) {
		//insertMinHeap(minH, nums[i]);
		recursiveInsertMin(minH, nums[i]);
		//insertMaxHeap(maxH, nums[i]);
		recursiveInsertMax(maxH, nums[i]);
	}

	printf("MIN HEAP:\n");
	for (i = 0; i < k; i++){
		printf("%i, ", minH->arr[i]);
	}
	printf("\n");

	printf("MAX HEAP:\n");
	for (i = 0; i < k; i++) {
		printf("%i, ", maxH->arr[i]);
	}
	printf("\n");

	system("PAUSE");
}

