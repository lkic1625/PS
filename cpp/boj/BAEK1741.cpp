#include<iostream>
#include<vector>
#include<set>

using namespace std;

set<int> adj[100001];
vector<int> ans;
int visited[100001];
int n, m, a, b;

int dfs(int parent, int current) {
	visited[current] = true;
	int bef = 0;
	int ret = 0;
	for (auto iter : adj[current]) {
		if (iter - bef++ == 1) continue;
		while (iter != bef) {
			if(visited[bef] == false)
				ret += (1 + dfs(current, bef));
			bef++;
		}
	}
	return ret;
}

int main() {

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adj[a].insert(b);
		adj[b].insert(a);
	}
	for (int i = 1; i <= n; i++) {
		if (false == visited[i]) {
			ans.push_back(dfs(0, i));
		}
	}
	printf("%d\n", ans.size());
	for (auto iter : ans) {
		printf("%d ", iter);
	}
	
}
