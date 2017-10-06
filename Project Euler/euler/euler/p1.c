#include <stdio.h>
#include <math.h>

// Find the sum of multiples of 3 or 5 below 1000
#define MAX_NUM 1000;

int p1() {
	int sum = 0;
	int i;
	
	for (i = 1; i < 1000; i++) {
		if (!(i % 3))
			sum += i;
		else if (!(i % 5))
			sum += i;
	}

	return sum;
}

#define FIB_LIM 4000000
// Determine the sum of all even fibonacci numbers whose value < 4e6
int p2(){
	int last = 3, last_last = 2, curr = last + last_last, sum=2;
	
	while (curr < FIB_LIM) {
		if (!(curr % 2))
			sum += curr;
		last_last = last;
		last = curr;
		
		curr = last + last_last;
	}

	return sum;
}

#define ERATO_LIM 600851475143
// Determine largest prime factor of lim using Sieve of Eratosthenes
long long p3() {
	unsigned long lim = floor(sqrt(ERATO_LIM));
	unsigned long curr = lim;
	unsigned long curr_facts = 0, i, found = 0;

	while (!found && curr >1) {
		curr--;
		unsigned long x = ERATO_LIM % curr;
		if (x == 0) {
			for (i = 2; i < curr; i++) {
				if (curr%i == 0) break;
			}

			if (i == curr)
				found = 1;
		}
		
	}

	return curr;
}

int isPalindrome(num) {
	int num_digits = 0;
	int iterator = num, curr_digit, i;

	// Create data structure for digits
	while (iterator != 0) {
		num_digits++;
		iterator /= 10;
	}

	int* digits = (int*)malloc(sizeof(int)*num_digits);

	// Store digits in dynamically array
	iterator = num;
	for(i=0; i<num_digits; i++) {
		curr_digit = iterator % 10;
		*(digits + i) = curr_digit;
		iterator /= 10;
	}

	// Check for palindrome
	for (i = 0; i < num_digits/2; i++) {
		if (*(digits + i) != *(digits + num_digits - 1 - i))
			break;
	}

	// Free memory allocated for data structure
	free(digits);


	// Return conclusion
	if (i == num_digits / 2)
		return 1;
	else
		return 0;
}
// Largest palindrome made by the product of two 3-digit numbers
int p4() {
	int i, j, prod_curr;
	int lim = 999;
	int prod_sofar = 0;

	for (i = 100; i <= lim; i++) {
		for (j = 100; j <= lim; j++) {
			prod_curr = i*j;

			if (isPalindrome(prod_curr)) {
				if (prod_curr > prod_sofar)
					prod_sofar = prod_curr;
			}
		}
	}

	return prod_sofar;
}
// Find smallest number that is divisible by all nums from 1-20
int p5() {
	int curr = 20, i;

	while (1) {
		curr++;

		for (i = 2; i <= 20; i++) {
			if (curr%i != 0)
				break;
		}

		if (i == 21)
			break;
	}

	return curr;
}

// Find smallest prime where replacing part of the digits (not nec. adjacent) yields 8 prime value family
int p6() {
	while (1) {
		//Find next prime

		//Replace digits
			//Increment replacement digit
				//Reposition replacement digits
				
				//Count number of primes
			//If primes == 8  break
	}
}

int p7() {
	int a, b, c;
	int i, j, k;
	int found = 0;

	for (i = 1; i <= 1000; i++) {
		for (j = 1; j <= 1000; j++) {
			a = i;
			b = j;
			k = pow(a, 2) + pow(b, 2);
			c = 1000 - a - b;
			if (pow(c, 2) == k) {
				found = 1;
				break;
			}

		}
		if (found)
			break;
	}

	return a*b*c;
	
}
void main() {
	int ans = p7();
	printf("%i", ans);
}