
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <assert.h>

// HIGHSCORES: 66

#define ROWS 20
#define COLS 50
char MAP[ROWS][COLS];
int snakeLen = 2;
int numNodes = 0;

// segment of snake
typedef struct bodySegments{
	char direction;
	int x, y;
	struct bodySegments* next;
}bodySegment;

bodySegment* head = NULL;
bodySegment* tail = NULL;

// turning node
typedef struct turnPoints{
	int x, y;
	char direction;
	struct turnPoints* next;
}turnPoint;

turnPoint* firstTurn = NULL;


void initMap() {
	int i, j;

	for (i = 0, j = 0; j < COLS; j++) {
		MAP[i][j] = '#';
	}
	for (i = ROWS-1, j = 0; j < COLS; j++) {
		MAP[i][j] = '#';
	}
	for (j = 0, i = 0; i < ROWS; i++) {
		MAP[i][j] = '#';
	}
	for (j = COLS-1, i = 0; i < ROWS; i++) {
		MAP[i][j] = '#';
	}
}

void drawMap() {
	int i, j;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			printf("%c", MAP[i][j]);
		}
		printf("\n");
	}
}

void initSnake() {

	head = (bodySegment*)malloc(sizeof(bodySegment));
	tail = (bodySegment*)malloc(sizeof(bodySegment));

	head->x = COLS / 2;
	head->y = ROWS / 2;
	head->direction = 'd';
	MAP[head->y][head->x] = '$';

	tail->x = head->x - 1;
	tail->y = head->y;
	tail->direction = 'd';
	MAP[tail->y][tail->x] = '$';

	head->next = tail;
	tail->next = NULL;
}

void incSnakeLen() {
	// Create new segment mirroring tail
	bodySegment* newSeg = (bodySegment*)malloc(sizeof(bodySegment));
	bodySegment* segPt = tail;
	newSeg->direction = tail->direction;
	newSeg->x = tail->x;
	newSeg->y = tail->y;
	newSeg->next = NULL;

	// Set new segment as new tail
	segPt->next = newSeg;
	tail = newSeg;

	// Offset new segment from tail
	switch (tail->direction) {
		case 's':
			(tail->y) = (tail->y) - 1;
			break;
		case 'w':
			(tail->y) = (tail->y) + 1;
			break;
		case 'd':
			(tail->x) = (tail->x) - 1;
			break;
		case 'a':
			(tail->x) = (tail->x) + 1;
			break;
	}
	
	snakeLen++;
}



void plantNode(char keyPressed) {
	turnPoint* newPt = (turnPoint*)malloc(sizeof(turnPoint));

	newPt->direction = keyPressed;
	newPt->x = head->x;
	newPt->y = head->y;
	newPt->next = NULL;

	turnPoint* currPt = firstTurn;

	if (currPt == NULL) {
		free(firstTurn);
		firstTurn = newPt;
	}
	else{
		while ((currPt->next) != NULL) {
			currPt = currPt->next;
		}

		currPt->next = newPt;
	}

	numNodes++;
}

int inSnake(x, y) {
	int i;
	bodySegment* currSeg = head;
	for (i = 0; i < snakeLen; i++) {
		if (currSeg->x == x && currSeg->y == y)
			return 1;
	}

	return 0;
}

int inBorder(x, y) {
	int left = 0;
	int right = COLS-1;
	int top = 0;
	int bottom = ROWS-1;

	if (x == left || x == right)
		return 1;
	else if (y == top || y == bottom)
		return 1;
	
	return 0;
}

void spawnFood() {
	int x, y;

	x = rand() % 50;
	y = rand() % 20;

	while (inSnake(x, y) || inBorder(x,y)) {
		x = rand() % 50;
		y = rand() % 20;
	}

	MAP[y][x] = 'O';
}

int checkCollision() {
	int i,x,y;
	bodySegment* currSeg = head,*compSeg = head;

	while(currSeg) {
		x = currSeg->x;
		y = currSeg->y;

		while(compSeg) {
			if (currSeg != compSeg) {
				if (x == compSeg->x && y == compSeg->y)
					return 1;
			}

			compSeg = compSeg->next;
		}
		currSeg = currSeg->next;
	}

	return 0;
}
int updateSnake() {
	int i, x, y, currNodes;
	char dir;
	bodySegment *currSeg = head, *tail1, *tail2;
	turnPoint *currPt, *lastPt;
	currNodes = numNodes;

	// Iterate through body segments
	while (currSeg != NULL) {
		currPt = firstTurn;
		lastPt = NULL;
		x = currSeg->x;
		y = currSeg->y;
		MAP[y][x] = '\0';
		dir = currSeg->direction;

		// Increment position based on previous directional input
		switch (dir) {
		case 's':
			(currSeg->y) = (currSeg->y) + 1;
			break;
		case 'w':
			(currSeg->y) = (currSeg->y) - 1;
			break;
		case 'd':
			(currSeg->x) = (currSeg->x) + 1;
			break;
		case 'a':
			(currSeg->x) = (currSeg->x) - 1;
			break;
		default:
			break;
		}

		// If curr segment is head, check if snake is eating
		if (currSeg == head) {
			// If eating, update length
			if (MAP[currSeg->y][currSeg->x] == 'O') {
				tail1 = tail;
				incSnakeLen();
				tail2 = tail;
				assert(tail1 != tail2);
			}
		}

		// Check if out-of-bounds
		if (inBorder(currSeg->x, currSeg->y)) {
			if (currSeg->x == 0)
				currSeg->x = COLS - 2;
			else if (currSeg->x == 49)
				currSeg->x = 1;
			else if (currSeg->y == 0)
				currSeg->y = ROWS - 2;
			else
				currSeg->y = 1;
		}
		
		if (checkCollision()) {
			return 0;
		}

		// Move outside ?
		// Iterate through turning nodes
		while (currPt) {
			// Check if body segment is over turning node
			if (((currPt->x) == (currSeg->x)) && ((currPt->y) == currSeg->y)) {
				currSeg->direction = currPt->direction;
				dir = currPt->direction;

				if (currSeg == tail) {
					
					firstTurn = currPt->next;
					free(currPt);
					currPt = NULL;
					numNodes--;
				}
				break;
			}
			else {
				lastPt = currPt;
				currPt = currPt->next;
			}
		}

		currSeg = currSeg->next;
	}

	currSeg = head;
	for (i = 0; i < snakeLen; i++) {
		MAP[currSeg->y][currSeg->x] = '$';
		currSeg = currSeg->next;
	}

	return 1;
}

void main() {
	char input = 0;
	int steps=0;
	int food = 0;
	initMap();
	initSnake();
	drawMap();

	while (1) {
		Sleep(50);
		if (steps < 12) {
			steps++;
		}
		else {
			steps = 0;
			spawnFood();
			food++;
		}

		if(_kbhit()) input=_getch();

		if (input) {
			if (input == 'a' || input == 'd') {
				if (head->direction == 'w' || head->direction == 's') {
					head->direction = input;
					plantNode(input);
				}
			} else if (input == 'w' || input == 's') {
				if (head->direction == 'a' || head->direction == 'd') {
					head->direction = input;
					plantNode(input);
				}
			}
			
		}
		
		if (updateSnake()) {
			system("cls");
			drawMap();
			printf("SCORE = %i\n", snakeLen-2);
			fflush(stdin);
			input = 0;
		}
		else {
			printf("GAME OVER\n");
			getchar();
			break;
		}

		
	}
}