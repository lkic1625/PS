#include<iostream>
#include<queue>
#include<set>
#include<algorithm>
#include<string.h>

using namespace std;

struct Point {
	int y, x;
};

const int MAX = 50 + 5, DIRECTION = 8;

int N, num_of_k;
int map[MAX][MAX], height[MAX][MAX], visited[MAX][MAX];
int dy[DIRECTION] = { -1, -1, 0, 1, 1, 1,0, -1 };
int dx[DIRECTION] = { 0, 1, 1, 1, 0, -1, -1, -1 };
set<int> s;
Point start;

int dfs(int left, int right, int y, int x) {
	int ret = 0;
	if (!(left <= height[y][x] && height[y][x] <= right)) return 0;
	visited[y][x] = true;
	for (int i = 0; i < DIRECTION; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (left <= height[ny][nx] && height[ny][nx] <= right && !visited[ny][nx]) {
			ret += (map[ny][nx] == 'K') + dfs(left, right, ny, nx);
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	
	string input;
	for (int y = 1; y <= N; y++) {
		cin >> input;
		for (int x = 1; x <= N; x++) {
			map[y][x] = input[x - 1];	
			if (map[y][x] == 'P') {
				start = { y, x };
			}
			if (map[y][x] == 'K') {
				num_of_k += 1;
			}
		}
	}
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> height[y][x];
			s.insert(height[y][x]);
		}
	}
	for (int y = 0; y <= N + 1; y++) {
		for (int x = 0; x <= N + 1; x++) {
			visited[y][x] = true;
		}
	}
	auto left = s.begin();
	auto right = s.begin();
	int ans = 10'000'000;
	while (s.end() != right) {
		while (s.end() != left) {			
			for (int y = 1; y <= N; y++) {				
				for (int x = 1; x <= N; x++) {
					visited[y][x] = false;
				}
			}
			int k = dfs(*left, *right, start.y, start.x);
			if (num_of_k != k) {
				break;
			}
			ans = min(ans, (*right)  - (*left));
			left++;		
		}
		right++;
	}

	cout << ans;


}