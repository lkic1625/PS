#include <iostream>
#include<vector>
#include<queue>
using namespace std;

#define N 100003
vector<int> adj[N], p;
int visited[N], level[2][N], root[2];
int n, m, d, x, a, b;

void dfs(int node, int length, int level[])
{
	visited[node] = 1;
	for (auto iter : adj[node]) {
		if (!visited[iter]) {
			level[iter] = length + 1;
			dfs(iter, length + 1, level);
		}
	}
}

int main()
{	
	cin >> n >> m >> d;
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &x);
		p.push_back(x);
	}
	for (int i = 0; i < n - 1; i++){

		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1, 0, level[0]);
	int k = 0;
	for (int i = 0; i < m; ++i){
		if (level[p[i]] > level[p[k]])
			k = i;
	}
	root[0] = p[k];
	memset(visited, 0, sizeof(visited));
	memset(level[0], 0, sizeof(level[0]));
	dfs(root[0], 0, level[0]);
	k = 0;
	for (int i = 0; i < m; ++i)
		if (level[p[i]] > level[p[k]])
			k = i;
	root[1] = p[k];
	memset(visited, 0, sizeof(visited));
	dfs(root[1], 0, level[1]);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (level[0][i] <= d && level[1][i] <= d)
			ans++;
	cout << ans << endl;
	return 0;
}

