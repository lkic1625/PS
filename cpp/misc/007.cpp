#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

const int BIT_SIZE = 1 << 20;

double cache[BIT_SIZE];
int N, map[21][21];

double dp(int bit) {
	int cnt = __builtin_popcount(bit);
	if (cnt == N) {
		return 1;
	}

	double &ret = cache[bit];
	if (ret != -1) return ret;
	ret = 1;
	
	for (int i = 0; i < N; i++) {
		if ((1 << i) & bit) continue;
		ret = max(ret, map[i][cnt] * dp(bit | (1 << i)));
	}
	return ret;
}

int main() {
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < BIT_SIZE; i++) {
		cache[i] = -1;	
	}

	double ans = dp(0);
	ans /= pow(100, N - 1);
	if (ans == 1) ans = 0;
	printf("%lf", ans);
}