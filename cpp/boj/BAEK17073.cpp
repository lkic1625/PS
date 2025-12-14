#include<iostream>
#include<vector>

using namespace std;

const int MAX = 500000 + 5;

int N, U, V, W;
int dp[MAX];
vector<int> adj[MAX];

void dfs(int bef, int cur) {
	int size = adj[cur].size() - 1;
	if (size == 0) return;
	for (auto child : adj[cur]) {
		if (child == bef) continue;
		dp[child] = dp[cur] / size;
		dfs(cur, child);
	}

}

int main() {
	cin >> N >> W;
	for (int i = 0; i < N - 1; i++) {
		cin >> U >> V;
		adj[U].push_back(V);
		adj[V].push_back(U);
	}
	
	dp[1] = W;
	dfs(0, 1);

	double ans = 0;
	for (int i = 1; i <= N; i++) {
		ans += dp[i];
	}
	ans = ans / N;

	cout << ans;
}