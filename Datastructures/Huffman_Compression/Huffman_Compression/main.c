/*
Description:
Simple implementation of Huffman Compression. Assumes that the file contains only characters
from ASCII 32-122.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for Hash Table - Based on ASCII range
#define HASHSIZE 91
#define MAGICNUMBER 32
#define MAXLETCOUNT 999

// Structs for tree nodes and hash table entries
typedef struct node {
	int val;
	char key;
	struct node *zero;
	struct node *one;
}node;

typedef struct hashEntry {
	char* key;
	struct hashEntry *next;
	int val;
}hashEntry;

// COMPRESSION function proto
void huffCompress(node*, char*);
// TREE functions protos
node* insertNode(int);
node* findNode(int);
node* dltNode(int);
node *root = NULL;

// HASHTABLE function protos
hashEntry *createDict();
hashEntry *insertKey(hashEntry*, char);
hashEntry *containsKey(hashEntry*, char);
int getVal(hashEntry*, char key);
hashEntry *getLoc(hashEntry*, char key);
int hash(char key);

// TREE functions
/*
desc: Insert new node into global tree
in: Value of new node
out: Pointer to new node
*/
node* insertNode(int val) {
	node* currNode = root, *parent = root, **nextPtr = &root;
	node* newNode = (node*)malloc(sizeof(node));
	newNode->zero = NULL;
	newNode->one = NULL;
	newNode->val = val;

	while (currNode != NULL) {
		//parent = currNode;
		if (val > currNode->val) {
			nextPtr = &(currNode->one);
			currNode = currNode->one;
		}
		else {
			nextPtr = &(currNode->zero);
			currNode = currNode->zero;
		}
	}

	*nextPtr = newNode;
}

/*
desc: Find node in the tree, given value
in: Value of node
out: Pointer to node
*/
node* findNode(int val) {
	node* currNode = root;

	while (currNode != NULL) {
		if (currNode->val == val)
			return currNode;
		else {
			if (val > currNode->val)
				currNode = currNode->one;
			else
				currNode = currNode->zero;
		}
	}

	return NULL;
}

/*
desc: Free node from global tree given value
in: Value of node
out: Pointer to node's parent
*/
node* dltNode(int val) {
	node *currNode = root, *parent = root;

	if (!findNode(val)) {
		printf("Node not found in tree.\n");
		return NULL;
	}

	while (currNode != NULL) {
		if (currNode->val == val) {
			free(currNode);
			currNode = NULL;
			break;
		}
		else {
			parent = currNode;
			if (val > currNode->val)
				currNode = currNode->one;
			else
				currNode = currNode->zero;
		}
	}
	return parent;
}

// HASHTABLE functions
/*
desc: Generate new hashtable
in: n/a
out: Pointer to head of the hashtable
*/
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

/*
desc: Check if key is contained in the table
in: pointer to table, key char
out: pointer to entry if contained, else null
*/
hashEntry *containsKey(hashEntry* table, char key)
{

	int index = hash(key), found = 0;
	hashEntry* currEntry = (table + index);

	while (currEntry != NULL) {
		if (currEntry->key == key)
			return 1;

		currEntry = currEntry->next;
	}

	return 0;
}

