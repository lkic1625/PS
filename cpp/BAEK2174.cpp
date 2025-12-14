#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

const int MAX = 100 + 5;

enum MAP {
	WALL = 0,
};

enum DIRECTION {
	N = 0,
	E = 1,
	S = 2,
	W = 3,
	SIZE = 4,
};
enum STATUS {
	ERROR = 5,
	NORMAL = 6,
};

struct Robot {
	int x, y, dir;
};

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int map[MAX][MAX];
int A, B, N, M, x, y, iteration, index;
string query, dir;
Robot r[MAX];

pair<int, int> command(int index, string query) {
	if (query == "L") {
		r[index].dir = (r[index].dir + SIZE - 1) % SIZE;
	}
	if (query == "R") {
		r[index].dir = (r[index].dir + 1) % SIZE;
	}
	if (query == "F") {
		auto[x, y, dir] = r[index];
		int nx = dx[dir] + x;
		int ny = dy[dir] + y;
		
		if (map[ny][nx] != -1) return { map[ny][nx] ,ERROR };
		map[y][x] = -1;
		map[ny][nx] = index;
		r[index].x = nx;
		r[index].y = ny;
		
		
	}

	return { 0, NORMAL };
}

int directionParsing(string dir) {
	if (dir == "N") return N;
	if (dir == "E") return E;
	if (dir == "S") return S;
	if (dir == "W") return W;

}

int main() {
	cin >> A >> B >> N >> M;
	//init
	fill(map, WALL);
	for (int i = 1; i <= A; i++) {
		for (int j = 1; j <= B; j++) {
			map[i][j] = -1;
		}
	}
	for (int i = 1; i <= N; i++) {
		cin >> x >> y >> dir;
		int direction = directionParsing(dir);
		map[x][y] = i;
		r[i] = { x, y , direction };
	}

	for (int i = 0; i < M; i++) {
		cin >> index >> query >> iteration;
		for (int j = 0; j < iteration; j++) {
			auto [crashed, status] = command(index, query);
			if (status == ERROR) {
				
				if (crashed == WALL) {
					cout << "Robot " << index << " crashes into the wall";
				}
				else {
					cout << "Robot " << index << " crashes into robot" << crashed;
				}
				break;
			}

		}
	}
}