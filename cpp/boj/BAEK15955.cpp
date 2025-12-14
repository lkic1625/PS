#include<iostream>
#include<set>
#include<vector>
#include<tuple>
#include<algorithm>
#include<queue>
#include<math.h>
#include<map>
#include<string.h>

using namespace std;

const int MAX = 250000 + 20, MAX_VALUE = 10e9, LOG_MAX = 21;

int N, Q;
int x, y, a, b, X;
int visited[MAX];
int lev[MAX], parent[LOG_MAX][2 * MAX], HP[LOG_MAX][2 * MAX];

vector<pair<int, int>> adj[MAX];
vector<tuple<int, int>> point;
set<tuple<int, int, int>> x_sorted_map, y_sorted_map;
priority_queue<tuple<int, int, int>> pq;

enum {
	FORWARD,
	REVERSE,
};

int LCA(int u, int v) {
	
	if (lev[u] > lev[v]) swap(u, v);

	int hp_u = 0, hp_v = 0;
	for (int i = LOG_MAX - 1; i >= 0; i--) {
		if (lev[v] - lev[u] >= (1 << i)) {
			hp_v = max(hp_v, HP[i][v]);
			v = parent[i][v];
		}
	}
	if (u == v) {
		return hp_v;
	}

	for (int i = LOG_MAX - 1; i >= 0; i--) {
		if (parent[i][u] != parent[i][v]) {
			hp_u = max(hp_u, HP[i][u]);
			hp_v = max(hp_v, HP[i][v]);
			u = parent[i][u];
			v = parent[i][v];
		}
	}
	hp_u = max(hp_u, HP[0][u]);
	hp_v = max(hp_v, HP[0][v]);
	//return maximum weight in this path
	return max(hp_u, hp_v);
}

void dfs(int before, int here, int level) {
	lev[here] = level;
	for (auto there : adj[here]) if (before != there.first) {
		parent[0][there.first] = here;
		HP[0][there.first] = there.second;
		dfs(here, there.first, level + 1);
	}
}

void add(set<tuple<int, int, int>>::iterator it, int a, int ax, int ay, int direction) {
	if (direction == REVERSE) it--;
	else if(direction == FORWARD) it++;

	auto[x, y, i] = *(it);
	
	//weight is the amount of HP needed to move.
	int weight = min(abs(x - ax), abs(y - ay));
	if(!visited[i]) pq.push({ -weight, i , a });
}

void select(int a) {
	auto[ax, ay] = point[a];
	auto it = x_sorted_map.find({ ax, ay, a });

	if (it != --x_sorted_map.end()) {
		add(it, a, ax, ay, FORWARD);
	}
	if (it != x_sorted_map.begin()) {
		add(it, a, ax, ay, REVERSE);
	}
	it = y_sorted_map.find({ ay, ax, a });
	if (it != --y_sorted_map.end()) {
		add(it, a, ay, ax, FORWARD);
	}
	if (it != y_sorted_map.begin()) {
		add(it, a, ay, ax, REVERSE);
	}
}

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//padding
	point.push_back({ 0, 0 });

	//input
	cin >> N >> Q;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		point.push_back({ x, y });
		x_sorted_map.insert({ x, y, i + 1 });
		y_sorted_map.insert({ y, x, i + 1 });
	}

	//init
	for (int i = 1; i <= N; i++) {
		visited[i] = false;
	}

	//prim algorithm
	visited[0] = true;
	pq.push({ 0, 1, 0 });
	while (!pq.empty()) {
		auto[w, cur, bef] = pq.top(); pq.pop();

		if (visited[cur]) continue;
		visited[cur] = true;
		//tree structure
		adj[bef].push_back({ cur, -w });
		adj[cur].push_back({ bef, -w });
		select(cur);
	}
	
	dfs(0, 1, 0);
	//LCA
	//O(NlogN)
	for (int k = 1; k < LOG_MAX; k++) {
		for (int i = 1; i <= N; i++) {
			parent[k][i] = parent[k - 1][parent[k - 1][i]];
			HP[k][i] = max(HP[k - 1][parent[k - 1][i]], HP[k - 1][i]);
		}
	}

	//O(QlogN)
	for (int i = 0; i < Q; i++) {
		//query
		cin >> a >> b >> X;
		//플레이어의 최대 HP 제한이 X일 때, 체크포인트 A에서 시작하여서 체크포인트 B로 이동할 수 있는 방법이 있는가?
		
		int hp = LCA(a, b);
		bool flag = hp <= X;
		cout << (flag  ? "YES" : "NO") << '\n';
	}
}