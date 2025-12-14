#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 32000 + 1;
int n, m, a, b, indegree[MAX];
queue<int> adj[MAX], q;

int main() {

	//input
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		//a -> b
		indegree[b]++;
		//make adj list 
		adj[a].push(b);
	}
	//init queue
	for (int i = 1; i <= n; i++) {
		if (indegree[i] == 0) {//push to the queue when node's indegree == 0
			q.push(i);
		}
	}
	while (!q.empty()) {
		//pop
		int vertex = q.front(); q.pop();
		//print sorted node sequence
		printf("%d ", vertex);

		while (!adj[vertex].empty()) {
			//pop
			int child = adj[vertex].front(); adj[vertex].pop();

			//update child node's indegree
			indegree[child]--;
			if (indegree[child] == 0) {//push to the queue when node's indegree == 0
				q.push(child);
			}
		}
	}
}