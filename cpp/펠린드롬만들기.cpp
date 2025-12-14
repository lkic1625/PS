#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int MAX = 1000 + 1;

int dp[MAX][MAX];

int solution(string plain)
{
	int answer = 0;
	int N = plain.size();
	for (int diff = 0; diff < N; diff++) {
		for (int s = 0, e = s + diff; s < N && e < N; s++, e++) {
			if (s == e) {
				dp[s][e] = true;
			}
			else if (e - s == 1) {
				dp[s][e] = (plain[e] == plain[s]);
			}
			else {
				dp[s][e] = (plain[e] == plain[s] && dp[s + 1][e - 1]);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		dp[i][i] = 1;
	}
	

	int s, e;
	int range = 1;
	for (int i = 0; i < N; i++) {

		if (dp[i][N - 1]) {
			range = max(range, N - i);
		}
	}
	answer = 2 * N - range;
	return answer;
}

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	

	//dp
	//It should be noted here that the order in which DP matrices are filled is diagonal,
	//which creates a lower triangulation matrix.
	string input;
	cin >> input;
	
	cout << solution(input);

}
