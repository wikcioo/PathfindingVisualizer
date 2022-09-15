#include <iostream>
#include <vector>

//Prim's algorithm
const char PASSAGE_CHAR = ' ';
const char WALL_CHAR = 'X';
//Should be odd for equal walls
const int HEIGHT = 96;
const int WIDTH = 40;

struct Point {
	int x, y;

	bool validPoint(Point point) {
		return x + point.x >= 2 && x + point.x < HEIGHT - 1 &&
			y + point.y >= 2 && y + point.y < WIDTH - 1;
	}

	Point returnNewPoint(Point point) {
		return { x + point.x,y + point.y };
	}
};

void createMaze(char maze[][WIDTH]);
