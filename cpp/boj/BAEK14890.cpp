#include<iostream>
#include<string.h>
#include<math.h>

using namespace std;

const int MAX = 100;

int N, L;
int map[MAX + 2][MAX + 2];

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

enum {
	BOUNDARY = -1,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

bool can_i_move(int y, int x, int direction) {
	for (int i = 0; i < L - 1; i++) {
		int ny = dy[direction] + y;
		int nx = dx[direction] + x;

		if (map[ny][nx] != map[y][x]) {
			return false;
		}

		y = ny, x = nx;
	}

	return true;
}

int traverse(int y, int x, int direction) {
	do {
		int ny = dy[direction] + y;
		int nx = dx[direction] + x;
		
		if (map[ny][nx] == map[y][x]) {
			y = ny, x = nx;
			continue;
		}

		bool is_movable = 
			(abs(map[ny][nx] - map[y][x]) == 1 && can_i_move(ny, nx, direction));
		if (is_movable) {
			y = y + L * dy[direction], x = x + L * dx[direction];
		}
		else {
			return false;
		}

	} while (map[y + dy[direction]][x + dx[direction]] != BOUNDARY);

	return true;
}


int main() {
	//init for boundary check.
	memset(map, BOUNDARY, sizeof map);

	cin >> N >> L;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	int answer = 0;
	for (int x = 1; x <= N; x++) {
		if (traverse(1, x, DOWN)) {
			answer += 1;
		}
	}

	for (int y = 1; y <= N; y++) {
		if (traverse(y, 1, RIGHT)) {
			answer += 1;
		}
	}

	cout << answer;
	
	
}