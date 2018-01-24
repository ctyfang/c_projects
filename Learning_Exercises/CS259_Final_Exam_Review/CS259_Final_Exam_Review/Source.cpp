#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hashtableopen.h"

#define _CRT_SECURE_NO_WARNINGS

// generate an array of items (may contain duplicates)
void generateItems(int arr[], int num, int maxnum)
{
	int numgenerated = 0;
	int value;
	while (numgenerated < num)
	{
		value = rand() % maxnum;
		arr[numgenerated] = value;
		numgenerated++;
	}
}

void main()
{
	// global variables setup
	const int maxvalue = 2000; // maximum value of randomly generated number
	const int numvalues = 1500; // number of values to generate
	const int htcapacity = 1000; // initial hash table capacity, will become a prime number
	const int numitemstoinsert = 700; // try changing this to affect the load factor (but don't go too far above htcapacity)
									  // try it in the range of around 300 to 1000

									  //int valuesarray[numvalues]; // array of generated values
	int valuesarray[1500]; // array of generated values

	int i; // a loop variable

		   // Hash table variables, each with a different probe scheme
	HashTableOpen htlinear;
	HashTableOpen htquadratic;
	HashTableOpen htdouble;

	// variables for analytics
	int probecount;
	double loadfactorlinear = 0;
	int numlinearsuccess = 0;
	int numlinearfailure = 0;
	double avgprobeslinearsuccess = 0;
	double avgprobeslinearfailure = 0;
	double loadfactorquadratic = 0;
	int numquadraticsuccess = 0;
	int numquadraticfailure = 0;
	double avgprobesquadraticsuccess = 0;
	double avgprobesquadraticfailure = 0;
	double loadfactordouble = 0;
	int numdoublesuccess = 0;
	int numdoublefailure = 0;
	double avgprobesdoublesuccess = 0;
	double avgprobesdoublefailure = 0;

	srand((unsigned int)time(NULL));
	printf("Generating values for insert/search...\n");
	generateItems(valuesarray, numvalues, maxvalue);

	// Initialization of each hashtable sets size to 0, create the status table, key table
	printf("Initializing linear probing table...\n");
	initializeHashTable(&htlinear, htcapacity, LINEARPROBE);
	printf("Initializing quadratic probing table...\n");
	initializeHashTable(&htquadratic, htcapacity, QUADRATICPROBE);
	printf("Initializing double hashing table...\n");
	initializeHashTable(&htdouble, htcapacity, DOUBLEHASH);

	printf("Inserting items into hash tables...\n");
	// insert items into the tables (some may fail!)
	for (i = 0; i < numitemstoinsert; i++)
	{
		insert(&htlinear, valuesarray[i]);
		insert(&htquadratic, valuesarray[i]);
		insert(&htdouble, valuesarray[i]);
	}

	printf("Performing searches...\n");
	// perform searches for analysis
	// Search for each key
	for (i = numitemstoinsert; i < numvalues; i++)
	{
		// search in the linear probing table
		if (search(&htlinear, valuesarray[i], &probecount))
		{
			numlinearsuccess++;
			avgprobeslinearsuccess += (double)probecount;
		}
		else
		{
			numlinearfailure++;
			avgprobeslinearfailure += (double)probecount;
		}
		// search in the quadratic probing table
		if (search(&htquadratic, valuesarray[i], &probecount))
		{
			numquadraticsuccess++;
			avgprobesquadraticsuccess += (double)probecount;
		}
		else
		{
			numquadraticfailure++;
			avgprobesquadraticfailure += (double)probecount;
		}
		// search in the double hashing table
		if (search(&htdouble, valuesarray[i], &probecount))
		{
			numdoublesuccess++;
			avgprobesdoublesuccess += (double)probecount;
		}
		else
		{
			numdoublefailure++;
			avgprobesdoublefailure += (double)probecount;
		}
	}
	// complete the analytics and print results
	printf("Insertions and searches complete.\n");
	printf("Computing analytics...\n\n");
	avgprobeslinearsuccess = avgprobeslinearsuccess / (double)numlinearsuccess;
	avgprobeslinearfailure = avgprobeslinearfailure / (double)numlinearfailure;
	avgprobesquadraticsuccess = avgprobesquadraticsuccess / (double)numquadraticsuccess;
	avgprobesquadraticfailure = avgprobesquadraticfailure / (double)numquadraticfailure;
	avgprobesdoublesuccess = avgprobesdoublesuccess / (double)numdoublesuccess;
	avgprobesdoublefailure = avgprobesdoublefailure / (double)numdoublefailure;
	loadfactorlinear = (double)htlinear.size / (double)htlinear.capacity;
	loadfactorquadratic = (double)htquadratic.size / (double)htquadratic.capacity;
	loadfactordouble = (double)htdouble.size / (double)htdouble.capacity;

	printf("Linear probing:\n---------------\n");
	printf("Load factor: %f\n", loadfactorlinear);
	printf("Number of successful searches: %d\n", numlinearsuccess);
	printf("Average number of probes per successful search: %f\n", avgprobeslinearsuccess);
	printf("Number of failed searches: %d\n", numlinearfailure);
	printf("Average number of probes per failed search: %f\n\n", avgprobeslinearfailure);

	printf("Quadratic probing:\n---------------\n");
	printf("Load factor: %f\n", loadfactorquadratic);
	printf("Number of successful searches: %d\n", numquadraticsuccess);
	printf("Average number of probes per successful search: %f\n", avgprobesquadraticsuccess);
	printf("Number of failed searches: %d\n", numquadraticfailure);
	printf("Average number of probes per failed search: %f\n\n", avgprobesquadraticfailure);

	printf("Double hashing:\n---------------\n");
	printf("Load factor: %f\n", loadfactordouble);
	printf("Number of successful searches: %d\n", numdoublesuccess);
	printf("Average number of probes per successful search: %f\n", avgprobesdoublesuccess);
	printf("Number of failed searches: %d\n", numdoublefailure);
	printf("Average number of probes per failed search: %f\n\n", avgprobesdoublefailure);

	system("pause");
}