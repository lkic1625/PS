#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

pair<int, int> ST[21][200202];
vector<int> v[100101], t[100101];
int N, M, a, b, timer;
int level[200202], tour[200202], cache[21], bi[200202];

void dfs(int parent, int node, int l ) {
	level[node] = l;
	tour[++timer] = node;
	t[node].push_back(timer);
	for (auto child : v[node]) {
		if (child != parent) {
			dfs(node, child, l + 1);
			tour[++timer] = node;
			t[node].push_back(timer);
		}
	}
}

int lca(int a, int b) {
	int l = t[a][0];
	int r = t[b][0];
	if (l > r) swap(l, r);
	int k = bi[r - l + 1];
	return min(ST[k][l], ST[k][r - cache[k] + 1]).second;
}	

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &a, &b);
		v[a].push_back(b); v[b].push_back(a);
	}
	dfs(0, 1, 0);
	
	cache[0] = 1;
	for (int i = 1; i <= 20; i++) {
		cache[i] = min(2000000 + 1, cache[i - 1] * 2);
	}
	memset(bi, -1, sizeof(bi));
	for (int i = 0; i < 20; i++) if (cache[i] < 200002) bi[cache[i]] = i;
	for (int i = 1; i < 200002; i++) if (bi[i] == -1) bi[i] = bi[i - 1];

	for (int i = 0; i < 2 * N; i++) {
		ST[0][i] = { level[tour[i]], tour[i] };
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < 2 * N; j++) {
			ST[i][j] = min(ST[i - 1][j], ST[i - 1][j + cache[i - 1]]);
		}
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}
}