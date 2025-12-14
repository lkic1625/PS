#include<iostream>
#include<algorithm>

#define MOD %

using namespace std;

const int PRIME = 10007, MAX = 1'000'000 + 1;

int N;
int dp[MAX];

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) dp[i] = i;

	for (int n = 1; n <= N; n++) {
		for (int i = 1; i <= n / 2; i++) {
			dp[n] = max(dp[n - i] * dp[i], dp[n]) MOD PRIME;
		}
	}

	cout << dp[N];

}