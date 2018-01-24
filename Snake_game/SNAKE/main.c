
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
int snakeLen;
int numNodes;

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
numNodes = 0;

enum MAPCHAR {
	snake_body,
	border,
	food
};

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

void drawSnake() {
	bodySegment *currSeg = head;
	int i;

	for (i = 0; i < snakeLen; i++) {
		MAP[currSeg->y][currSeg->x] = '$';
		currSeg = currSeg->next;
	}
}

void initSnake() {
	snakeLen = 2;
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

	x = rand() % COLS;
	y = rand() % ROWS;

	while (inSnake(x, y) || inBorder(x,y)) {
		x = rand() % COLS;
		y = rand() % ROWS;
	}

	MAP[y][x] = 'O';
}

int checkCollision() {
	int i,x,y;
	bodySegment *currSeg = head->next;

	while(currSeg) {
		if (head->x == currSeg->x && head->y == currSeg->y){
			return 1;
		}
		else
			currSeg = currSeg->next;
	}
	
	return 0;
}

void checkSegBounds(bodySegment* currSeg) {
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
}

void checkEating() {
	if (MAP[head->y][head->x] == 'O') {
		//tail1 = tail;
		incSnakeLen();
		//tail2 = tail;
		//assert(tail1 != tail2);
	}
}

int checkRedirect(bodySegment *last, bodySegment *curr) {
	if (last->direction != curr->direction) {
		curr->direction = last->direction;
		return 0;
	}
	return 1;
}
int updateSnake() {
	int redirect, x, y, currNodes, currSegs;
	char dir;
	bodySegment *currSeg = head, *tail1, *tail2, *lastSeg = head;
	turnPoint *currPt, *lastPt;
	currNodes = numNodes;

	// Iterate through body segments
	redirect = 1;
	//currSegs = snakeLen;
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
			printf("Snake updating error!\n");
			return;
		}

		// If on head seg, check if eating
		if (currSeg == head) {
			checkEating();
		}
		
		// ERROR: new segs are updated with previous tail.
		// new seg should retain OLD tail direction
		/*
		else {
			if (redirect)
				redirect = checkRedirect(lastSeg, currSeg);
			else
				redirect = 1;
		}
		*/
		// Check if out-of-bounds
		checkSegBounds(currSeg);

		// Check if there was collision
		if (checkCollision()) {
			return 0;
		}

		// Redirect snake segments by iterating through turning nodes
		
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
		
		lastSeg = currSeg;
		currSeg = currSeg->next;
	}
	drawSnake();

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