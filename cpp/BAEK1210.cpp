#include<iostream>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

const int MAX_N = 200 * 2 + 5, MAX_COST = 1e7, MAX_FLOW = MAX_COST * 100;

long long capacity[MAX_N][MAX_N], flow[MAX_N][MAX_N];
vector<int> adj[MAX_N];
int n, m, source, sink, cost, a, b;

void connect(int u, int v, int cost) {
	//connection between the two vertices must be marked with adjacent list.
	adj[u].push_back(v);
	adj[v].push_back(u);
	capacity[u][v] = cost;
}

void FordFulkerson(int source, int sink) {
	//init flow edge
	memset(flow, 0, sizeof(flow));
	
	while (true) {
		vector<int> parent(2 * n + 2, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (auto there : adj[here]) {
				if (capacity[here][there] - flow[here][there] > 0
					&& parent[there] == -1) {//If there is a node that has not been visited and can flow, push to the queue.
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1) break;
		long long amount = MAX_FLOW + 1;
		//finding the minimum amount of flow.
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		//flowing..
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		
	}
}


int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//시작점과 끝점 사이에 모든 경로에 반드시 점거된 톨게이트를 지나게 한다
	// == 시작점과 끝점 사이의 연결을 끊어 버린다
	//min-cut problem
	cin >> n >> m;
	cin >> source >> sink;
	sink += n;

	for (int gate = 1; gate <= n; gate++) {
		//To cut the edge, divide the toll gate into the entrance and exit and set it as a cost to occupy the edge weight.
		int exit = gate + n;
		cin >> cost;
		connect(gate, exit, cost);

	}

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		connect(a + n, b, MAX_COST);
		connect(b + n, a, MAX_COST);
	}

	FordFulkerson(source, sink);

	
	vector<int> visited(2 * n + 2, false);
	queue<int> q; 
	q.push(source); 
	visited[source] = 1;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (auto there : adj[here]) {
			if (visited[there]) continue;
			if (capacity[here][there] - flow[here][there] > 0) {
				q.push(there);
				visited[there] = true;
			}
		}
	}

	for (int gate = 1; gate <= n; gate++) {
		int exit = gate + n;
		//gate entry is allowed, but exit is not allowed then this is min-cut
		if (visited[gate] && !visited[exit]) {
			cout << gate << " ";
		}
	}
}