#include<iostream>
#include<queue>
#include<vector>

using namespace std;

vector<pair<int, int>> adj[100001];
priority_queue<pair<int, int>> pq;
int dist[100001], a, b, w, n, m, visited[100001] = { 1, };


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		adj[a].push_back({ b, w });
		
		adj[b].push_back({ a, w });
	}
	pq.push({ 0, 1 }); 
	while (!pq.empty()) {
		auto node = pq.top().second;
		auto path = pq.top().first;
		pq.pop();
		if (path < dist[node]) {
			dist[node] = path;
		}
		if (n == node) break;
		for (auto iter : adj[node]) {
			auto child = iter.first;
			auto weight = iter.second;
			if (!visited[child]) {
				visited[child] = true;
				pq.push({ path + weight, child });
			}
		}
	}
}