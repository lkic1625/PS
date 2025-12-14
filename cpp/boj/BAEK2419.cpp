#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#include<algorithm>

using namespace std;

const int MAX = 300 + 5, MAX_M = 1e6, MAX_X = 1e4 + 1, BOUNDARY = MAX * MAX_M;

enum {
	LEFT,
	RIGHT,
	DIRECTION = 2,
};

int n, m, x;
int cache[DIRECTION][MAX][MAX];
vector<int> coord;

int dp(int selected, int l, int r, int count) {

	if (l < 1 || r > n + 1) return BOUNDARY;
	if (count == 0) return 0;

	int& ret = cache[selected][l][r];
	if (ret != -1) return ret;

	ret = BOUNDARY;

	int bef = (selected == LEFT) ? l : r;
	int left_candy = count * abs(coord[bef] - coord[l - 1]);
	int right_candy = count * abs(coord[bef] - coord[r + 1]);

	ret = min(ret, right_candy + dp(RIGHT, l, r + 1, count - 1));
	ret = min(ret, left_candy + dp(LEFT, l - 1, r, count - 1));
	
	return ret;

}


int main() {
	cin >> n >> m;

	//boudary
	coord.push_back(MAX_X * 2);
	coord.push_back(-MAX_X * 2);
	coord.push_back(0);
	
	for (int i = 1; i <= n; i++) {
		cin >> x;
		coord.push_back(x);
	}

	sort(coord.begin(), coord.end());
	int start = lower_bound(coord.begin(), coord.end(), 0) - coord.begin();
	
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		memset(cache, -1, sizeof cache);
		ans = max(ans, i * m - dp(RIGHT, start, start, i));
	}

	cout << ans;

}