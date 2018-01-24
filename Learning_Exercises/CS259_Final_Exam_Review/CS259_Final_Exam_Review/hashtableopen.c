// File:        hashtableopen.c
// Author:      Geoffrey Tien
// Date:        2017-11-30
// Description: Implementation for an open-addressing hash table

#include "hashtableopen.h"

// Initializes the member attributes of ht
// PARAM: initcapacity, capacity will be set to the first
//        prime number at least as large as initcapacity
// PARAM: method, determines the collision resolution scheme
//        used in this open addressing hash table
void initializeHashTable(HashTableOpen* ht, int initcapacity, int method)
{
  int i;
  ht->size = 0; // initially has no elements
  ht->capacity = smallestPrime(initcapacity);
  ht->keytable = (int*) malloc(ht->capacity * sizeof(int)); // one key table contains the actual keys
  ht->statustable = (int*) malloc(ht->capacity * sizeof(int)); // one table contains occupied, free, or removed
  for (i = 0; i < ht->capacity; i++)
  {
    ht->statustable[i] = STATUSFREE; // Fill status table with STATUSFREE
  }
  ht->probescheme = method;
}

// Destroys any dynamic memory associated with ht
void destroyHashTable(HashTableOpen* ht)
{
  free(ht->keytable);
  free(ht->statustable);
}

// Checks whether a number x is a prime number
// Returns TRUE if yes, FALSE otherwise
int isPrime(int x)
{
  int mod;
  int prime = TRUE;
  int i = 2; // start testing divisibility from the number 2
  while (prime && (i * i <= x))
  {
    mod = x % i;
    if (mod == 0)
      prime = FALSE;
    i++;
  }
  return prime;
}

// Returns the smallest prime number at least as large as x
int smallestPrime(int x)
{
  int result = x;
  // optimization: only odd numbers can be prime
  if (result % 2 == 0)
    result++; // make result an odd number
  while (!isPrime(result))
    result += 2;
  return result;
}

// primary hash function for determining the initial index
// We will use h1(x) = (17 * x) % capacity
int h1(HashTableOpen* ht, int key)
{
  return (17 * key) % ht->capacity;
}

// secondary hash function used to determine gap for double hashing
// We will use h2(x) = 11 - (x % 11)
int h2(HashTableOpen* ht, int key)
{
  return 11 - (key % ht->capacity);
}

// inserts the key into ht
// Returns TRUE if successful
// Returns FALSE if key exists or if unable to insert
//   after ht->capacity number of probes
int insert(HashTableOpen* ht, int key)
{
  int numprobes = 0;
  int startindex = h1(ht, key);
  int insertionindex = startindex;
  int doublehashoffset = h2(ht, key);
  // find the insertion index, based on probing scheme
  while (ht->statustable[insertionindex] == STATUSOCCUPIED)
  {
    // return if duplicate or too many probes
    if (ht->keytable[insertionindex] == key || numprobes > ht->capacity)
      return FALSE;
    else
    {
      numprobes++;
      switch (ht->probescheme)
      {
        case LINEARPROBE:
          insertionindex = (startindex + numprobes) % ht->capacity;
          break;
        case QUADRATICPROBE:
          insertionindex = (startindex + (numprobes * numprobes)) % ht->capacity;
          break;
        case DOUBLEHASH:
          insertionindex = (startindex + (numprobes * doublehashoffset)) % ht->capacity;
          break;
      }
    }
  }
  // If we have reached this point without returning due to failure,
  // we can insert the item
  // Note that this does not account for duplicates which may appear
  // beyond any tombstones encountered
  ht->keytable[insertionindex] = key;
  ht->statustable[insertionindex] = STATUSOCCUPIED;
  ht->size += 1;
  return TRUE;
}

// searches the hash table for the requested key
// Returns TRUE if the key is found
// Returns FALSE if key is not found after at most ht->capacity probes
//   or if a free space is found while probing
// PARAM: count will be (initialized and) updated with the number of probes
//        performed
int search(HashTableOpen* ht, int key, int* count)
{
  int numprobes = 0;
  int startindex = h1(ht, key);
  int searchindex = startindex;
  int doublehashoffset = h2(ht, key);
  while ((ht->statustable[searchindex] == STATUSOCCUPIED || ht->statustable[searchindex] == STATUSREMOVED )
          && numprobes <= ht->capacity)
  {
    // return TRUE if found
    if (ht->statustable[searchindex] == STATUSOCCUPIED && ht->keytable[searchindex] == key)
    {
      *count = numprobes;
      return TRUE;
    }
    // otherwise continue probing
    numprobes++;
    switch (ht->probescheme)
    {
      case LINEARPROBE:
        searchindex = (startindex + numprobes) % ht->capacity;
        break;
      case QUADRATICPROBE:
        searchindex = (startindex + (numprobes * numprobes)) % ht->capacity;
        break;
      case DOUBLEHASH:
        searchindex = (startindex + (numprobes * doublehashoffset)) % ht->capacity;
        break;
    }
  }
  // If we reach this point without returning due to success,
  // we have either made too many probes, or we have found a free space.
  // In either case, return FALSE
  *count = numprobes;
  return FALSE;
}