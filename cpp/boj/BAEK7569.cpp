#include<iostream>
#include<queue>

using namespace std;

struct Point {
	int x, y, z;
	Point(int x, int y, int z) :x(x), y(y), z(z) {}
};
int M, N, H, ans = -1;
int map[102][102][102];
int dy[6] = { 0, 1, 0, -1, 0, 0 };
int dx[6] = { 1, 0, -1, 0, 0, 0 };
int dz[6] = { 0, 0, 0, 0, 1, -1 };
queue<Point> q1, q2;

void fill(int x, int y, int z, bool queueFlag) {
	for (int i = 0; i < 6; i++) {
		if (map[z + dz[i]][y + dy[i]][x + dx[i]] == 0) {
			map[z + dz[i]][y + dy[i]][x + dx[i]] = 1;
			if (queueFlag) q1.push(Point(x + dx[i], y + dy[i], z + dz[i]));
			else q2.push(Point(x + dx[i], y + dy[i], z + dz[i]));
		}
	}
}

int main() {
	//init 
	for (int i = 0; i < 102; i++) {
		for (int j = 0; j < 102; j++) {
			for (int k = 0; k < 102; k++) {
				map[i][j][k] = -1;
			}
		}
	}
	//input
	scanf("%d %d %d", &M, &N, &H);
	for (int i = 1; i < H + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			for (int k = 1; k < M + 1; k++) {
				scanf("%d", &map[i][j][k]);
				if (map[i][j][k] == 1) {
					q1.push(Point(k, j, i));
				}
			}	
		}
	}

	//bfs
	//큐 두개를 운영하여 문제 조건에 필요한 날짜를 계산.
	while (q1.size() != 0 || q2.size() != 0) {
		if (q1.size()) ans++;
		while (q1.size() != 0) {
			int x = q1.front().x;
			int y = q1.front().y;
			int z = q1.front().z;
			q1.pop();
			fill(x, y, z, false);
		}
		if (q2.size()) ans++;
		while (q2.size() != 0) {
			int x = q2.front().x;
			int y = q2.front().y;
			int z = q2.front().z;
			q2.pop();
			fill(x, y, z, true);
		}

	}
	//check map
	for (int i = 1; i < H + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			for (int k = 1; k < M + 1; k++) {
				if (map[i][j][k] == 0) {
					cout << -1;
					return 0;
				}
			}
		}
	}
	//output
	cout << ans;



}