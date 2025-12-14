#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define MAX 100000
#define ROOT 1
using namespace std;
typedef long long ll;

struct Node {
	ll dist;
	int weight;
	int n;
	Node(ll dist, int weight, int n) 
		: dist(dist), weight(weight), n(n) {}
};
//priority_queue 사용을 위한 연산자 정의
bool operator<(const Node& lv, const Node& rv) {
	return lv.dist > rv.dist;
}


int n, x, y, w;
bool visited[MAX + 1] = { true, };
vector<pair<int, int>> adj[MAX + 1];
priority_queue<Node> q;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &x, &y, &w);
		adj[x].push_back(make_pair(y, w));
		adj[y].push_back(make_pair(x, w));
	}

	q.push(Node(0, 0, 1));
	ll dist;
	ll ans = 0;

	while (q.size() != 0) {
		int node = q.top().n;
		int weight = q.top().weight;
		dist = q.top().dist;
		visited[node] = true;
		q.pop();

		for (auto iter = adj[node].begin(); iter != adj[node].end(); iter++) {
			int child = (*iter).first;
			if (visited[child]) continue;
			int weight = (*iter).second;

			q.push(Node((dist + weight), weight, child));
			ans += weight;
		}
	}
	cout << ans * 2 - dist;
	
	

	
}