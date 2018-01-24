// File:        hashtableopen.h
// Author:      Geoffrey Tien
// Date:        2017-11-30
// Description: Definitions for an open-addressing hash table
//              Whether linear probing, quadratic probing, or double
//              hashing is used as the collision resolution scheme
//              is specified during initialization.
//              Note that removal has NOT been implemented,
//              and the insertion method implemented here does not
//              scan over tombstones looking for duplicates before
//              inserting (it should fail if any duplicate exists)
//              Warning - this code is not guaranteed to be bug-free!
//              Use at your own peril...

#ifndef _HASHTABLEOPEN_H_
#define _HASHTABLEOPEN_H_

#include <stdlib.h>

// macros for collision resolution scheme
#define LINEARPROBE 1
#define QUADRATICPROBE 2
#define DOUBLEHASH 3

// macros for cell status
#define STATUSFREE 0
#define STATUSREMOVED 1
#define STATUSOCCUPIED 2

#define TRUE 1
#define FALSE 0

typedef struct HashTableOpen
{
  int size;
  int capacity;
  int* keytable;    // stores the key values
  int* statustable; // stores the free/occupied/removed status
  int probescheme;  // linear probing, quadratic probing, or double hashing
} HashTableOpen;

// Initializes the member attributes of ht
// PARAM: initcapacity, capacity will be set to the first
//        prime number at least as large as initcapacity
// PARAM: method, determines the collision resolution scheme
//        used in this open addressing hash table
void initializeHashTable(HashTableOpen* ht, int initcapacity, int method);

// Destroys any dynamic memory associated with ht
void destroyHashTable(HashTableOpen* ht);

// Checks whether a number x is a prime number
// Returns TRUE if yes, FALSE otherwise
int isPrime(int x);

// Returns the smallest prime number at least as large as x
int smallestPrime(int x);

// primary hash function for determining the initial index
int h1(HashTableOpen* ht, int key);

// secondary hash function used to determine gap for double hashing
int h2(HashTableOpen* ht, int key);

// inserts the key into ht
// Returns TRUE if successful
// Returns FALSE if key exists or if unable to insert
//   after ht->capacity number of probes
int insert(HashTableOpen* ht, int key);

// searches the hash table for the requested key
// Returns TRUE if the key is found
// Returns FALSE if key is not found after at most ht->capacity probes
//   or if a free space is found while probing
// PARAM: count will be (initialized and) updated with the number of probes
//        performed
int search(HashTableOpen* ht, int key, int* count);

#endif