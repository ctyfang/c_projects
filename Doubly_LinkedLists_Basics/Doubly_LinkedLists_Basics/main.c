#include <stdlib.h>

typedef struct node {
	char* artist;
	char* songName;
	struct node* prev;
	struct node* next;
}node;


node *createNewList();
node *createNode(char*, char*);
node *insertNth(node*, node*, int);
node *deleteNth(node*, int);
node *findSongByName(node*, char*);
//node *findSongByArtist(node*, char*);

node *createNewList() {
	return NULL;
}

node *createNode(char* artist, char* songName) {
	node *newNode = (node*)malloc(sizeof(node));
	newNode->artist = artist;
	newNode->songName = songName;
	newNode->next = NULL;
	return newNode;
}

node *insertNth(node* nodeInsert, node* list, int pos) {
	int i;
	node *curr = list, *prev = NULL;

	for (i = 1; i < pos; i++) {
		if (curr == NULL) {
			return NULL;
		}
		prev = curr;
		curr = curr->next;
	}

	if (prev != NULL)
		prev->next = nodeInsert;
	else
		list = nodeInsert;

	nodeInsert->next = curr;
	return list;
	// return new head
}

node *deleteNth(node* list, int pos) {
	int i;
	node *curr = list, *prev = NULL;

	for (i = 1; i < pos; i++) {
		if (curr == NULL) {
			return NULL;
		}
		prev = curr;
		curr = curr->next;
	}

	node *next = curr->next;
	// Prev node exist?
	if (prev != NULL) {
		prev->next = curr->next;
		// Next node exist?
		if (next != NULL)
			next->prev = prev;
	}
	else {
		if (curr->next != NULL)
			curr->next->prev = NULL;
		list = curr->next;
	}

	free(curr);
	curr = NULL;
	return list;
}

node *findSongByName(node *list, char* songName) {
	node *curr = list;

	while (curr != NULL) {
		if (!strcmp(curr->songName, songName))
			return curr;
		curr = curr->next;
	}
	return NULL;
}

void main() {
	node *list = createNewList();
	list = createNode("Linkin Park", "Numb");
	node *n1 = createNode("John Mayer", "Why Georgia");
	node *n2 = createNode("John Mayer", "No Such Thing");

	list = insertNth(n1, list, 1);
	list = insertNth(n2, list, 3);
	list = deleteNth(list, 1);
	list = deleteNth(list, 2);
}