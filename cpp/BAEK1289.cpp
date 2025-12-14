#include<iostream>
#include<vector>
#include<tuple>

using namespace std;
const long long MOD_MUL_INVERSE_OF_2 = 500000004; // 2^2 * 3^2 * 7 * 109^2 * 167
const long long MOD = 1000000007;
const long long MAX = 100000 + 2;
long long N, s, t, w, dist[MAX], cache[MAX];
vector<tuple<long long, long long>> adj[MAX];

long long dfs(long long bef, long long cur) {
	long long& ret = dist[cur];
	for (long long i = 0; i < adj[cur].size(); i++) {
		auto[child, weight] = adj[cur][i];
		if (child == bef) continue;
		ret += (weight * dfs(cur, child) + weight) % MOD;
		ret = ret % MOD;
	}
	return ret;
}

void dp(long long bef, long long cur, long long weight) {
	long long& ret = cache[cur];
	ret = ((dist[bef] - (dist[cur] + 1) * weight + cache[bef] + 1) * weight) % MOD;

	for (long long i = 0; i < adj[cur].size(); i++) {
		auto[child, weight] = adj[cur][i];
		if (child == bef) continue;
		dp(cur, child, weight);
	}
}


int main() {

	//fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (long long i = 0; i < N - 1; i++) {
		cin >> s >> t >> w;
		adj[s].push_back({ t, w });
		adj[t].push_back({ s, w });
	}

	dfs(0, 1);
	dp(0, 1, 0);
	long long ans = 0;
	for (long long i = 1; i <= N; i++) {
		ans += (cache[i] + dist[i]) % MOD;
		ans = ans % MOD;
	}
	ans = (ans * MOD_MUL_INVERSE_OF_2) % MOD;
	cout << ans;

}