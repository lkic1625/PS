#include<iostream>
#include<vector>
#include<math.h>
#include<cassert>
#include<queue>
#include<string>

typedef unsigned long long ll;
const ll mod = 1LL << 32;

typedef unsigned int uint;

using namespace std;

const int MAX_N = 500000 + 5, MAX_Q = 100000;
const long long MOD = 1LL << 32;

enum {
	ROOT = 1,
	ADD_V_TO_SUBTREE_OF_X = 1,
	ADD_V_TO_PATH_FROM_X_TO_Y = 2,
	MUL_V_TO_SUBTREE_OF_X = 3,
	MUL_V_TO_PATH_FROM_X_TO_Y = 4,
	SUM_ALL_IN_SUBTREE_OF_X = 5,
	SUM_ALL_IN_PATH_FROM_X_TO_Y = 6,
	MUL = 0,
	ADD = 1,
	SUM = 9,
};

struct Seg {
	ll tree[2020202];
	ll tmp[2020202][2];

	void push(int node, int s, int e) {
		if (tmp[node][0] == 1 && tmp[node][1] == 0) return;
		tree[node] *= tmp[node][0]; tree[node] %= mod;
		tree[node] += (e - s + 1) * tmp[node][1]; tree[node] %= mod;
		if (s ^ e) {
			tmp[node * 2][0] *= tmp[node][0]; tmp[node * 2][0] %= mod;
			tmp[node * 2][1] *= tmp[node][0]; tmp[node * 2][1] %= mod;
			tmp[node * 2][1] += tmp[node][1]; tmp[node * 2][1] %= mod;

			tmp[node * 2 + 1][0] *= tmp[node][0]; tmp[node * 2 + 1][0] %= mod;
			tmp[node * 2 + 1][1] *= tmp[node][0]; tmp[node * 2 + 1][1] %= mod;
			tmp[node * 2 + 1][1] += tmp[node][1]; tmp[node * 2 + 1][1] %= mod;
		}
		tmp[node][0] = 1, tmp[node][1] = 0;
	}

	void update(int node, int s, int e, int l, int r, ll mul, ll sum) {
		push(node, s, e);
		if (r < s || e < l) return;
		if (l <= s && e <= r) {
			tree[node] *= mul; tree[node] %= mod;
			tree[node] += (e - s + 1) * sum; tree[node] %= mod;
			if (s ^ e) {
				tmp[node * 2][0] *= mul; tmp[node * 2][0] %= mod;
				tmp[node * 2][1] *= mul; tmp[node * 2][1] %= mod;
				tmp[node * 2][1] += sum; tmp[node * 2][1] %= mod;

				tmp[node * 2 + 1][0] *= mul; tmp[node * 2 + 1][0] %= mod;
				tmp[node * 2 + 1][1] *= mul; tmp[node * 2 + 1][1] %= mod;
				tmp[node * 2 + 1][1] += sum; tmp[node * 2 + 1][1] %= mod;
			}
			return;
		}
		int m = s + e >> 1;
		update(node * 2, s, m, l, r, mul, sum);
		update(node * 2 + 1, m + 1, e, l, r, mul, sum);
		tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % mod;
	}

	ll query(int node, int s, int e, int l, int r) {
		push(node, s, e);
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return tree[node];
		int m = s + e >> 1;
		ll t1 = query(node * 2, s, m, l, r);
		ll t2 = query(node * 2 + 1, m + 1, e, l, r);
		return (t1 + t2) % mod;
	}
} seg;


struct SegmentTree {
	uint seg[MAX_N * 4];
	uint lazy[2][MAX_N * 4];
	
	SegmentTree() {
		for (int i = 0; i < 4 * MAX_N; i++) {
			lazy[MUL][i] = 1;
		}
	}

	void update_lazy(int node, int left, int right, int operation) {
		if (lazy[operation][node] == 0) return;
		if (operation == ADD) {
			seg[node] += (right - left + 1) * lazy[operation][node];
			//seg[node] %= MOD;
			if (left != right) {
				lazy[operation][node * 2] += lazy[operation][node];
				//lazy[operation][node * 2] %= MOD;
				lazy[operation][node * 2 + 1] += lazy[operation][node];
				//lazy[operation][node * 2 + 1] %= MOD;
			}
			lazy[operation][node] = 0;
		}
		else {
			seg[node] = seg[node] * lazy[operation][node];
			//seg[node] %= MOD;
			if (left != right) {
				lazy[operation][node * 2] *= lazy[operation][node];
				//lazy[operation][node * 2] %= MOD;
				lazy[operation][node * 2 + 1] *= lazy[operation][node];
				//lazy[operation][node * 2 + 1] %= MOD;
			}
			lazy[operation][node] = 1;
		}
	}

	uint update_mul(int lo, int hi, int mul, int node, int left, int right) {
		update_lazy(node, left, right, MUL);
		update_lazy(node, left, right, ADD);
		if (lo > right || left > hi) {
			return seg[node];
		}
		if (lo <= left && right <= hi) {
			lazy[MUL][node] *= mul;
			update_lazy(node, left, right, MUL);
			//return seg[node] %= MOD;
			return seg[node];
		}
		int mid = (left + right) / 2;
		return seg[node] = (update_mul(lo, hi, mul, 2 * node, left, mid) + update_mul(lo, hi, mul, 2 * node + 1, mid + 1, right)) % MOD;
	}

