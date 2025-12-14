#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#define MAX 300000
#define ROOT 1
using namespace std;
typedef long long ll;

struct Node {
	ll dist;
	int weight;
	int n;
	int num;
	Node(ll dist, int weight, int n, int num)
		: dist(dist), weight(weight), n(n), num(num) {}
};
//priority_queue 사용을 위한 연산자 정의
bool operator<(const Node& lv, const Node& rv) {
	return lv.dist > rv.dist;

}

int n, x, y, w, m, u;
int check[MAX + 1], w1[MAX + 1];
int visited[MAX + 1] = { true, };
vector<pair<pair<int, int>,int>> adj[MAX + 1];
priority_queue<Node> q;
set<int> edge;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < MAX + 1; i++)
		check[i] = 1000000000;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &x, &y, &w);
		adj[x].push_back({ {y, w}, i });
		adj[y].push_back({ {x, w}, i });
	}
	scanf("%d", &u);

	q.push(Node(0, 0, u, 0));
	ll dist;
	ll ans = 0;

	while (q.size() != 0) {
		int node = q.top().n;
		int weight = q.top().weight;
		int num = q.top().num;
		dist = q.top().dist;

		if (check[node] >= dist) {
			w1[node] = weight;
			check[node] = dist;
			visited[node] = num;
		}
		
		q.pop();
		
		for (auto iter = adj[node].begin(); iter != adj[node].end(); iter++) {
			int child = (*iter).first.first;
			if (visited[child]) continue;
			int weight = (*iter).first.second;
			int n1 = (*iter).second;
			q.push(Node((dist + weight), weight, child, n1));
		}
	}
	for (int i = 1; i < n + 1; i++) {
		ans += w1[i];
		edge.insert(visited[i]);
	}
	cout << ans << endl;
	for (auto iter = ++edge.begin(); iter != edge.end(); iter++) {
		printf("%d ", *iter);
	}
}