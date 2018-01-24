// recursive fibonacci
// recursive functions consist of two or more cases
// i) base case, and
// ii) recursive base
int fib(int num) {
	if (num <= 0)
		return 0;
	else if (num == 1)
		return 1;
	else {
		return fib(num - 1) + fib(num - 2);
	}

}

// single bubblesort pass
void singleBubble(int *arr, int size) {
	int j, temp;

	for (j = 0; j < size - 1; j++) {
		if (arr[j] > arr[j + 1]) {
			temp = arr[j + 1];
			arr[j + 1] = arr[j];
			arr[j] = temp;
		}
	}
}

// bubble sort using recursion
// base case: swap two items
// recursive case: call bubble sort again
void bubbleSort(int *arr, int size) {
	if (size == 1)
		return;
	else {
		singleBubble(arr, size);
		bubbleSort(arr, size - 1);
	}
}

// basic bubble sort using for loops
void basicBubble(int *arr, int size) {
	int i,j, temp;
	int count = 0;

	for (i = 0; i < size-1; i++) {
		count = 0;
		for (j = 0; j < size-1; j++) {
			if (arr[j] > arr[j + 1]) {
				count++;
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
		if (!count)
			break;
	}
}

// recursive implementation of linear search
// checks each element, re-dos search with lesser array size
int linSearch(int *arr, int size, int val) {
	if (size == 0)
		return 0;
	else if (arr[size-1] == val)
		return 1;
	else
		linSearch(arr, size-1, val);
}

void main() {
	int arr[4] = { 4,3,2,1 };

	//basicBubble(arr, 4);
	//bubbleSort(arr, 4);
	//fib(2);
	linSearch(arr, 4, 4);
}