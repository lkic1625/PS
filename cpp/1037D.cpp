#include<iostream>
#include<string.h>
#include<queue>
#include<set>
using namespace std;

set<int> adj[200001];

queue<pair<int, int>> q;
int n, x, y, seq[200001];

int main() {
	//0 root
	adj[1].insert(0);
	memset(seq, -1, sizeof(seq));

	scanf("%d", &n);
	
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &x, &y);
		adj[x].insert(y);
		adj[y].insert(x);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &seq[i]);
	}
	int trav = 1;
	q.push({ 0, 1 });
	while (q.size() != 0) {
		int valid = 0;
		int parent = q.front().first;
		int vertex = q.front().second;
		q.pop();
		auto exist = adj[vertex].end();

		for (int i = 0; i < adj[vertex].size(); i++) {
			if (adj[vertex].find(seq[trav]) != exist) {
				q.push({ vertex, seq[trav] });
				trav++; valid++;
			}
		}
		if (valid != adj[vertex].size() - 1) break;
	}
 	cout << ((trav == n || n == 1) && seq[0] == 1 ? "Yes" : "No") << endl;
}

