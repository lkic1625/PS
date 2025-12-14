#include<iostream>

using namespace std;

int dp[2001][2001], N, S, E, M, n[2001];

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> n[i];
	}
	
	//dp
	//It should be noted here that the order in which DP matrices are filled is diagonal,
  	//which creates a lower triangulation matrix.
	
	for (int diff = 0; diff < N; diff++) {
		for (int s = 0, e = s + diff; s < N; s++, e++) {
			if (s == e) {
				dp[s][e] = true;
			} 
			else if (e - s == 1) {
				dp[s][e] = (n[e] == n[s]);
			}
			else {
				dp[s][e] = (n[e] == n[s] && dp[s + 1][e - 1]);
			}
		}
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		cout << dp[S - 1][E - 1] << '\n';
	}
}
