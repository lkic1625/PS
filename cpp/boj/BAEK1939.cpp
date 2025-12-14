#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<string.h>
#include<queue>
using namespace std;

const int MAX = 1000000000;
int n, m, a, b, c, s, e;
int check[100001];
vector<pair<int, int>> adj[100001];
priority_queue<int> pq;


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	int minWeight = MAX;
	scanf("%d %d", &s, &e);
	pq.push(s);
	while (!pq.empty()) {
		int node = pq.top();
		for (auto iter : adj[node]) {
			if (check[iter]) {
				
			}
			else {
				
			}
			
		}
		pq.pop();
	}
}