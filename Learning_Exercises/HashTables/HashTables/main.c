#include <math.h>
#include <stdlib.h>
#include <stdio.h>
// Hash Functions need to be fast, deterministic, uniform
// FAST - constant time, usually single division
// DETERMINISTIC - same input, same output
// UNIFORM - distribute data uniformly over the table. Hash function generates each value
//			 in the output range with equal probability. Holds for universe of all possible vals
// If hash function uses modulo, make table size the first prime > 2*number of expected values

// Overload factor, lambda, is defined as number of entries / table size
// As lambda approaches 0.5, probability of collision becomes quite high

// Checks if a given number is prime
int isPrime(double num) {
	int i;
	
	for (i = 2; i <= sqrt(num); i++) {
		if (fmod(num, i) == 0)
			return 0;
	}

	return 1;
}

// Find first prime number larger than twice the expected number of entries
int calcTableSize(double numEntries) {
	double size = 2 * numEntries + 1;
	int primeCheck = isPrime(size);

	while (primeCheck == 0) {
		size++;
		primeCheck = isPrime(size);
	}
	
	return size;
}

double hornerFactor(char *string) {
	int len = strlen(string);
	int i;
	double sum = string[0];

	for (i = 1; i < len; i++) {
		sum *= 256;
		sum += string[len];
	}
	
	return sum;
}
int hashFunction(int num) {
	return num % 23;
}

int insertLinProbe(int *table, int num) {
	int index = hashFunction(num);

	while (table[index] != 0) {
		index++;
	}
	printf("Inserted %i at index %i\n", num, index);
	table[index] = num;
}

int insertQuadProbe(int *table, int num) {
	int index = hashFunction(num);
	int p = 1;

	while (table[index] != 0) {
		index += pow(p, 2);
		p++;
	}
	printf("Inserted %i at index %i\n", num, index);
	table[index] = num;
}

int secondHash(int num) {
	int p = 5;
	return p - (num % p);
}

int insertDoubleHash(int *table, int num) {
	int index = hashFunction(num);

	while (table[index] != 0) {
		index += secondHash(num);
	}
	printf("Inserted %i at index %i\n", num, index);
	table[index] = num;
}
void main() {
	double numEntries = 11;
	int *hashTable = (int*)calloc(calcTableSize(numEntries), sizeof(int));
	int numbers[] = { 29, 32, 58, 21, 81};
	int numLen = 5;

	int i;
	for (i = 0; i < numLen; i++) {
		insertDoubleHash(hashTable, numbers[i]);
	}

	system("PAUSE");
	return;
}