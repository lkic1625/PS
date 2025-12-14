#include<iostream>
#define MOD %

using namespace std;

const int MAX = 100'000 + 1, PRIME = 1'000'000'007;

int N;
long long dp[MAX];
long long factorial[MAX];

int main() {
	cin >> N;

	dp[1] = 0;
	dp[2] = 1;
	factorial[0] = 1;
	for (int n = 1; n <= N; n++) {
		factorial[n] = (factorial[n - 1] * n) MOD PRIME;
	}
	for (int i = 3; i <= N; i++) {
		dp[i] = ((i - 1) * (dp[i - 1] + dp[i - 2])) MOD PRIME;
	}
	
	cout << (factorial[N] * dp[N]) MOD PRIME;

}