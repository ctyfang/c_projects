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

// Input: none
// Side-Effects: Removes root, replaces it with highest index item, heapifies down
// Output: root value
int removeMin(minHeap *heap) {
	int rtValue = heap->arr[0];
	int newRtVal = heap->arr[heap->numItems - 1];
	heap->arr[heap->numItems - 1] = 0;
	heap->numItems--;
	int ind = 0;
	heap->arr[ind] = newRtVal;
	int leftChild = heap->arr[ind * 2 + 1], rightChild = heap->arr[ind * 2 + 2];

	// Heapify down
	while (newRtVal > leftChild || newRtVal > rightChild) {
		if (newRtVal > leftChild && newRtVal > rightChild) {
			if (leftChild < rightChild) {
				heap->arr[ind] = leftChild;
				heap->arr[ind * 2 + 1] = newRtVal;
				ind = ind * 2 + 1;
			}
			else {
				heap->arr[ind] = rightChild;
				heap->arr[ind * 2 + 2] = newRtVal;
				ind = ind * 2 + 2;
			}
		}
		else if (newRtVal > leftChild) {
			heap->arr[ind] = leftChild;
			heap->arr[ind * 2 + 1] = newRtVal;
			ind = ind * 2 + 1;
		}
		else {
			heap->arr[ind] = rightChild;
			heap->arr[ind * 2 + 2] = newRtVal;
			ind = ind * 2 + 2; 
		}
		leftChild = heap->arr[ind * 2 + 1];
		rightChild = heap->arr[ind * 2 + 2];
	}
	return rtValue;
}

// Input: pointer to heap, value
// Side-Effects: insert value at the last position, percolate it upwards iteratively
// Output: none
void insertMinHeap(minHeap *heap, int val) {
	int ind = heap->numItems, parentInd = heap->numItems / 2, temp;
	
	if(heap->numItems +1 <= heap->capacity)
		heap->arr[heap->numItems] = val;
	else {
		resizeMinHeap(heap);
		heap->arr[heap->numItems] = val;
	}

	if(ind != 0) {
		// Heapify up
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
// Side-Effect: percolate one step up, and call heapifyMin again, or return
// Notes: This is a helper function. Interface lies in recursiveInsert
void heapifyMin(minHeap *heap, int ind) {
	if (ind == 0)
		return;
	else {
		int parentInd = ind / 2, temp;

		// Swap with parent if less than it
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

void heapifyMaxArr(int arr[], int size, int ind) {
	// if left child ind < sizeof(arr) 
	//		compare values with arr[ind] and swap if needed
	//		heapifyMax(arr, size, leftChild)
	// if right child ind < sizeof(arr)
	//		compare values with arr[ind] and swap if needed
	//		heapifyMax(arr, size, rightChild)
	int leftInd = ind * 2 + 1, rightInd = ind * 2 + 2, maxInd;
	int temp;

	if (leftInd < size && arr[leftInd] > arr[ind])
		maxInd = leftInd;
	else
		maxInd = ind;

	if (rightInd < size && arr[rightInd] > arr[maxInd])
		maxInd = rightInd;

	if (maxInd != ind) {
		temp = arr[maxInd];
		arr[maxInd] = arr[ind];
		arr[ind] = temp;
		heapifyMaxArr(arr, size, maxInd);
	}
	else {
		return;
	}
	// check if swap is needed with right
}


void buildHeap(int arr[], int size) {
	int i, ind = (size - 1) / 2;

	for (i = ind;  i >= 0; i--) {
		heapifyMaxArr(arr, size, i);
	}
}

int removeRoot(int arr[], int size) {
	// replace root with last leaf
	int root = arr[0];
	arr[0] = arr[size - 1];
	size--;

	// heapify down
	heapifyMaxArr(arr, size, 0);
	return root;
}
int *heapSort(int arr[], int size) {
	buildHeap(arr, size);
	int *sortedArr = (int*)malloc(sizeof(int)*size);
	int i;

	for (i = 0; i < size; i++) {
		sortedArr[i] = removeRoot(arr, size-i);
	}

	return sortedArr;
}
void main() {
	/*
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

	//removeMin(minH);
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
	*/

	int nums[] = {7,27,96,48,58,23,21,76,87,44};
	int *sorted = heapSort(nums, 10);
	int i;
	for (i = 0; i < 10; i++) {
		printf("%i, ", sorted[i]);
	}
	printf("\n");
	system("PAUSE");
}

