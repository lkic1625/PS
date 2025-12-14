#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 100000000;
int C, N, K, L, M, R, r,c;
int n[100], cls[100];
int cache[100][10000];

int bitCount(int x) {
	if (x == 0) return 0;
	return x % 2 + bitCount(x / 2);
}

bool func(int state, int subset) {
	while (subset != 0) {
		unsigned long lb;
		//lb = __builtin_ctz(subset);
		//g++ version
		_BitScanForward(&lb, subset);
		//visual studio version
		if ((n[lb] & state) != n[lb]) return false;
		subset &= (subset - 1);
	}
	return true;
}

int dp(int state, int current) {
	//basis case
	if (bitCount(state) >= K ) return 0;
	if (current == M) return MAX;

	int& ret = cache[current][state];
	if (ret != -1) return ret;
	ret = MAX;
	
	int candidate = (cls[current] & ~state);

	for (int subset = candidate; subset; subset = ((subset - 1) & candidate)) {
		if (bitCount(subset) > L) continue;
		if (func(state, subset)) ret = min(ret, 1 + dp(state | subset, current + 1));
	}
	ret = min(ret, dp(state, current + 1)); //empty set case

	return ret;
}

int main() {
	cin >> C;
	while (C-- > 0) {
		for (int i = 0; i < 100; i++) {
			n[i] = 0;
			cls[i] = 0;
			for (int j = 0; j < 10000; j++) {
				cache[i][j] = -1;
			}
		}
		
		cin >> N >> K >> M >> L;
		for (int i = 0; i < N; i++) {
			cin >> R;
			for (int j = 0; j < R; j++) {
				cin >> r;
				n[i] |= 1 << r;
			}
		}
		for (int i = 0; i < M; i++) {
			cin >> c;
			int temp;
			for (int j = 0; j < c; j++) {
				cin >> temp;
				cls[i] |= 1 << temp;
			}
		}
		int ans = dp(0, 0);
		if (ans >= MAX) cout << "IMPOSSIBLE" << endl;
		else cout << ans << endl;

	}
}