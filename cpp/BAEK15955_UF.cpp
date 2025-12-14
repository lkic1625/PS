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

struct UnionFind {
	int parent[MAX];
	UnionFind() {
		for (int i = 0; i < MAX; i++) {
			parent[i] = i;
		}
	}

	int find(int a) {
		if (parent[a] == a) {
			return a;
		}

		return parent[a] = find(parent[a]);
	}

	void merge(int a, int b) {
		a = find(a);
		b = find(b);

		parent[b] = a;
	}

};

struct Query {
	int HP, a, b, index;
};

struct Point {
	int x, y, index;
};

struct Edge {
	int u, v, weight;
};

int N, Q;
int x, y, a, b, X;
int visited[MAX];
int response[MAX];

vector<tuple<int, int, int>> x_sorted, y_sorted, edge;
vector<Query> query;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> N >> Q;

	for (int i = 1; i <= N; i++) {
		cin >> x >> y;
		x_sorted.push_back({ x, y, i });
		y_sorted.push_back({ y, x, i });
	}

	for (int i = 0; i < Q; i++) {
		cin >> a >> b >> X;
		query.push_back({ X, a, b, i });
	}
	//x좌표순으로 sorting
	sort(x_sorted.begin(), x_sorted.end());
	//y좌표순으로 sorting
	sort(y_sorted.begin(), y_sorted.end());

	for (int i = 0; i + 1 < x_sorted.size(); i++) {
		auto [x, y, index] = x_sorted[i];
		auto [next_x, next_y, next_index] = x_sorted[i + 1];
		
		int u = index;
		int v = next_index;
		int weight = next_x - x;
		edge.push_back({ weight, u, v });
	}

	for (int i = 0; i + 1 < y_sorted.size(); i++) {
		auto [y, x, index] = y_sorted[i];
		auto [next_y, next_x, next_index] = y_sorted[i + 1];

		int u = index;
		int v = next_index;
		int weight = next_y - y;
		edge.push_back({ weight, u, v });
	}

	//HP 순서로 sorting
	sort(query.begin(), query.end(), [](const Query& lv, const Query& rv) {
		return lv.HP < rv.HP;
	});
	//weight 순으로 sorting
	sort(edge.begin(), edge.end());

	UnionFind uf;
	int offset = 0;

	//kruskal algorithm
	for (int i = 0; i < Q; i++) {
		auto [HP, a, b, index] = query[i];
		for (offset; offset < edge.size(); offset++) {
			auto [diff, u, v] = edge[offset];
			if (diff > HP) break;
			uf.merge(u, v);
		}
		//플레이어의 최대 HP 제한이 X일 때, 체크포인트 A에서 시작하여서 체크포인트 B로 이동할 수 있는 방법이 있는가?
		// == 길이가 X이하인 간선을 선택해 MST를 생성할 때, 정점 A와 B는 Connected 되어있는가?
		int isMovable = (uf.find(a) == uf.find(b));
		response[index] = isMovable;

	}

	for (int i = 0; i < Q; i++) {
		if (response[i]) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}

}