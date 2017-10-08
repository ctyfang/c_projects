// Intro to Hash Tables

/*
Hashtables help implement a dictionary datatype, i.e. an associative arrray. In these datatypes,
FIND operations execute in O(1), like in regular arrays, but the keys/indices don't have to be integers

Hash functions map non-integer keys to integer values, which we can use to access their location in the table.
A "collision" is when two keys get hashed to the same integer value - this is addressed using one of two methods.

The chaining approach is where you store a linked list at each table location.
Runtime is no longer equal in all cases due to the storage of more than one key at a location. We define
overload factor alpha as n/m, where n= number of keys, m= number of locations. Describes probability
of a key not being found immediately after hash table access.

The open address approach is where each key gets its own location. If the hash function produces
the same location, we walk through the table until we find an empty spot. This "walk" is called the
probing sequence, and as long as this sequence is unchanged, we'll be able to find the key again.
The overload factor in this case is <1, contrary to chaining, since we'll always have more locations than keys
(require excess keys to perform the probe).

Hash functions
*/

#include <stdlib.h>
#include <stdio.h>
#define HASHSIZE 60
#define MAGICNUMBER 65

typedef struct hashEntry{
	char* key;
	struct hashEntry *next;
	int val;
}hashEntry;

hashEntry *createDict();
hashEntry *insertKey(hashEntry*, char);
hashEntry *containsKey(hashEntry*, char);
int getVal(hashEntry*, char key);
int getLoc(hashEntry*, char key);
//int hash(char* key);

hashEntry *createDict()
{
	hashEntry *table = (hashEntry*)malloc(sizeof(hashEntry)*HASHSIZE);
	int i;

	for (i = 0; i < HASHSIZE; i++) {
		(table + i)->next = NULL;
		(table + i)->val = 0;
		(table + i)->key = NULL;
	}

	return table;
}

hashEntry *containsKey(hashEntry* table, char key)
{

	int index = hash(key), found = 0;
	if (key == ' ')
		index = 59;
	hashEntry* currEntry = (table+index);

	while (currEntry != NULL) {
		if (currEntry->key == key)
			return 1;

		currEntry = currEntry->next;
	}

	return 0;
}

hashEntry *insertKey(hashEntry* table, char key)
{
	int index = hash(key);
	if (key == ' ')
		index = 59;
	hashEntry* currEntry = (table + index), *newEntry;

	while (currEntry->next != NULL) {
		currEntry = currEntry->next;
	}

	if (currEntry->key == NULL) {
		currEntry->key = key;
		newEntry = currEntry;
	}
	else {
		newEntry = (hashEntry*)malloc(sizeof(hashEntry));

		if (!newEntry) {
			printf("Could not allocate memory for entry.\n");
			return NULL;
		}

		newEntry->key = key;
		newEntry->val = 0;
		newEntry->next = NULL;
	}

	return newEntry;
}

int getLoc(hashEntry* table, char key) {
	int index = hash(key);
	if (key == ' ')
		index = 59;
	hashEntry* currEntry = (table + index);

	while (currEntry->key != key) {
		currEntry = currEntry->next;
	}

	return currEntry;
}

int getVal(hashEntry* table, char key) {
	hashEntry* entry = getLoc(table, key);
	return entry->val;
}

int hash(char key) {

	return (key - MAGICNUMBER) % HASHSIZE;
}

void main() {
	FILE* filepointer;
	char* filename = "sample.txt", currChar;

	fopen_s(&filepointer, filename, "r");

	if (!filepointer) {
		printf("Could not open file.\n");
		return;
	}

	hashEntry* hashTab = createDict();
	hashEntry* entry = NULL;
	currChar = fgetc(filepointer);
	while (currChar != EOF) {
		if (containsKey(hashTab, currChar)) {
			entry = getLoc(hashTab, currChar);
			entry->val++;
		} 
		else {
			entry = insertKey(hashTab, currChar);
			entry->val = entry->val + 1;
		}
		currChar = fgetc(filepointer);
	}
	printf("Done reading.\n");

	int i,val;

	for (i = MAGICNUMBER; i < (MAGICNUMBER + HASHSIZE); i++) {
		if (containsKey(hashTab, (char)i)) {
			val = getVal(hashTab, (char)i);
			printf("%c = %i\n", (char)i, val);
		}
	}
	printf("Done.");
}