	uint update_add(int lo, int hi, int add, int node, int left, int right) {
		update_lazy(node, left, right, ADD);
		update_lazy(node, left, right, MUL);
		if (lo > right || left > hi) {
			return seg[node];
		}
		if (lo <= left && right <= hi) {
			lazy[ADD][node] += add;
			update_lazy(node, left, right, ADD);
			//return seg[node] %= MOD;
			return seg[node];
		}
		int mid = (left + right) / 2;
		return seg[node] = (update_add(lo, hi, add, 2 * node, left, mid) + update_add(lo, hi, add, 2 * node + 1, mid + 1, right)) % MOD;
	}

	uint sum(int lo, int hi, int node, int left, int right) {
		update_lazy(node, left, right, ADD);
		update_lazy(node, left, right, MUL);
		if (lo > right || left > hi) {
			return 0;
		}
		if (lo <= left && right <= hi) {
			return seg[node];
		}
		int mid = (left + right) / 2;
		return (sum(lo, hi, node * 2, left, mid) + sum(lo, hi, node * 2 + 1, mid + 1, right)) % MOD;

	}
};

SegmentTree graph;
vector<int> adj[MAX_N], children[MAX_N];

uint  visited[MAX_N], parent[MAX_N], seg_index[MAX_N], offset, subtree_size[MAX_N], depth[MAX_N], heavy_path_top[MAX_N], end_index_of_path[MAX_N];
uint  N, Q, S, E, X, Y, command;
uint V;

void dfs(int here) {
	visited[here] = true;
	for (auto child : adj[here]) if(!visited[child]) {
		children[here].push_back(child);
		dfs(child);
	}
}

void dfs1(int here, int level) {
	
	assert(level < N);
	subtree_size[here] = 1;
	depth[here] = level;
	for (int& child : children[here]) {
		parent[child] = here;
		dfs1(child, level + 1);
		subtree_size[here] += subtree_size[child];
		if (subtree_size[child] > subtree_size[children[here][0]]) {
			swap(children[here].back(), children[here][0]);
		}
	}
	
}


void dfs(int here, int level) {
	visited[here] = true;
	subtree_size[here] = 1;
	depth[here] = level;

	for (int& child : adj[here]) if (!visited[child]) {
		parent[child] = here;
		dfs(child, level + 1);
		subtree_size[here] += subtree_size[child];

		children[here].push_back(child);
		if (subtree_size[child] > subtree_size[children[here][0]]) {
			swap(children[here].back(), children[here][0]);
		}
	}
}

void heavy_light_decomposion(int here) {

	seg_index[here] = ++offset;
	
	for (auto child : children[here]) {
		if (child == children[here].front()) {
			heavy_path_top[child] = heavy_path_top[here];
		}
		else {
			heavy_path_top[child] = child;
		}
		heavy_light_decomposion(child);
		
	}
	end_index_of_path[here] = offset;
}


void subtree_query(int X, uint value, int operation) {
	int lo = seg_index[X];
	int hi = end_index_of_path[X];

	if (operation == MUL) {
		graph.update_mul(lo, hi, value, 1, 0, N);
	}
	else if(operation == ADD){
		graph.update_add(lo, hi, value, 1, 0, N);
	}
	else{
		cout << graph.sum(lo, hi, 1, 0, N) << endl;
	}
}


void range_query(int X, int Y, uint value, int operation) {

	uint ret = 0;

	while (heavy_path_top[X] != heavy_path_top[Y]) {
		if (depth[heavy_path_top[X]] > depth[heavy_path_top[Y]]) swap(X, Y);

		int top_of_path_Y = heavy_path_top[Y];
		int lo = seg_index[top_of_path_Y];
		int hi = seg_index[Y];

		if (operation == MUL) {
			graph.update_mul(lo, hi, value, 1, 0, N);
		}
		else if(operation == ADD){
			graph.update_add(lo, hi, value, 1, 0, N);
		}
		else {
			ret += graph.sum(lo, hi, 1, 0, N);
			//ret %= MOD;
		}

		Y = parent[top_of_path_Y];
	}

	if (depth[X] > depth[Y]) swap(X, Y);

	int lo = seg_index[X];
	int hi = seg_index[Y];

	if (operation == MUL) {
		graph.update_mul(lo, hi, value, 1, 0, N);
	}
	else if (operation == ADD) {
		graph.update_add(lo, hi, value, 1, 0, N);
	}
	else {
		ret += graph.sum(lo, hi, 1, 0, N);
		//ret %= MOD;
		cout << ret << endl;
	}
}

int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> Q;

	for (int i = 1; i < N; i++) {
		cin >> S >> E;
		adj[S].push_back(E);
		adj[E].push_back(S);
	}

	heavy_path_top[ROOT] = ROOT;
	dfs(ROOT, 0);
	heavy_light_decomposion(ROOT);

	for (int i = 0; i < Q; i++) {
		cin >> command;
		switch (command)
		{
		case ADD_V_TO_SUBTREE_OF_X:
			cin >> X >> V;
			subtree_query(X, V, ADD);
			break;
		case ADD_V_TO_PATH_FROM_X_TO_Y:
			cin >> X >> Y >> V;
			range_query(X, Y, V, ADD);
			break;
		case MUL_V_TO_SUBTREE_OF_X:
			cin >> X >> V;
			subtree_query(X, V, MUL);
			break;
		case MUL_V_TO_PATH_FROM_X_TO_Y:
			cin >> X >> Y >> V;
			range_query(X, Y, V, MUL);
			break;
		case SUM_ALL_IN_SUBTREE_OF_X:
			cin >> X;
			subtree_query(X, 0, SUM);
			break;
		case SUM_ALL_IN_PATH_FROM_X_TO_Y:
			cin >> X >> Y;
			range_query(X, Y, 0, SUM);
			break;
		default:
			break;
		}
		
	}

}