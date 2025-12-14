
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

const int MAX = 200001;
vector<int> adj[MAX];
int N, M, A, B;
int cache[MAX][4], parent[MAX], last, start_point[MAX];

void dfs(int bef, int here) {
	last = here;
	for (auto child : adj[here]) if (child != bef) {
		dfs(here, child);
	}

}

int find(int x) {

	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	parent[x] = y;
}

int dp(int prv, int cur, int dis) {

	if (dis > 3) return MAX + MAX;
	if (adj[cur].size() == 0) return 1;
	if (adj[cur].size() == 1 && adj[cur][0] == prv) return dis >= 2 ? 1 : 0;

	int& ret = cache[cur][dis];
	if (ret != -1) return ret;

	int on = 1, off = 0;
	for (auto iter : adj[cur]) {
		if (iter != prv) {
			on += dp(cur, iter, 1);
			off += dp(cur, iter, dis + 1);
		}
	}
	return ret = min(on, off);

}

int main() {
	cin >> N >> M;
	for (int i = 0; i < MAX; i++) {
		parent[i] = i;
		for (int j = 0; j < 4; j++)
			cache[i][j] = -1;
	}
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		adj[A].push_back(B);
		adj[B].push_back(A);
		if (find(A) != find(B))
			uni(A, B);
	}

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (parent[i] == i) {
			
			dfs(0, i);
			for (int i = 0; i < MAX; i++) {
				for (int j = 0; j < 4; j++)
					cache[i][j] = -1;
			}
			int temp = dp(0, 1, 2);
			for (int i = 0; i < MAX; i++) {
				for (int j = 0; j < 4; j++)
					cache[i][j] = -1;
			}
			int temp2 = dp(0, last, 2);
			ans += min(temp, temp2);
		}
	}

	cout << ans;



}

