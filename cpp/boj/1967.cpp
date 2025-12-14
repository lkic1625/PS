#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX_N = 10000 + 1;
int n, u, v, w, visited[MAX_N], dist[MAX_N];
vector<pair<int, int>> adj[MAX_N];

void dfs(int u, int length, int dist[])
{
	//visit u
	visited[u] = 1;
	for (auto iter : adj[u]) {
		int v = iter.first, weight = iter.second;
		//if not visited child node v
		if (!visited[v]) {
			dist[v] = length + weight;
			dfs(v, dist[v], dist);
		}
	}
}

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> v >> w;
		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });
	}

	//root == 1
	dfs(1, 0, dist);
	int a = 1;
	for (int i = 1; i <= n; i++) {
		//find maximum distance from root
		if (dist[i] > dist[a]) {
			a = i;
		}
	}
	//init dfs params
	memset(visited, 0, sizeof(visited));
	memset(dist, 0, sizeof(dist));
	
	dfs(a, 0, dist);
	int b = 1;
	for (int i = 1; i <= n; i++) {
		//find maximum distance from node A 
		if (dist[i] > dist[b]) {
			b = i;
		}
	}
	//dist A-B is diameter of the tree
	cout << dist[b];

}