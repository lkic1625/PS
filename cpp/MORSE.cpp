#include<iostream>
#include<algorithm>

using namespace std;

const long long INF = 1000000001;

int C, N, M;
long long binomal[200][200];
long long K;

//이항계수 메모이제이션.
long long dp(int n, int m) {
	if (n < 0 || m < 0) return 0;

	if (binomal[n][m] > 0) {
		return binomal[n][m];
	}
	if (n == 0 || n == m) {
		return binomal[n][m] = 1;
	}

	return binomal[n][m] = min(dp(n - 1, m - 1) + dp(n - 1, m), INF);
}

//k번째 탐색을 위한 함수.
void kth(int n, int m, int k) {
	if (n == 0 && m == 0) {
		printf("\n");
		return;
	}

	long long t = dp(n + m - 1, n - 1);
	if (t > k) {
		printf("-");
		kth(n - 1, m, k);
	}
	else {
		printf("o");
		kth(n, m - 1, k - t);
	}

}

int main() {
	cin >> C;
	while (C-- > 0) {
		cin >> N >> M >> K;
		kth(N, M, K - 1);
	}
}