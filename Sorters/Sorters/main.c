#include <stdlib.h>

// Find the minimum of a given array
int findMin(int arr[], int size) {
	int i, min = arr[0];
	for (i = 1; i < size; i++) {
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}

// Selection Sort
// Complexity: O(n^2)
// Pros: Performs better when auxiliary memory is limited
// Cons: Inefficient on large lists
// n(n-1)/2 comparisons. First pass is n, second is n-1, then n-2... 
void selection_sort(int arr[], int size) {
	//int sortedArr = (int*)malloc(sizeof(int)*size);
	int i, j, min, minInd, temp;
	
	// find min
	for (i = 0; i < size - 1; i++) {
		// find min
		min = arr[i];
		minInd = i;
		for (j = i + 1; j < size; j++) {
			if (arr[j] < min) {
				minInd = j;
				min = arr[j];
			}
		}
		// swap with current index
		temp = arr[i];
		arr[i] = arr[minInd];
		arr[minInd] = temp;
	}
}

// Insertion Sort
// Complexity : O(n^2)
// Pros: O(n) for small data sets. Requires constant amount of memory space.
// Cons: O(n^2) in worst case.
void insertion_sort(int arr[], int size) {
	int i, j, temp;

	for (i = 1; i < size; i++) {
		temp = arr[i];
		j = i;
		while (temp < arr[j - 1] && j > 0) {
			// shift left
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = temp;
	}

}

// Bubble Sort
// Complexity: O(n^2)
// Pros: Simple
// Cons: Slow and impractical for large data sets
void bubble_sort(int arr[], int size) {
	int i, j, temp;

	for (i = 0; i < size-1; i++) {
		for (j = 0; j < size-i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

// Heap Sort Helper Functions ------------------

// Input: Array to-be heapified, size of head, index of root
// Side-Effect: Recursively heapify the tree rooted at index
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

// Input: Array to-be heapified, size of the array
// Side-Effects: Build heap from an array
void buildHeap(int arr[], int size) {
	int i, ind = (size - 1) / 2;

	for (i = ind; i >= 0; i--) {
		heapifyMaxArr(arr, size, i);
	}
}

// Input: Heap, size of heap
// Side-Effect: Remove root, re-heapify the array
// Return: Root value
int removeRoot(int arr[], int size) {
	// replace root with last leaf
	int root = arr[0];
	arr[0] = arr[size - 1];
	size--;

	// heapify down
	heapifyMaxArr(arr, size, 0);
	return root;
}

// Heap sort
// Complexity: O(nlogn)
void heap_sort(int arr[], int size) {
	buildHeap(arr, size);
	int *sortedArr = (int*)malloc(sizeof(int)*size);
	int i;

	for (i = 0; i < size; i++) {
		sortedArr[i] = removeRoot(arr, size - i);
	}

	for (i = 0; i < size; i++) {
		arr[i] = sortedArr[i];
	}
}

void main() {
	int arr[] = { 1,2,3,4,5 };

	//selection_sort(arr, 5);
	//insertion_sort(arr, 5);
	//bubble_sort(arr, 5);
	heap_sort(arr, 5);

	system("PAUSE");
	return;
}