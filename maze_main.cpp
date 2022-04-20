#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_ROW 13
#define MAX_COL 17
#define START_POINT 0 
#define END_POINT  0
#define MAX_STACK_SIZE (MAX_ROW - 2) * (MAX_COL - 2)
#define EXIT_ROW (MAX_ROW - 2)
#define EXIT_COL (MAX_COL - 2)

// declaration of maze -> 
// if maze[row][col] == 0 path
// else if maze[row][col] == -1 block
short maze[MAX_ROW][MAX_COL] = {

	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	  {1,START_POINT,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},

	  {1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1},

	  {1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1},

	  {1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1},

	  {1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1},

	  {1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1},

	  {1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},

	  {1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1},

	  {1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1},

	  {1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1},

	  {1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,END_POINT,1},

	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};

// past path storage variables
short mark[MAX_ROW][MAX_COL];

// definition of movement stack
typedef struct {
	short row;
	short col;
	short dir;
}element;
element stack[MAX_STACK_SIZE];

int top = -1;

void stackFull() {
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

void stackEmpty() {
	fprintf(stderr, "Stack if empty, cannot delete element");
	exit(EXIT_FAILURE);
}

// push element at top of stack
void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) stackFull();
	stack[top++] = item;
}

element pop() {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}

typedef struct {
	short vert;
	short horiz;
}offsets;
offsets move[8];

void path(void) {
	// defining directions based on index values
	move[0].vert = -1; move[0].horiz = 0;
	move[1].vert = -1; move[1].horiz = 1;
	move[2].vert = 0;  move[2].horiz = 1;
	move[3].vert = 1;  move[3].horiz = 1;
	move[4].vert = 1;  move[4].horiz = 0;
	move[5].vert = 1;  move[5].horiz = -1;
	move[6].vert = 0;  move[6].horiz = -1;
	move[7].vert = -1; move[7].horiz = -1;	
	
	int i, row, col, nextRow, nextCol, dir, found = false;
	element pos;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		pos = pop();
		row = pos.row;
		col = pos.col;
		dir = pos.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL){
				found = true;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]){
				mark[nextRow][nextCol] = 1;
				pos.row = row;
				pos.col = col;
				pos.dir = ++dir;
				push(pos);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}	
			else ++dir;
		}
	}
	if (found) {
		printf("The path is:\n");
		for (i = 0; i <= top; i++) {
			printf("maze[%d][%d] -> \n", stack[i].row, stack[i].col);
		}
		printf("maze[%d][%d] -> \n", row, col);
		printf("maze[%d][%d] -> \n", EXIT_ROW, EXIT_COL);
	}
	else printf("The maze dose not have a path");
}

int main() {
	path();

	return EXIT_SUCCESS;
}