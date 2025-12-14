#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 100000 + 5;

enum {
	X,
	Y,
	Z
};

vector<tuple<int, int>> axis_sorted[3];
vector<int> adj[MAX];

int x, y, z, N;
int parent[MAX];

//union find for kruskal algorithm
int find(int a) {
	if (parent[a] == a) {
		return a;
	}
	return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
	a = find(a);
	b = find(b);

	parent[a] = b;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> z;
		axis_sorted[X].push_back({ x, i });
		axis_sorted[Y].push_back({ y, i });
		axis_sorted[Z].push_back({ z, i });
	}	

	//sorting
	sort(axis_sorted[X].begin(), axis_sorted[X].end());
	sort(axis_sorted[Y].begin(), axis_sorted[Y].end());
	sort(axis_sorted[Z].begin(), axis_sorted[Z].end());

	priority_queue<tuple<int, int, int>> pq;
	
	//when sorted, the vertex next to both is the nearest vertex on that coordinate.
	for (int i = 0; i < N - 1; i++){
		for (int j = 0; j < 3; j++) {
			auto [u_coord, u] = axis_sorted[j][i];
			auto [v_coord, v] = axis_sorted[j][i + 1];

			pq.push({ -abs(u_coord - v_coord), u, v });
		}
	}

	for (int i = 0; i < N; i++) {
		parent[i] = i;
	}

	int ans = 0;
	//kruskal algorithm
	while (!pq.empty()) {
		auto [dist, u, v] = pq.top(); pq.pop();
		if (find(u) == find(v)) continue;
		merge(u, v);
		ans += -dist;
	}

	cout << ans;
}