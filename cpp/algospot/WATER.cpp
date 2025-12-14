#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

priority_queue<pair<int,pair<int, int>>> q;

int map[102][102];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, -1 };
int t, m, n, low, x, y;;



int main() {
	memset(map, -1, sizeof(map));
	low = 10000000;
	cin >> m >> n;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			q.push({ map[i][j], {i, j} });
			
		}
	}

	while (q.size() != 0) {
		int height = q.top().first;
		int y = q.top().second.first;
		int x = q.top().second.second;
		q.pop();
		
	}

}