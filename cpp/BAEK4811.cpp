#include<iostream>

using namespace std;

const int MAX = 30 + 1;
int N, input;
long long dp[MAX][MAX];

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//DP
	for (int h = 0; h <= 30; h++) {
		for (int w = 0; w <= 30; w++) {
			if (h == 0) {
				dp[h][w] = 1;
			} 
			else if (w == 0) {
				dp[h][w] = dp[h - 1][w + 1];
			}
			else {
				dp[h][w] = dp[h - 1][w + 1] + dp[h][w - 1];
			}
		}
	}

	while (true) {
		cin >> N;
		if (N == 0) break;
		cout << dp[N][0] << '\n';
	}
	
}