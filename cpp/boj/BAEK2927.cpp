#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

enum {
	ROOT = 0,
};

const int MAX_N = 3e4 + 5, MAX_Q = 3e5 + 5;

int penguins[MAX_N], visited[MAX_N], number_of_descendants[MAX_N], parent[MAX_N], segment_mapper[MAX_N], offset, top_of_path[MAX_N], depth[MAX_N];
int N, Q, A, B;
string operation;

vector<int> adj[MAX_N], children[MAX_N];

struct Query {
	char operation;
	int A, B;
};

struct SegmentTree {
	int seg[MAX_N * 4];
	void _update(int index, int diff, int node, int left, int right) {
		if (index > right || index < left) {
			return;
		}
		seg[node] += diff;
		if (left != right) {
			int mid = (left + right) / 2;
			_update(index, diff, node * 2, left, mid);
			_update(index, diff, node * 2 + 1, mid + 1, right);
		}
	}

	void update(int index, int value) {
		_update(index, value, 1, 1, N);
	}
	int _query(int lo, int hi, int node, int left, int right) {
		if (lo > right || hi < left) {
			return 0;
		}
		if (lo <= left && right <= hi) {
			return seg[node];
		}

		int mid = (left + right) / 2;
		return _query(lo, hi, node * 2, left, mid) + _query(lo, hi, node * 2 + 1, mid + 1, right);
	}

	int query(int lo, int hi) {
		return _query(lo, hi, 1, 1, N);
	}
};

struct UnionFind {
	int parent[MAX_N];
	UnionFind() {
		for(int i = 0; i < MAX_N; i++){
			parent[i] = i;
		}
	}
	int find(int u) {
		if (parent[u] == u) {
			return u;
		}
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u);
		v = find(v);

		parent[u] = v;
	}
};

Query queries[MAX_Q];
SegmentTree tree;
UnionFind uf;


void dfs(int here, int level) {
	visited[here] = true;
	number_of_descendants[here] = 1;
	depth[here] = level;

	for (auto child : adj[here]) if (!visited[child]) {
		parent[child] = here;
		children[here].push_back(child);
		dfs(child, level + 1);
		
		number_of_descendants[here] += number_of_descendants[child];
		if (number_of_descendants[children[here].back()] > number_of_descendants[children[here].front()]) {
			swap(children[here].front(), children[here].back());
		}
	}
}

void heavy_light_decompostion(int here) {
	//dfs ordering
	segment_mapper[here] = offset++;
	tree.update(segment_mapper[here], penguins[here]);

	for (auto child : children[here]) {
		if (children[here].front() != child || here == ROOT) {
			top_of_path[child] = child;
		}
		else {
			top_of_path[child] = top_of_path[here];
		}
		heavy_light_decompostion(child);
	}
}

int query(int u, int v) {
	int ret = 0;
	if (u == v) return penguins[v];
	
	while (top_of_path[u] != top_of_path[v]) {
		if (depth[top_of_path[u]] > depth[top_of_path[v]]) {
			swap(u, v);
		}
		int lo = segment_mapper[top_of_path[v]];
		int hi = segment_mapper[v];

		ret += tree.query(lo, hi);
		v = parent[top_of_path[v]];
	}
	if (depth[u] > depth[v]) {
		swap(u, v);
	}
	int lo = segment_mapper[u];
	int hi = segment_mapper[v];
	
	ret += tree.query(lo, hi);


	return ret;
}

void update(int u, int value) {
	tree.update(segment_mapper[u], value - penguins[u]);
	penguins[u] = value;
}


int main() {
	//FAST I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> penguins[i];
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> operation >> A >> B;
		queries[i] = { operation.front(), A, B };
		if (queries[i].operation == 'b') {//opeartion == "bridge"
			uf.merge(A, B);
			adj[A].push_back(B);
			adj[B].push_back(A);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (uf.find(i) != ROOT) {
			uf.merge(i, ROOT);
			adj[ROOT].push_back(i);
			adj[i].push_back(ROOT);
		}
	}

	dfs(ROOT, 0);
	heavy_light_decompostion(ROOT);

	for (int i = 1; i <= N; i++) {

		uf.parent[i] = i;
	}

	for (int i = 0; i < Q; i++) {
		auto [operation, A, B] = queries[i];

		if (operation == 'b') {
			if (uf.find(A) == uf.find(B)) {
				cout << "no" << endl;
			}
			else {
				uf.merge(A, B);
				cout << "yes" << endl;
			}
		}
		else if (operation == 'e') {
			if (uf.find(A) == uf.find(B)) {
				cout << query(A, B) << endl;
			}
			else {
				cout << "impossible" << endl;
			}
		}
		else {
			penguins[A] = B;
			update(A, B);
		}
	}



}