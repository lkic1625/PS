#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAX_N 30000

struct DisjointSet {
    int n;
    vector<int> parent, rank;
    DisjointSet(int _n) : n(_n), parent(_n), rank(_n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) rank[v]++;
        return true;
    }
    bool is_connected(int u, int v) {
        return find(u) == find(v);
    }
};

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int _n) : n(_n), tree(_n * 4) {}

    void _update(int node, int start, int end, int idx, int dif) {
        if (idx < start || idx > end) return;
        tree[node] += dif;
        if (start != end) {
            int mid = (start + end) / 2;
            _update(node * 2, start, mid, idx, dif);
            _update(node * 2 + 1, mid + 1, end, idx, dif);
        }
    }

    void update(int idx, int dif) {
        _update(1, 0, n - 1, idx, dif);
    }

    int _query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) / 2;
        return _query(node * 2, start, mid, left, right) + _query(node * 2 + 1, mid + 1, end, left, right);
    }

    int query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }
};

struct Query {
    char type;
    int a, b;
};

int N, Q;
vector<int> penguins;
vector<Query> queries;
vector<int> adj[MAX_N + 1];
vector<int> children[MAX_N + 1];
int parent[MAX_N + 1];
int depth[MAX_N + 1];
int subtree_size[MAX_N + 1];
vector<int> exp_ancestor[MAX_N + 1];
vector<vector<int> > heavy_paths;
vector<int> heavy_path_index;

void dfs(int u, vector<bool>& visited) {
    // calculate depth, exp_ancestor, subtree_size
    visited[u] = true;
    subtree_size[u] = 1;

    exp_ancestor[u] = vector<int>(1, parent[u]);
    for (int log_jump = 0;; ++log_jump) {
        int arrived = exp_ancestor[u][log_jump];
        if (exp_ancestor[arrived].size() <= log_jump) break;
        int next = exp_ancestor[arrived][log_jump];
        exp_ancestor[u].push_back(next);
    }

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            children[u].push_back(v);
            depth[v] = depth[u] + 1;
            dfs(v, visited);
            subtree_size[u] += subtree_size[v];
        }
    }
}

void HLD(int root) {
    heavy_path_index.resize(N + 1, -1);

    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) q.push(v);

        if (u == root) continue;

        int p = parent[u];

        if (subtree_size[u] * 2 >= subtree_size[p] && p != root) {
            int pi = heavy_path_index[p];
            heavy_paths[pi].push_back(u);
            heavy_path_index[u] = pi;
        }
        else {
            int ui = heavy_paths.size();
            heavy_path_index[u] = ui;
            heavy_paths.push_back(vector<int>(2));
            heavy_paths.back()[0] = p;
            heavy_paths.back()[1] = u;
        }
    }
}

vector<SegmentTree> segment_trees;

void initialize_trees() {
    segment_trees.clear();
    segment_trees.reserve(heavy_paths.size());
    for (auto& path : heavy_paths) {
        int m = path.size();
        segment_trees.push_back(SegmentTree(m));
        for (int i = 0; i < m; i++) {
            segment_trees.back().update(i, penguins[path[i]]);
        }
    }
}

int find_node_in_path(int path_index, int node) {
    int top = heavy_paths[path_index][0];
    return depth[node] - depth[top];
}

void update(int u, int x) {
    int path_index_u = heavy_path_index[u];
    int ui = find_node_in_path(path_index_u, u);
    segment_trees[path_index_u].update(ui, x - penguins[u]);

    for (int v : children[u]) {
        int path_index_v = heavy_path_index[v];
        if (path_index_u != path_index_v) {
            int vi = find_node_in_path(path_index_v, u);
            segment_trees[path_index_v].update(vi, x - penguins[u]);
        }
    }

    penguins[u] = x;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    int diff = depth[v] - depth[u];
    for (int i = 0; (1 << i) <= diff; i++) {
        if (diff & (1 << i))
            v = exp_ancestor[v][i];
    }

    if (u == v) return u;

    for (int i = exp_ancestor[u].size() - 1; i >= 0; i--) {
        if (i < exp_ancestor[v].size() && exp_ancestor[u][i] != exp_ancestor[v][i]) {
            u = exp_ancestor[u][i];
            v = exp_ancestor[v][i];
        }
    }
    return exp_ancestor[u][0];
}

// total penguins on path u - v

int query_topdown(int u, int v) {
    if (u == v) return penguins[u];

    if (heavy_path_index[u] == heavy_path_index[v]) {
        int path_index = heavy_path_index[u];
        int ui = find_node_in_path(path_index, u);
        int vi = find_node_in_path(path_index, v);
        return segment_trees[path_index].query(ui, vi);
    }

    int path_index = heavy_path_index[v];
    int top_of_path = heavy_paths[path_index][0];
    int vi = find_node_in_path(path_index, v);
    return segment_trees[path_index].query(0, vi) + query_topdown(u, top_of_path) - penguins[top_of_path];
}

int query(int u, int v) {
    int t = lca(u, v);
    return query_topdown(t, u) + query_topdown(t, v) - penguins[t];
}

void input() {
    cin >> N;

    penguins.resize(N + 1);
    penguins[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> penguins[i];
    }

    cin >> Q;
    queries.resize(Q);

    char t[10];
    for (int i = 0; i < Q; i++) {
        cin >> t >> queries[i].a >> queries[i].b;
        queries[i].type = t[0];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();

    // make tree
    DisjointSet ds1(N + 1);
    for (int i = 0; i < Q; i++) {
        if (queries[i].type == 'b' && !ds1.is_connected(queries[i].a, queries[i].b)) {
            ds1.merge(queries[i].a, queries[i].b);
            adj[queries[i].a].push_back(queries[i].b);
            adj[queries[i].b].push_back(queries[i].a);
        }
    }

    // dfs
    parent[0] = -1;
    subtree_size[0] = N + 1;
    exp_ancestor[0] = vector<int>();
    depth[0] = 0;
    vector<bool> visited(N + 1, false);
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            parent[i] = 0;
            children[0].push_back(i);
            depth[i] = 1;
            dfs(i, visited);
        }
    }
    // HLD
    HLD(0);
    initialize_trees();

    DisjointSet ds(N + 1);

    for (int i = 0; i < Q; i++) {
        int a = queries[i].a, b = queries[i].b;
        switch (queries[i].type) {
        case 'b':
            cout << (ds.merge(a, b) ? "yes" : "no") << "\n";
            break;
        case 'p':
            update(a, b);
            //cout << "update!\n";
            break;
        case 'e':
            if (ds.is_connected(a, b)) {
                cout << query(a, b) << "\n";
            }
            else {
                cout << "impossible\n";
            }
            break;
        }
    }

     for(auto& path: heavy_paths){
     	for(int u: path){
     		cout << penguins[u] << " ";
     	}
     	cout <<"\n";
     }

    return 0;
}