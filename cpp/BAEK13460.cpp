#include<iostream>

using namespace std;

enum {
	UP,
	LEFT,
	DOWN,
	RIGHT,
	
	

	FAIL = -10000,

	ROAD = '.',
	WALL = '#',
	RED = 'R',
	BLUE = 'B',
	HOLE = 'O',
};

const int SIZE = 10 + 2;

struct Point {
	int x, y;
	

};

Point red, blue, hole;
int map[SIZE][SIZE], dx[4] = { 0, 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };

int N, M;
char input;

Point tilt(Point p, int direction) {
	bool reach_the_wall = false;
	bool fall_into_hole = false;

	while (!reach_the_wall && !fall_into_hole) {
		auto nx = p.x + dx[direction];
		auto ny = p.y + dy[direction];
		if (map[ny][nx] == WALL) {
			reach_the_wall = true;
		}
		else if (map[ny][nx] == HOLE) {
			fall_into_hole = true;
			p = { nx, ny };
		}
		else {
			p = { nx, ny };
		}
	}

	return p;
}

int traversal(Point red, Point blue, int depth) {
	if (depth > 10) return FAIL;

	for (int direction = 0; direction < 4; direction++) {

	}

	UP;
	if (red.y > blue.y) {
		auto tilted_red = tilt(red, UP);
		map[tilted_red.y][tilted_red.x] = WALL;
		auto tilted_blue = tilt(blue, UP);
		
		traversal(tilted_red, tilted_blue, depth + 1);
		
		map[tilted_red.y][tilted_red.x] = ROAD;

	}
	else {
		auto tilted_blue = tilt(blue, UP);
		map[tilted_blue.y][tilted_blue.x] = WALL;
		auto tilted_red = tilt(red, UP);
		map[tilted_red.y][tilted_red.x] = ROAD;

		traversal(tilted_red, tilted_blue, depth + 1);

	}
	

	RIGHT;

	

}

int main() {
	cin >> N >> M;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			cin >> input;
			if (input == RED) {
				red = { x, y };
			}
			else if (input == BLUE) {
				blue = { x , y };
			}
			else if (input == HOLE) {
				hole = { x, y };
			}
			map[y][x] = input;
		}
	}
}