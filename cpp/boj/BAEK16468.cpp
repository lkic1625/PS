#include<iostream>

using namespace std;

const int MOD = 100030001;
const int MAX_N = 300 + 2, MAX_L = 500 + 2;
int N, L;
int cache[MAX_N][MAX_L];

int dp(int n, int l) {
	if (l >= L || n >= N) return l == L && n == N;

	int& ret = cache[n][l];
	if (ret != -1) return ret;

	ret = dp(n + 2, l + 1) + 2 * dp(n + 1, l + 1) + 2 * dp(n, l + 1);
	ret = ret % MOD;

	return ret % MOD;
}

int main() {
	memset(cache, -1, sizeof cache);
	cin >> N >> L;
	cout << dp(0, 0);
}