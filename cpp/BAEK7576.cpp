#include<iostream>
#include<queue>

using namespace std;

int M, N, ans = -1;
int map[1002][1002];
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
queue<pair<int, int>> q1, q2;

void fill(int x, int y, bool queueFlag) {
	for (int i = 0; i < 4; i++) {
		if (map[x + dx[i]][y + dy[i]] == 0) {
			map[x + dx[i]][y + dy[i]] = 1;
			if (queueFlag) q1.push(make_pair(x + dx[i], y + dy[i]));
			else q2.push(make_pair(x + dx[i], y + dy[i]));
		}	
	}
}

int main() {
	//init 
	for (int i = 0; i < 1002; i++) {
		for (int j = 0; j < 1002; j++) {
			map[i][j] = -1;
		}
	}
	//input
	scanf("%d %d", &M, &N);
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				q1.push(make_pair(i, j));
			}
		}
	}

	//bfs
	//큐 두개를 운영하여 문제 조건에 필요한 날짜를 계산.
	while (q1.size() != 0 || q2.size() != 0) {
		if (q1.size()) ans++;
		while (q1.size() != 0) {
			int x = q1.front().first;
			int y = q1.front().second;
			q1.pop();
			fill(x, y, false);
		}
		if (q2.size()) ans++;
		while (q2.size() != 0) {
			int x = q2.front().first;
			int y = q2.front().second;
			q2.pop();
			fill(x, y, true);
		}
		
	}
	//check map
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			if (map[i][j] == 0) {
				cout << -1;
				return 0;
			}
		}
	}
	//output
	cout << ans;
	
	

}