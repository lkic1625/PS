#include<iostream>
#include<vector>
#include<set>

using namespace std;

multiset<int> ans;
set<int> adj[100001];
int visited[100001];
int n, m, a, b, parm;

void dfs(int parent, int current) {
	visited[current] = true;
	int bef = 0;
	
	for (auto iter : adj[current]) {
		while (iter != ++bef) {
			if (visited[bef] == false) {
				parm++;
				dfs(current, bef);
			}
		}
	}
	
}

int main() {

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adj[a].insert(b);
		adj[b].insert(a);
	}
	for (int i = 0; i <= n; i++) {
		adj[i].insert(n + 1);
	}
	for (int i = 1; i <= n; i++) {
		if (false == visited[i]) {
			parm = 0;
			dfs(0, i);
			ans.insert(++parm);
		}
	}
	printf("%d\n", ans.size());
	
	for (auto iter : ans) {
		printf("%d ", iter);
	}

}