#include<iostream>
#include<queue>
#include<string.h>
#define SIZE 125
using namespace std;

const int INF = SIZE * SIZE * 10 + 1;
int map[SIZE + 2][SIZE + 2], N, dist[SIZE + 2][SIZE + 2], test_case;
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
priority_queue<pair<int, pair<int, int >>> q;

int main() {
	
	do {
		test_case++;
		memset(map, INF, sizeof(map));
		memset(dist, INF, sizeof(map));
		cin >> N;
		if (!N) return 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> map[i][j];
			}
		}
		dist[1][1] = map[1][1];
		q.push({ -dist[1][1], { 1,1 } });
		while (q.size() != 0) {
			int cost = -q.top().first;
			int x = q.top().second.first;
			int y = q.top().second.second;
			q.pop();
			for (int i = 0; i < 4; i++) {
				int nextX = x + dx[i];
				int nextY = y + dy[i];
				if (dist[nextY][nextX] > cost + map[nextY][nextX]) {
					dist[nextY][nextX] = cost + map[nextY][nextX];
					q.push({ -dist[nextY][nextX], { nextX,nextY } });
				}
			}
			
		}
		cout << "Problem " << test_case << ": " << dist[N][N] << endl;
	} while (N != 0);
}