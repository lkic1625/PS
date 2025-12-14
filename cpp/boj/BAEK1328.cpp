#include<iostream>

#define MOD %

using namespace std; 

const int PRIME = 1000000007, MAX = 100 + 5;

long long dp[MAX][MAX][MAX];
int N, R, L;

int memo(int n, int l, int r) {
	if (l == 0 || r == 0) return 0;
	
	long long& ret = dp[n][l][r];
	if (ret != -1) return ret;

	return ret = (memo(n - 1, l - 1, r) + memo(n - 1, l, r - 1) + memo(n - 1, l, r) * (n - 2)) MOD PRIME;
}

int main() {
	
	cin >> N >> R >> L;
	//Recurrence relation
	//dp[N][L][R] = dp[N - 1][L - 1][R] + dp[N - 1][L][R - 1] + dp[N - 1][L][R] * (N - 2);
	dp[1][1][1] = 1;
	for (int n = 2; n <= N; n++) {
		for (int l = n; l > 0; l--) {
			for (int r = 1; l + r <= n + 1; r++) {
				dp[n][l][r] = dp[n - 1][l - 1][r] + dp[n - 1][l][r - 1] + dp[n - 1][l][r] * (n - 2);
				dp[n][l][r] = dp[n][l][r] MOD PRIME;
			}
		}
	}

	cout << dp[N][L][R];
}