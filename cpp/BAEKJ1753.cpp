#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string.h>
#define V 20000
#define E 300000
using namespace std;

const long long INF = V * E + 1;
int v1, e, root, u, w,v;
long long dist[V + 1];
vector<pair<int, int>> vertex[V + 1];
priority_queue<pair<long long, int>> q;

int main() {
	//init
	for (int i = 1; i < V + 1; i++)
		dist[i] = INF;
	scanf("%d %d", &v1, &e);
	scanf("%d", &root);
	dist[root] = 0;
	q.push(make_pair(0, root));
	for (int i = 0; i < e; i++) {
		scanf("%d %d %d", &u, &v, &w);
		vertex[u].push_back({ v,w });
	}
	while (!q.empty()) {
		long long d = -q.top().first;
		int node = q.top().second;
		q.pop();
		if (dist[node] < d) continue;

		for (auto iter = vertex[node].begin(); iter != vertex[node].end(); iter++) {
			int child = (*iter).first;
			int weight = (*iter).second;
			if (dist[child] > d + weight) {
				dist[child] = d + weight;
				q.push({ -dist[child], child });
			}
		}
	}
	for (int i = 1; i <= v1; i++) {
		if (dist[i] != INF)
			printf("%lld\n", dist[i]);
		else
			printf("%s\n", "INF");
	}
	

}