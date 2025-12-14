#include<iostream>
#include<queue>
#include<algorithm>
#include<string.h>

using namespace std;

int T, N, W;
int area[20002];
int cache[4][5][20001];

int dp(int cond, int flag, int x) {
	//basis case
	if (x >= N) return 0;

	//memoization
	int& ret = cache[cond][flag][x];
	if (ret != -1) return ret;

	//indexing process
	int idx = x == 0 ? N : x;

	int vertical = area[idx + N] + area[idx] <= W;
	int inhzt = area[idx] + area[idx + 1] <= W;
	int outhzt = area[idx + N] + area[idx + N + 1] <= W;

	//Circular exception handling
	if (x == N - 1 && cond != 0) {
		if (cond == 3) {
			return flag == 0 ? vertical : 0;
		}
		if (cond == 2) {
			return flag != 1 ? inhzt : 0;
		}
		if (cond == 1) {
			return flag != 2 ? outhzt : 0;
		}
	}

	if (flag == 0) {
		ret = max(vertical + dp(cond, 0, x + 1), ret);
		ret = max(inhzt + outhzt + dp(cond, 0, x + 2), ret);
		ret = max(inhzt + dp(cond, 1, x + 1), ret);
		ret = max(outhzt + dp(cond, 2, x + 1), ret);

	}
	if (flag == 1) {
		ret = max(outhzt + dp(cond, 2, x + 1), dp(cond, 0, x + 1));
	}
	if (flag == 2) {
		ret = max(inhzt + dp(cond, 1, x + 1), dp(cond, 0, x + 1));
	}

	return ret;
}

int main() {
	cin >> T;
	while (T-- > 0) {
		//init
		scanf("%d %d", &N, &W);
		memset(cache, -1, sizeof(cache));
		for (int i = 1; i <= 2 * N; i++) {
			scanf("%d", &area[i]);
		}

		int ans = 0;
		ans = max(ans, dp(3, 0, 0));//꼬리 전부를 채우는 경우
		ans = max(ans, dp(2, 1, 0));//꼬리 바깥을 채우는 경우
		ans = max(ans, dp(1, 2, 0));//꼬리 안을 채우는 경우
		ans = max(ans, dp(0, 0, 1));//순환하지 않을 경우

		cout << 2 * N - ans << "\n";

	}
}