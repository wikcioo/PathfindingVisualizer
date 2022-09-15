#include "MazeGeneration.h"

using namespace std;

void createMaze(char maze[][WIDTH])
{
	struct Point points[] = { { -2, 0 },
							{ 0, -2 },
							{ 0, 2 },
							{ 2, 0 } };
	srand(time(NULL));
	Point currentPoint = { 2,2 };
	maze[currentPoint.x][currentPoint.y] = PASSAGE_CHAR;
	vector<Point> frontier;
	for (auto point : points) {
		if (currentPoint.validPoint(point)) {
			frontier.push_back({ currentPoint.returnNewPoint(point) });
		}
	}

	while (frontier.size() > 0) {
		int number = rand() % frontier.size();
		currentPoint = frontier.at(number);
		if (maze[currentPoint.x][currentPoint.y] == WALL_CHAR) {
			maze[currentPoint.x][currentPoint.y] = PASSAGE_CHAR;
			vector<Point> neighbours;
			for (auto point : points) {
				Point newPoint = currentPoint.returnNewPoint(point);
				if (currentPoint.validPoint(point) && maze[newPoint.x][newPoint.y] == PASSAGE_CHAR) {
					neighbours.push_back({ newPoint.x,newPoint.y });
				}
			}
			if (neighbours.size() > 0) {
				int passageNum = rand() % neighbours.size();
				Point newPassage = neighbours.at(passageNum);
				int x = (newPassage.x + currentPoint.x) / 2;
				int y = (newPassage.y + currentPoint.y) / 2;
				maze[x][y] = PASSAGE_CHAR;
			}
			for (auto point : points) {
				Point newPoint = currentPoint.returnNewPoint(point);
				if (currentPoint.validPoint(point) && maze[newPoint.x][newPoint.y] == WALL_CHAR) {
					frontier.push_back({ newPoint.x,newPoint.y });
				}
			}
		}
		frontier.erase(frontier.begin() + number);


	}
}