/*
desc: Insert new key into table, assumed does not currently exist
in: pointer to table, key char
out: pointer to new entry
*/
hashEntry *insertKey(hashEntry* table, char key)
{
	int index = hash(key);
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

/*
desc: Find entry for a given key in the hash table
in: Pointer to table, and key char
out: Pointer to new node
*/
hashEntry* getLoc(hashEntry* table, char key) {
	int index = hash(key);
	hashEntry* currEntry = (table + index);

	while (currEntry->key != key) {
		currEntry = currEntry->next;
	}

	return currEntry;
}

/*
desc: Get val from entry, given key
in: pointer to table and key char
out: value for that key
*/
int getVal(hashEntry* table, char key) {
	hashEntry* entry = getLoc(table, key);
	return entry->val;
}

/*
desc: Map key char to an integer index for hashtable
in: char key
out: index, based on ascii range supported
*/
int hash(char key) {
	return (key - MAGICNUMBER) % HASHSIZE;
}

// Linked list for nodes
typedef struct listItem {
	node* node;
	struct listitem* next;
}listItem;

listItem* head = NULL;

/*
desc: Using binary tree passed in, compress the text file and write to new file
in: tree and filepath
out: none. Side-effect: write compressed text file to new location.
*/
void huffCompress(node *tree, char* filename) {
	FILE *filepointer = NULL, *writepointer = NULL;
	char* newfile = "comp_file.bin";
	char currChar;
	//strcpy(newfile, filename);
	//strcat(newfile, "_comp");

	fopen_s(&filepointer, filename, "r");
	if (!filepointer) {
		printf("Couldn't open file for reading.\n");
		return;
	}

	fopen_s(&writepointer, newfile, "wb");
	if (!writepointer) {
		printf("Couldn't create new file.\n");
		return;
	}

	currChar = fgetc(filepointer);
	while (currChar != EOF) {
		
		currChar = fgetc(filepointer);
	}
}
void main() {
	// Count letters, store in hash table -----------

	// Open file for reading
	FILE* filepointer = NULL;
	char* filename = "sample.txt";

	fopen_s(&filepointer, filename, "r");
	if (!filepointer) {
		printf("Could not open file.\n");
		return;
	}

	// Read file, store letter counts
	hashEntry* table = createDict(), *currEntry = NULL;
	int numEntries = 0;
	char currChar = fgetc(filepointer);
	while (currChar != EOF) {
		if (containsKey(table, currChar)) {
			currEntry = getLoc(table, currChar);
		}
		else {
			currEntry = insertKey(table, currChar);
			numEntries++;
		}
		currEntry->val = currEntry->val + 1;
		currChar = fgetc(filepointer);
	}
	fclose(filepointer);

	// Generate tree node for each letter and linked list of nodes ----------------
	int i, index, nodeCount = 0;
	node *indivNodes = (node*)malloc(sizeof(node)*numEntries);
	node *currNode = NULL;
	listItem *currItem = head;
	for (i = 0; i < HASHSIZE; i++) {
		if(((table + i)->val)>0){
			currItem = head;
			currNode = (node*)malloc(sizeof(node));
			currNode->key = (table + i)->key;
			currNode->val = (table + i)->val;

			if (currItem == NULL) {
				head = (listItem*)malloc(sizeof(listItem));
				currItem = head;
			}
			else {
				while (currItem->next) {
					currItem = currItem->next;
				}
				currItem->next = (listItem*)malloc(sizeof(listItem));
				currItem = currItem->next;
				/*
				indivNodes[nodeCount].key = (char)(i + MAGICNUMBER);
				indivNodes[nodeCount].val = getVal(table, (char)(i + MAGICNUMBER));
				nodeCount++;
				*/
			}
			currItem->node = currNode;
			currItem->next = NULL;
		}
	}

	//printf("Linked list of nodes generated.\n");
	// Print letter counts
	/*
	for (i = 0; i < numEntries; i++) {
		node currNode = *(indivNodes+i);
		printf("%c = %i\n", currNode.key, currNode.val);
	}
	*/

	currItem = head;
	char currKey;
	int currVal;
	while (currItem != NULL) {
		currKey = currItem->node->key;
		currVal = currItem->node->val;
		printf("%c = %i\n", currKey, currVal);
		currItem = currItem->next;
	}

	// Build tree using nodes -------------------------------
	int numItems = numEntries;
	node *minA=NULL,*minB=NULL, *newParent, *newChildA, *newChildB;
	listItem *prevItem=NULL, *minItemA=NULL, *minItemB=NULL;
	int minAval, minBval;

	while (numItems != 1) {
		// Find lowest item in list
		minAval = MAXLETCOUNT, minBval = MAXLETCOUNT;
		currItem = head;
		for (i = 0; i < numItems; i++) {
			if (currItem->node->val < minAval) {
				minItemA = currItem;
				minAval = currItem->node->val;
			}
			currItem = currItem->next;
		}

		currItem = head;
		for (i = 0; i < numItems; i++) {
			if (currItem->node->val < minBval) {
				if (currItem == minItemA) {
					currItem = currItem->next;
					continue;
				}
				minItemB = currItem;
				minBval = currItem->node->val;
			}
			currItem = currItem->next;
		}
		/*
		minAval = MAXLETCOUNT, minBval = MAXLETCOUNT;
		for (i = 0; i < numEntries; i++) {
			currNode = (indivNodes + i);
			if (!(currNode->key) && !(currNode->zero) && !(currNode->one))
				continue;
			if (currNode->val < minAval) {
				minA = currNode;
				minAval = currNode->val;
			}
		}

		// Find second lowest
		for (i = 0; i < numEntries; i++) {
			currNode = (indivNodes + i);
			if (!currNode)
				continue;
			if (currNode->val < minBval) {
				if (currNode == minA)
					continue;
				else {
					minB = currNode;
					minBval = currNode->val;
				}
			}
		}
		*/

		// Create parent node
		node *newNode = (node*)malloc(sizeof(node));
		newChildA = (node*)malloc(sizeof(node));
		memcpy(newChildA, minItemA->node, sizeof(node));
		newChildB = (node*)malloc(sizeof(node));
		memcpy(newChildB, minItemB->node, sizeof(node));

		free(minItemA->node);
		free(minItemB->node);
		newNode->key = '\0';
		newNode->zero = newChildA;
		newNode->one = newChildB;
		newNode->val = minAval + minBval;

		// Free item B
		prevItem = head;
		currItem = head;
		while (currItem != minItemB) {
			prevItem = currItem;
			currItem = currItem->next;
		}

		if (prevItem == currItem) { // If item B is the head of the list..
			head = currItem->next;
			free(currItem); 
		}
		else {
			prevItem->next = currItem->next;
			free(currItem);
		}
		minItemA->node = newNode;

		/*
		minA->val = minBval + minAval;
		minA->zero = newChildA;
		minA->one = newChildB;
		minA->key = NULL;
		minB->key = NULL;
		*/
		numItems--;
	}
	// Save tree, free hashtable
	free(table);
	printf("Tree successfully generated.\n");
	node *tree = head->node;
	free(head);

	// Compress data using the tree
	huffCompress(tree, filename);
}