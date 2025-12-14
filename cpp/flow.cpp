//source code for praticing ford-fulkerson Algorithm

#include<algorithm>
#include<queue>
#include<iostream>
#include<vector>
using namespace std;

const int MAX_V = 100;

int V;
int capacity[MAX_V + 1][MAX_V + 1], flow[MAX_V][MAX_V];

int FordFulkerson (int source, int sink) {
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;

	while (true) {
		vector<int> parent(MAX_V + 1, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++) {
				if (capacity[here][there] - flow[here][there] > 0
					&& parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}

		}
		if (parent[sink] == -1) break;
		int amount = 123123123;
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}