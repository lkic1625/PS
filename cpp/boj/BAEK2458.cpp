#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;

int N, M, a, b, visited[501];
queue<int> trav;
vector<int> adj[501];
int deg[501];


int main() {
	cin >> N >> M;
	
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		deg[b]++;
	}
	for (int i = 1; i <= N; i++) {
		visited[i] = 1;
		if (deg[i] == 0) {
			trav.push(i);
		}
	}
	while (!trav.empty()) {
		auto node = trav.front();
		trav.pop();
		for(auto next : adj[node]) {
			deg[next]--;
			if (deg[next] == 0) trav.push(next);
			visited[next] += visited[node];
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (visited[i] + adj[i].size() == N - 1) ans++;
	}
	cout << ans;
	
}