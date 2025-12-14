//https://www.acmicpc.net/problem/1261

#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
int n, m;
int cache[101][101];
int dx[4] = { 0,1 ,-1,0 };
int dy[4] = { 1, 0, 0 , -1 };
queue<pair<int, int>> q;
vector<string> map;
bool dfs(int y, int x) {

	if (map[y][x] == '1' || map[y][x] == '2') return false;
	if (y == n && x == m) return true;
	
	bool ret = dfs(y , x + 1) || dfs(y + 1, x) || dfs(y, x - 1) || dfs(y - 1, x);
	if (!ret) q.push(make_pair(y, x));

	return ret;
	
}
int bfs() {
	for (int i = 1; i <= n * m; i++) {
		int qSize = q.size();
		for (int j = 0; j < qSize; j++) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			for (int k = 0; i < 4; i++) {
				if (map[y + dy[k]][x + dx[k]] == '1') {
					map[y + dy[k]][x + dx[k]] = '0';
					if (dfs(y + dy[k], x + dx[k]))
						return i;
					map[y + dy[k]][x + dx[k]] = '1';
				}
			}
		}
	}
}
int main() {
	cin >> m >> n;
	string temp, bound;
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			cache[i][j] = -1;
	for (int i = 0; i < m + 2; i++) bound += '2';
	//init
	map.push_back(bound);
	for (int i = 0; i < n; i++) {
		cin >> temp;
		temp = '2' + temp + '2';
		map.push_back(temp);	
	}
	map.push_back(bound);
	//map
	int ans = 0;
	if (!dfs(1, 1)) {
		ans += bfs();
	}
	
	cout << ans << endl;
	
}