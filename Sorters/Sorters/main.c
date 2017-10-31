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
void selection_sort(int arr[], int size) {
	//int sortedArr = (int*)malloc(sizeof(int)*size);
	int i, j, min, minInd, temp;
	
	// find min
	for (i = 0; i < size - 1; i++) {
		min = arr[i];
		minInd = i;
		for (j = i + 1; j < size; j++) {
			if (arr[j] < min) {
				minInd = j;
				min = arr[j];
			}
		}
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
void main() {
	int arr[] = { 5,4,3,2,1 };

	//selection_sort(arr, 5);
	//insertion_sort(arr, 5);
	//bubble_sort(arr, 5);
}